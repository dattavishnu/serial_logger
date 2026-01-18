#pragma once
#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif // _WIN32
#define ASIO_STANDALONE
#include <asio.hpp>
#include <iostream>
#include <string>
#include <mutex>
#include <array>
#include <fstream>

class arduino_serial {
private:
    asio::io_context io_context;
    asio::serial_port serial_port;
    std::array<char, 256> read_buffer;
    std::fstream logs;
    std::string log_file;
    asio::executor_work_guard<asio::io_context::executor_type> work_guard;
    asio::strand<asio::io_context::executor_type> strand_;

public:
    explicit arduino_serial(std::string port, std::string log_file_path)
        : io_context(),
        serial_port(io_context, port),
        strand_(asio::make_strand(io_context)),
        log_file(log_file_path),
        work_guard(asio::make_work_guard(io_context))
    {
        serial_port.set_option(asio::serial_port_base::baud_rate(9600));
        serial_port.set_option(asio::serial_port_base::character_size(8));
    }

      bool is_open() const {
        return serial_port.is_open();
    }
    bool set_baud_rate(unsigned int baud_rate) {
        try {
            serial_port.set_option(asio::serial_port_base::baud_rate(baud_rate));
            return true;
        }
        catch (const asio::system_error& e) {
            std::cerr << "Error setting baud rate: " << e.what() << std::endl;
            return false;
        }
    }
    bool set_character_size(unsigned int size) {
        try {
            serial_port.set_option(asio::serial_port_base::character_size(size));
            return true;
        }
        catch (const asio::system_error& e) {
            std::cerr << "Error setting character size: " << e.what() << std::endl;
            return false;
        }
    }
    void set_log_file(std::string str) {
        log_file = str;
    }
    void read() {
        serial_port.async_read_some(
            asio::buffer(read_buffer),
            asio::bind_executor(
                strand_,
                [this](const asio::error_code& ec, std::size_t bytes) {
                    if (ec) {
                        std::cerr << "read error: " << ec.message() << "\n";
                        return;
                    }

                    std::cout.write(read_buffer.data(), bytes);
                    read(); // safe: same strand
                }
            )
        );
    }

    void read_to_logs() {
        serial_port.async_read_some(
            asio::buffer(read_buffer),
            asio::bind_executor(
                strand_,
                [this](const asio::error_code& ec, std::size_t bytes) {
                    if (ec) {
                        std::cerr << "read error: " << ec.message() << "\n";
                        return;
                    }

                    if (!logs.is_open())
                        logs.open(log_file, std::ios::app);

                    logs.write(read_buffer.data(), bytes);
                    logs.flush();

                    read_to_logs(); // safe
                }
            )
        );
    }

    void run() {
        io_context.run();
	}
    void close() {
        asio::error_code close_ec;
        serial_port.close(close_ec);
        if (close_ec) {
            std::cerr << "error closing serial port: " << close_ec.message() << std::endl;
        }
    }
    ~arduino_serial() {
        if (serial_port.is_open()) {
            asio::error_code close_ec;
            serial_port.close(close_ec);
            if (close_ec) {
                std::cerr << "error closing serial port: " << close_ec.message() << std::endl;
            }
        }
    }
};

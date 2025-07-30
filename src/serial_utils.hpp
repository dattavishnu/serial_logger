// SPDX-License-Identifier: MIT
// Copyright (c) 2025 Vishnu

#pragma once
#define ASIO_STANDALONE
#include <asio.hpp>
#include <iostream>
#include <string>
#include <mutex>
#include <array>
#include <fstream>
class arduino_serial{
    private:
        asio::io_context io_context;
        asio::serial_port serial_port;
        std::array<char, 256> read_buffer;
        std::fstream logs;
    public:
        arduino_serial (std::string str):serial_port(io_context,str){
        try{
        serial_port.set_option(asio::serial_port_base::baud_rate(9600));
        serial_port.set_option(asio::serial_port_base::character_size(8));
        }
        catch(const asio::system_error &e){
                std::cerr<<"error"<<e.what()<<std::endl;
        }
        }
        bool is_open() const {
            return serial_port.is_open();
        }
        bool set_baud_rate(unsigned int baud_rate) {
            try {
                serial_port.set_option(asio::serial_port_base::baud_rate(baud_rate));
                return true;
            } catch (const asio::system_error& e) {
                std::cerr << "Error setting baud rate: " << e.what() << std::endl;
                return false;
            }
        }
        bool set_character_size(unsigned int size) {
            try{
                serial_port.set_option(asio::serial_port_base::character_size(size));
                return true;
            } catch (const asio::system_error& e) {
                std::cerr << "Error setting character size: " << e.what() << std::endl;
                return false;
            }
        }
        bool set_log_file(std::string str){
            
        }
        void read(){
            serial_port.async_read_some(asio::buffer(read_buffer),[&](const asio::error_code& ec, std::size_t bytes_transferred){
                if(ec){
                    std::cerr<<"error: "<<ec.message()<<std::endl;
                    return;
                }
                std::string data(read_buffer.data(), bytes_transferred);
                std::cout<<data;
                read(); // Continue reading
            });
        }
        void read_to_logs(){
            serial_port.async_read_some(asio::buffer(read_buffer),[&](const asio::error_code& ec, std::size_t bytes_transferred){
                if(ec){
                    std::cerr<<"error: "<<ec.message()<<std::endl;
                    return;
                }
                logs.open("../logs/logs.txt",std::ios::app);
                if(logs.is_open()){
                std::string data(read_buffer.data(), bytes_transferred);
                logs<<data;
                logs.close();
                }
                read_to_logs(); // Continue reading
                
            });
        }
        void run(){
            io_context.run();
        }        
        bool write(const std::string& message){
            asio::async_write(serial_port, asio::buffer(message), [&](const asio::error_code& ec, std::size_t bytes_transferred){
                if(ec){
                    std::cerr<<"write error: "<<ec.message()<<std::endl;
                    return false;
                } else {
                    std::cout<<"sent: "<<message<<std::endl;
                }
            });
            return true;
        }
        void close(){
            asio::error_code close_ec;
            serial_port.close(close_ec);
            if(close_ec){
                std::cerr<<"error closing serial port: "<<close_ec.message()<<std::endl;
            }
        }
        ~arduino_serial (){
            if(serial_port.is_open()){
                asio::error_code close_ec;
                serial_port.close(close_ec);
                if(close_ec){
                    std::cerr<<"error closing serial port: "<<close_ec.message()<<std::endl;
                }
            }
        }
    };

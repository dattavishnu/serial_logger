# Arduino Serial Logger

A C++ program to asynchronously read data from an Arduino (or any serial device) over `/dev/ttyUSB0` using **ASIO standalone**, and log the data to a text file. This project is useful for debugging or recording sensor data sent over serial.

---

## 🛠 Requirements

- C++17 compatible compiler (e.g., `g++`, `clang++`)
- CMake ≥ 3.10
- POSIX system (Linux, macOS)
- ASIO header-only library
- Arduino or serial device connected via `/dev/ttyUSB0`

---

## Building

1. Clone this repo and place the [ASIO](https://think-async.com/Asio/Download.html) headers in `external/asio/include/`.
2. Build using CMake:

```bash
mkdir build
cd build
cmake ..
make

---

## To Do

- [ ] Implement `set_log_file(path)` method
- [ ] Add timestamps to logs
- [ ] Command-line configuration (port, baud, log path)
- [ ] Windows compatibility

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Author

Vishnu  
Pull requests and improvements are welcome!

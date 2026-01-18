// MIT License

// Copyright (c) 2025 Vishnu

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the “Software”), to deal
// in the Software without restriction, including without limitation the rights  
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell  
// copies of the Software, and to permit persons to whom the Software is  
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in  
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,  
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE  
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER  
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  
// SOFTWARE.


#include <iostream>
#include <memory>
#include "Header.h"
int main(int argc, char* argv[]) {
    std::unique_ptr<arduino_serial> serial = std::make_unique<arduino_serial>("COM3", "logs/logs.txt");
    if (!serial->is_open()) {
        std::cerr << "Failed to open serial port: " << "COM3" << std::endl;
        return 1;
    }
    std::cout << "Serial port opened successfully: " << " COM3" << std::endl;
    serial->read_to_logs();
    serial->run();

    return 0;

}

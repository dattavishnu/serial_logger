
project(serial_logger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
add_executable(serial_logger
    src/main.cpp
    src/serial_utils.hpp
)

# Add ASIO include directory
target_include_directories(serial_logger PRIVATE external/asio/include)


target_compile_definitions(serial_logger PRIVATE ASIO_STANDALONE)

# Optional warnings
target_compile_options(serial_logger PRIVATE -Wall -Wextra -pedantic)


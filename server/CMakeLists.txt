cmake_minimum_required(VERSION 3.26)
project(FlipCoinServer)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)

# 指定服务端源文件
add_executable(FlipCoinServer main.cpp server.cpp)
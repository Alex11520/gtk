cmake_minimum_required(VERSION 3.26)
project(flipcoin)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)

# 找到PkgConfig以确保我们可以找到Gtkmm
find_package(PkgConfig)

# 使用PkgConfig寻找Gtkmm的路径
pkg_check_modules(GTKMM gtkmm-4.0)

# 添加Gtkmm的头文件路径
include_directories(${GTKMM_INCLUDE_DIRS})

# 添加链接器的搜索路径
link_directories(${GTKMM_LIBRARY_DIRS})

# 添加Gtkmm的编译标志到我们的项目
add_definitions(${GTKMM_CFLAGS_OTHER})

# 定义client和server为子项目
add_subdirectory(client)
add_subdirectory(server)

# 指定这个子项目需要最低版本为3.10的CMake
cmake_minimum_required(VERSION 3.10)

# 定义子项目名称
project(FlipCoinClient)

# 找到GTKMM需要的包
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

# 包含GTKMM头文件
include_directories(${GTKMM_INCLUDE_DIRS})

# 链接GTKMM库文件
link_directories(${GTKMM_LIBRARY_DIRS})

# 添加GTKMM编译选项
add_definitions(${GTKMM_CFLAGS_OTHER})

# 指定编译源代码生成可执行文件
add_executable(FlipCoinClient main.cpp window.cpp
        coin_drawing_area.cpp
        coin_drawing_area.h)

# 链接GTKMM库到我们的客户端项目
target_link_libraries(FlipCoinClient ${GTKMM_LIBRARIES})

# 指定 cmake 最小版本, 意指 cmake 版本小于指定版本则构建过程终止
cmake_minimum_required(VERSION 3.26)

# 语言环境配置 ###########################################################################################################

# 语言版本
set(CMAKE_C_STANDARD 17)

# 如果指定的语言版本不受支持, 则构建过程终止
set(CMAKE_C_STANDARD_REQUIRED True)

# 只弃用 ISO C++ 标准的编译器标志, 而不使用特定编译器的扩展
set(CMAKE_C_EXTENSIONS OFF)

if(UNIX)
    # 将 install_rpath 的设置应用在 build_rpath 上
    # 避免在开发期间出现动态库找不到的问题
    set(CMAKE_BUILD_WITH_INSTALL_RPATH True)
endif()

# 项目配置 ##############################################################################################################

# 项目名称和语言
project(graver LANGUAGES C VERSION 1.0.0)

# 发布目录
set(dist_dir ${CMAKE_BINARY_DIR}/dist)

# 二进制文件目录
set(bin_dir ${dist_dir}/bin)

# 裤文件目录
set(lib_dir ${dist_dir}/lib)

# 内部库
# 配置类库
set(lib_lib_name graverlib)

if(WIN32)
    set(lib_lib_file_name ${CMAKE_SHARED_LIBRARY_PREFIX}${lib_lib_name}${CMAKE_DEBUG_POSTFIX}${CMAKE_SHARED_LIBRARY_SUFFIX})
endif()

# 编译相关配置 ###########################################################################################################

# 生成 compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 包含全局头文件
include_directories(${PROJECT_SOURCE_DIR}/include)

# 添加子目录
add_subdirectory(src)

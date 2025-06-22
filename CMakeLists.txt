cmake_minimum_required(VERSION 3.22)

# 告诉 CMake 对 FetchContent 使用新的、更健壮的时间戳行为
cmake_policy(SET CMP0135 NEW)
get_filename_component(PROJECT_NAME_FROM_DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME_FROM_DIR} VERSION 1.0 LANGUAGES CXX)

# --- 全局设置 ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# --- 主可执行文件 ---
add_executable(${PROJECT_NAME})

# 添加源文件
target_sources(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/Src/main.cpp"
)

# 添加头文件
target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/Inc"
)

# --- 链接库 (来自 Lib 目录) ---
# 告诉 CMake 在哪里寻找库文件
target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/Lib")

# 链接一个具体的库文件 (例如，链接一个名为 'libexample.a' 或 'example.lib' 的库)
# 注意：这里只需要写库的名字 'example'，CMake 会自动查找 libexample.a 或 example.lib
# target_link_libraries(${PROJECT_NAME} PRIVATE example)

# --- 测试 (来自 Test 目录) ---
# 开启测试功能
enable_testing()

# 使用 Google Test 框架
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# --- 定义测试目标 ---
# 添加一个测试可执行文件
add_executable(Test Test/test.cpp)

# 为测试目标链接主项目的代码和头文件
target_include_directories(Test PRIVATE
    "${PROJECT_SOURCE_DIR}/Inc"
)

# 告诉 CMake 在哪里寻找库文件
target_link_directories(Test PRIVATE "${PROJECT_SOURCE_DIR}/Lib")

# 链接一个具体的库文件 (例如 'libexample.a')
# 如果你的测试代码调用了 example 库的功能，就需要取消这行的注释
# target_link_libraries(Test PRIVATE example)

# 将测试可执行文件链接到 Google Test
# GTest::gtest_main 包含了 Google Test 的库和它自己的 main 函数
target_link_libraries(Test PRIVATE GTest::gtest_main)

# 将测试可执行文件注册为一个 CTest 测试
add_test(NAME MyProjectTest COMMAND Test)

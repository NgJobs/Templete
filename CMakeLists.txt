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

# --- 创建核心逻辑库 ---
# 将所有核心逻辑代码（除了 main 函数）定义为一个库
add_library(core_logic SHARED)

# 为这个库添加源文件
target_sources(core_logic PRIVATE
    "${PROJECT_SOURCE_DIR}/Src/sum.cpp"

    # 如果未来有 multiply.cpp, a.cpp, b.cpp 等，都在这里添加
)

# 告诉使用这个库的目标，它们需要包含哪个目录来找到头文件
target_include_directories(core_logic PUBLIC
    "${PROJECT_SOURCE_DIR}/Inc"
)

# --- 主可执行文件 ---
add_executable(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/Src/main.cpp")

# 将主程序链接到核心逻辑库
target_link_libraries(${PROJECT_NAME} PRIVATE core_logic)

# --- 链接库 (来自 Lib 目录) ---
target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/Lib")

# 链接一个具体的库文件 (例如 'libexample.a')
# target_link_libraries(Test PRIVATE example)

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
add_executable(Test "${PROJECT_SOURCE_DIR}/Test/test.cpp")

# 将测试程序也链接到核心逻辑库
target_link_libraries(Test PRIVATE core_logic GTest::gtest_main)

# --- 链接库 (来自 Lib 目录) ---
target_link_directories(Test PRIVATE "${PROJECT_SOURCE_DIR}/Lib")

# 链接一个具体的库文件 (例如 'libexample.a')
# target_link_libraries(Test PRIVATE example)

# 将测试可执行文件注册为一个 CTest 测试
add_test(NAME MyProjectTest COMMAND Test)

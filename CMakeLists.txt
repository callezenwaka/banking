cmake_minimum_required(VERSION 3.10)
project(Bank VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Avoid using include_directories globally
# Instead, use target_include_directories for specific targets
set(HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)

# First, download and build GoogleTest before defining targets
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
# Prevent overriding parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Create library target for core bank functionality
add_library(bank_lib
    src/account.cpp
    src/bank.cpp
)

# Set include directories for the library
target_include_directories(bank_lib PUBLIC ${HEADERS_DIR})

# Add compiler warnings for bank_lib
if(MSVC)
    target_compile_options(bank_lib PRIVATE /W4)
else()
    target_compile_options(bank_lib PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Add main bank executable
add_executable(bank src/main.cpp)
target_link_libraries(bank PRIVATE bank_lib)

# Enable testing
enable_testing()

# Add test executable
add_executable(bank_tests
    tests/test_main.cpp
    tests/test_account.cpp
    tests/test_bank.cpp
)

# Link test executable with our library and Google Test
target_link_libraries(bank_tests 
    PRIVATE 
    bank_lib
    GTest::gtest 
    GTest::gtest_main
)

# Add test
add_test(NAME bank_tests COMMAND bank_tests)
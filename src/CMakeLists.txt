# Create library target for core bank functionality
add_library(bank_lib
    account.cpp
    bank.cpp
)

# Set include directories for the library
target_include_directories(bank_lib 
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
)

# Add compiler warnings
if(MSVC)
    target_compile_options(bank_lib PRIVATE /W4)
else()
    target_compile_options(bank_lib PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Add main bank executable
add_executable(bank main.cpp)
target_link_libraries(bank PRIVATE bank_lib)
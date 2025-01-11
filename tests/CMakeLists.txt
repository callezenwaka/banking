add_executable(bank_tests
    test_main.cpp
    test_account.cpp
    test_bank.cpp
)

target_link_libraries(bank_tests 
    PRIVATE 
    bank_lib
    GTest::gtest 
    GTest::gtest_main
)

add_test(NAME bank_tests COMMAND bank_tests)
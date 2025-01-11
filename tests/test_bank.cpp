#include <gtest/gtest.h>
#include "bank.h"
#include <filesystem>

// class BankTest : public ::testing::Test {
// protected:
//     Bank* bank;
//     const std::string TEST_FILENAME = "test_accounts.txt";

//     void SetUp() override {
//         // Remove test file if it exists
//         std::filesystem::remove(TEST_FILENAME);
//         bank = new Bank();
//     }

//     void TearDown() override {
//         delete bank;
//         // Clean up test file
//         std::filesystem::remove(TEST_FILENAME);
//     }
// };

// test_bank.cpp
class BankTest : public ::testing::Test {
protected:
    std::unique_ptr<Bank> bank;
    const std::string TEST_FILENAME = "test_accounts.txt";

    void SetUp() override {
        // Remove test file if it exists
        std::filesystem::remove(TEST_FILENAME);
        bank = std::make_unique<Bank>(TEST_FILENAME);
    }

    void TearDown() override {
        bank.reset();  // Delete bank before removing file
        std::filesystem::remove(TEST_FILENAME);
    }
};

TEST_F(BankTest, CreateNewAccount) {
    EXPECT_TRUE(bank->createAccount("ACC001", "John Doe"));
    
    Account* acc = bank->findAccount("ACC001");
    ASSERT_NE(acc, nullptr);
    EXPECT_EQ(acc->getAccountNumber(), "ACC001");
    EXPECT_EQ(acc->getName(), "John Doe");
    EXPECT_DOUBLE_EQ(acc->getBalance(), 0.0);
}

TEST_F(BankTest, PreventDuplicateAccounts) {
    EXPECT_TRUE(bank->createAccount("ACC001", "John Doe"));
    EXPECT_FALSE(bank->createAccount("ACC001", "Jane Doe"));
}

TEST_F(BankTest, DepositToAccount) {
    EXPECT_TRUE(bank->createAccount("ACC001", "John Doe"));
    
    EXPECT_TRUE(bank->deposit("ACC001", 1000.0));
    
    Account* acc = bank->findAccount("ACC001");
    ASSERT_NE(acc, nullptr);
    EXPECT_DOUBLE_EQ(acc->getBalance(), 1000.0);
}

TEST_F(BankTest, DepositInvalidAmount) {
    EXPECT_TRUE(bank->createAccount("ACC001", "John Doe"));
    
    EXPECT_FALSE(bank->deposit("ACC001", -100.0));
    EXPECT_FALSE(bank->deposit("ACC001", 0.0));
    
    Account* acc = bank->findAccount("ACC001");
    ASSERT_NE(acc, nullptr);
    EXPECT_DOUBLE_EQ(acc->getBalance(), 0.0);
}

TEST_F(BankTest, DepositToNonexistentAccount) {
    EXPECT_FALSE(bank->deposit("ACC001", 1000.0));
}

TEST_F(BankTest, WithdrawFromAccount) {
    EXPECT_TRUE(bank->createAccount("ACC001", "John Doe"));
    EXPECT_TRUE(bank->deposit("ACC001", 1000.0));
    
    EXPECT_TRUE(bank->withdraw("ACC001", 300.0));
    
    Account* acc = bank->findAccount("ACC001");
    ASSERT_NE(acc, nullptr);
    EXPECT_DOUBLE_EQ(acc->getBalance(), 700.0);
}

TEST_F(BankTest, WithdrawInvalidAmount) {
    EXPECT_TRUE(bank->createAccount("ACC001", "John Doe"));
    EXPECT_TRUE(bank->deposit("ACC001", 1000.0));
    
    EXPECT_FALSE(bank->withdraw("ACC001", -100.0));
    EXPECT_FALSE(bank->withdraw("ACC001", 0.0));
    EXPECT_FALSE(bank->withdraw("ACC001", 1500.0));
    
    Account* acc = bank->findAccount("ACC001");
    ASSERT_NE(acc, nullptr);
    EXPECT_DOUBLE_EQ(acc->getBalance(), 1000.0);
}

TEST_F(BankTest, WithdrawFromNonexistentAccount) {
    EXPECT_FALSE(bank->withdraw("ACC001", 100.0));
}

TEST_F(BankTest, FindNonexistentAccount) {
    EXPECT_EQ(bank->findAccount("ACC001"), nullptr);
}
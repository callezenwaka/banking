#include <gtest/gtest.h>
#include "account.h"

class AccountTest : public ::testing::Test {
protected:
    Account* account;

    void SetUp() override {
        account = new Account("ACC001", "John Doe", 1000.0);
    }

    void TearDown() override {
        delete account;
    }
};

TEST_F(AccountTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(account->getAccountNumber(), "ACC001");
    EXPECT_EQ(account->getName(), "John Doe");
    EXPECT_DOUBLE_EQ(account->getBalance(), 1000.0);
}

TEST_F(AccountTest, DepositValidAmount) {
    EXPECT_TRUE(account->deposit(500.0));
    EXPECT_DOUBLE_EQ(account->getBalance(), 1500.0);
}

TEST_F(AccountTest, DepositInvalidAmount) {
    EXPECT_FALSE(account->deposit(-100.0));
    EXPECT_DOUBLE_EQ(account->getBalance(), 1000.0);
    
    EXPECT_FALSE(account->deposit(0.0));
    EXPECT_DOUBLE_EQ(account->getBalance(), 1000.0);
}

TEST_F(AccountTest, WithdrawValidAmount) {
    EXPECT_TRUE(account->withdraw(300.0));
    EXPECT_DOUBLE_EQ(account->getBalance(), 700.0);
}

TEST_F(AccountTest, WithdrawInvalidAmount) {
    EXPECT_FALSE(account->withdraw(-100.0));
    EXPECT_DOUBLE_EQ(account->getBalance(), 1000.0);
    
    EXPECT_FALSE(account->withdraw(0.0));
    EXPECT_DOUBLE_EQ(account->getBalance(), 1000.0);
    
    EXPECT_FALSE(account->withdraw(1500.0));
    EXPECT_DOUBLE_EQ(account->getBalance(), 1000.0);
}

TEST_F(AccountTest, ToStringFormatting) {
    std::string expected = "ACC001,John Doe,1000.000000";
    EXPECT_EQ(account->toString(), expected);
}
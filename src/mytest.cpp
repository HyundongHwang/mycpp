#include <string>
#include <vector>
#include <algorithm>

#include "logsloth.h"
#include "gtest/gtest.h"

TEST(TestSuite0, Test0) {
    EXPECT_TRUE(true);
    LOGSLOTH("test0");
}

TEST(TestSuite0, Test1) {
    EXPECT_TRUE(true);
    LOGSLOTH("test1");
}

TEST(TestSuite0, Test2) {
    EXPECT_TRUE(false);
    LOGSLOTH("test2");
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    auto res = RUN_ALL_TESTS();
}
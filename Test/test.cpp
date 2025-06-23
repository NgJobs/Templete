#include <gtest/gtest.h>

#include "sum.h"  // 确保 sum.h 在 Inc 目录中

// 定义一个名为 "SumTest" 的测试套件，以及一个名为 "Basic" 的测试用例
TEST(SumTest, Basic) {
  EXPECT_EQ(sum(1, 2), 3);
  EXPECT_EQ(sum(-1, 1), 0);
}
// 一个演示如何使用 Google C++ 测试框架的示例程序。
// 本示例展示了如何为一个函数编写一个简单的单元测试，
// 使用 Google C++ 测试框架。
// 使用 Google C++ 测试框架编写单元测试就像 1-2-3 一样简单：
// 步骤 1. 包含必要的头文件，以便你的测试逻辑所需的声明都已包含。
// 不要忘记 gtest.h，它声明了测试框架。

#include "sample1.h"

#include <limits.h>

#include "gtest/gtest.h"
namespace {

// 步骤 2. 使用 TEST 宏来定义你的测试。
//
// TEST 有两个参数：测试用例名和测试名。
// 使用宏后，你应该在一对大括号之间定义你的测试逻辑。你可以使用一系列宏来指示测试的成功或失败。EXPECT_TRUE 和 EXPECT_EQ 是这样的宏的例子。要获取完整的列表，请参阅 gtest.h。
//
// <技术细节>
//
// 在 Google Test 中，测试被组织成测试用例。这是如何保持测试代码整洁的方法。你应该将逻辑相关的测试放入同一个测试用例中。
// 测试用例名和测试名都应该是有效的 C++ 标识符。并且你不应该在名字中使用下划线(_)。
// Google Test 保证你定义的每个测试都恰好运行一次，但它不对测试执行的顺序做出保证。因此，你应该以一种方式编写测试，使它们的结果不依赖于它们的顺序。
//
// </技术细节>

// 测试 Factorial()。

// 测试负数的阶乘。
TEST(FactorialTest, Negative) {
  // 这个测试名为 "Negative"，属于 "FactorialTest"
  // 测试用例。
  EXPECT_EQ(1, Factorial(-5));
  EXPECT_EQ(1, Factorial(-1));
  EXPECT_GT(Factorial(-10), 0);

  // <技术细节>
  //
  // EXPECT_EQ(expected, actual) 与
  // EXPECT_TRUE((expected) == (actual))
  // 是相同的，除了当断言失败时它会打印出预期值和实际值。这对于调试非常有帮助。因此在这种情况下更推荐使用 EXPECT_EQ。
  // 另一方面，EXPECT_TRUE 接受任何布尔表达式，因此更通用。
  //
  // </技术细节>
}

// Tests factorial of 0.
TEST(FactorialTest, Zero) { EXPECT_EQ(1, Factorial(0)); }

// Tests factorial of positive numbers.
TEST(FactorialTest, Positive) {
  EXPECT_EQ(1, Factorial(1));
  EXPECT_EQ(2, Factorial(2));
  EXPECT_EQ(6, Factorial(3));
  EXPECT_EQ(40320, Factorial(8));
}

// Tests IsPrime()

// Tests negative input.
TEST(IsPrimeTest, Negative) {
  // This test belongs to the IsPrimeTest test case.

  EXPECT_FALSE(IsPrime(-1));
  EXPECT_FALSE(IsPrime(-2));
  EXPECT_FALSE(IsPrime(INT_MIN));
}

// Tests some trivial cases.
TEST(IsPrimeTest, Trivial) {
  EXPECT_FALSE(IsPrime(0));
  EXPECT_FALSE(IsPrime(1));
  EXPECT_TRUE(IsPrime(2));
  EXPECT_TRUE(IsPrime(3));
}

// Tests positive input.
TEST(IsPrimeTest, Positive) {
  EXPECT_FALSE(IsPrime(4));
  EXPECT_TRUE(IsPrime(5));
  EXPECT_FALSE(IsPrime(6));
  EXPECT_TRUE(IsPrime(23));
}
}  // namespace

// 步骤 3. 在 main() 中调用 RUN_ALL_TESTS()。
// 我们通过链接 src/gtest_main.cc 文件来实现这一点，该文件包含一个 main() 函数，它为我们调用 RUN_ALL_TESTS()。
// 这将运行你定义的所有测试，打印结果，并在成功时返回 0，否则返回 1。
// 你注意到我们没有注册测试了吗？RUN_ALL_TESTS() 宏神奇地知道我们定义的所有测试。这不是很方便吗？

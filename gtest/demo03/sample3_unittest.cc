// A sample program demonstrating using Google C++ testing framework.

// In this example, we use a more advanced feature of Google Test called
// test fixture.
//
// A test fixture is a place to hold objects and functions shared by
// all tests in a test case.  Using a test fixture avoids duplicating
// the test code necessary to initialize and cleanup those common
// objects for each test.  It is also useful for defining sub-routines
// that your tests need to invoke a lot.
//
// <TechnicalDetails>
//
// The tests share the test fixture in the sense of code sharing, not
// data sharing.  Each test is given its own fresh copy of the
// fixture.  You cannot expect the data modified by one test to be
// passed on to another test, which is a bad idea.
//
// The reason for this design is that tests should be independent and
// repeatable.  In particular, a test should not fail as the result of
// another test's failure.  If one test depends on info produced by
// another test, then the two tests should really be one big test.
//
// The macros for indicating the success/failure of a test
// (EXPECT_TRUE, FAIL, etc) need to know what the current test is
// (when Google Test prints the test result, it tells you which test
// each failure belongs to).  Technically, these macros invoke a
// member function of the Test class.  Therefore, you cannot use them
// in a global function.  That's why you should put test sub-routines
// in a test fixture.
//
// </TechnicalDetails>
// 测试夹具（Test Fixture）是为软件测试提供环境和条件的一组代码，它允许测试用例在其中运行。
// 夹具是指用来固定和支撑被测试对象（如电路板或其他电子组件）的装置，以便进行各种测试。
// 这些夹具确保被测试对象在测试过程中保持在正确的位置和状态，以便测试可以准确进行。
// 在软件测试中，这个概念被抽象化，用来指代为测试用例提供必要环境和条件的代码和数据结构。
// 就像硬件测试中的夹具一样，软件测试中的“测试夹具”为测试用例提供了一个稳定的环境，确保测试可以在一个受控和一致的状态下执行。


// 测试夹具是一个用于存放测试用例中所有测试共享的对象和函数的地方。
// 使用测试夹具可以避免为每个测试重复编写初始化和清理这些共享对象的代码。
// 它还有助于定义测试需要频繁调用的子程序。

#include "sample3-inl.h"
#include "gtest/gtest.h"
namespace {
// To use a test fixture, derive a class from testing::Test.
// 要使用测试夹具，需要从 testing::Test 派生一个类。
class QueueTestSmpl3 : public testing::Test {
  // 把成员变量声明为 protected，以便子类可以访问它们。
  // 例如，如果你的测试夹具有子类，子类可以访问这些成员变量。
 protected:  // You should make the members protected s.t. they can be
             // accessed from sub-classes.
  // virtual void SetUp() will be called before each test is run.  You
  // should define it if you need to initialize the variables.
  // Otherwise, this can be skipped.
  // SetUp()是一个虚函数，定义在gtest的API中；
  // 它在每个测试运行前被调用。一般用于初始化变量；
  void SetUp() override {
    q1_.Enqueue(1);
    q2_.Enqueue(2);
    q2_.Enqueue(3);
  }

  // virtual void TearDown() will be called after each test is run.
  // You should define it if there is cleanup work to do.  Otherwise,
  // you don't have to provide it.
  // TearDown()是一个虚函数，定义在gtest的API中；
  // 它在每个测试运行后被调用。一般用于清理工作；
  // virtual void TearDown() {
  // }

  // A helper function that some test uses.
  // 一个静态辅助函数 Double，它将传入的整数 n 乘以 2 并返回结果。
  static int Double(int n) { return 2 * n; }

  // A helper function for testing Queue::Map().
  // 用于测试 Queue::Map() 方法的辅助函数。
  void MapTester(const Queue<int>* q) {
    // Creates a new queue, where each element is twice as big as the
    // corresponding one in q.
    // 创建一个新队列，其中每个元素都是 q 中对应元素的两倍。
    const Queue<int>* const new_q = q->Map(Double);

    // Verifies that the new queue has the same size as q.
    // 验证新队列的大小与 q 相同。
    ASSERT_EQ(q->Size(), new_q->Size());

    // Verifies the relationship between the elements of the two queues.
    // 验证两个队列元素之间的关系。
    for (const QueueNode<int>*n1 = q->Head(), *n2 = new_q->Head();
         n1 != nullptr; n1 = n1->next(), n2 = n2->next()) {
      EXPECT_EQ(2 * n1->element(), n2->element());
    }
    // 删除新创建的队列，释放内存。
    delete new_q;
  }

  // Declares the variables your tests want to use.
  // 声明你的测试想要使用的变量。
  Queue<int> q0_;
  Queue<int> q1_;
  Queue<int> q2_;
};

// When you have a test fixture, you define a test using TEST_F
// instead of TEST.

// Tests the default c'tor.
// 当有测试夹具时，使用 TEST_F 而不是 TEST 来定义测试。
// 测试默认构造函数。
TEST_F(QueueTestSmpl3, DefaultConstructor) {
  // You can access data in the test fixture here.
  EXPECT_EQ(0u, q0_.Size());
}

// Tests Dequeue().
// 测试 Dequeue() 方法。
TEST_F(QueueTestSmpl3, Dequeue) {
  int* n = q0_.Dequeue();     // 从 q0_ 队列中出队一个元素。
  EXPECT_TRUE(n == nullptr);  // 验证出队的结果为 nullptr，因为 q0_ 是空队列。

  n = q1_.Dequeue();          // 从 q1_ 队列中出队一个元素。
  ASSERT_TRUE(n != nullptr);  // 断言出队的结果不为 nullptr。
  EXPECT_EQ(1, *n);           // 验证 q1_ 队列的大小变为 0。
  EXPECT_EQ(0u, q1_.Size());  // 删除出队的元素，释放内存。
  delete n;

  n = q2_.Dequeue();
  ASSERT_TRUE(n != nullptr);
  EXPECT_EQ(2, *n);
  EXPECT_EQ(1u, q2_.Size());
  delete n;
}

// Tests the Queue::Map() function.
// 调用 MapTester 函数测试队列的 Map 方法。
TEST_F(QueueTestSmpl3, Map) {
  MapTester(&q0_);
  MapTester(&q1_);
  MapTester(&q2_);
}
}  // namespace

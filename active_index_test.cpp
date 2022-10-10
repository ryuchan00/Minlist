#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include <algorithm>

#include "contents.h"
#include "minhash.h"

class FunctionTest : public CPPUNIT_NS::TestFixture {
  //テストクラス
  CPPUNIT_TEST_SUITE(FunctionTest);  //登録のスタート
  CPPUNIT_TEST(test_active_index);   //メンバ関数の登録
  CPPUNIT_TEST_SUITE_END();          //登録の終了

 protected:
  //   Function *func;
  void test_active_index();

 public:
  void setUp();
  void testDown();
};

CPPUNIT_TEST_SUITE_REGISTRATION(FunctionTest);

//テスト起動時に実行
void FunctionTest::setUp() {
  //   func = new Function();
}

//テスト終了時に実行
void FunctionTest::testDown() {
  //   delete func;
}

void FunctionTest::test_active_index() {
  std::vector<std::vector<int>> minhash;
  // std::vector<int> a{4, 5, 6, 7, 10, 11, 8, 9};
  // std::vector<int> b{4, 5, 6, 7, 10, 11, 8, 9};
  minhash[0] = {4, 5, 6, 7, 10, 11, 8, 9};
  // minhash[1] = {4, 3, 2, 1, 5, 6, 7, 8};

  int num_of_hash = minhash.size();
  int multi = 4;
  int vm = minhash[0].size() / multi;

  // std::vector<std::vector<std::vector<index>>> fx(num_of_hash);
  // std::vector<index> a1 = {{1, 4}};
  // std::vector<index> a2 = {{1, 10}, {2, 8}};
  // fx[0][0] = a1;
  // fx[0][1] = a2;
  std::vector<std::vector<int>> fx{};

  CPPUNIT_ASSERT_EQUAL(active_index(num_of_hash, vm, multi, minhash), fx);
}

int main(int argc, char const *argv[]) {
  CPPUNIT_NS::TestResult controller;

  //結果収集
  CPPUNIT_NS::TestResultCollector result;
  controller.addListener(&result);

  //途中結果の収集
  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener(&progress);

  //テストを走らせる。テストを入れて走る
  CPPUNIT_NS::TestRunner runner;
  runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
  runner.run(controller);

  //結果を標準出力にする。
  CPPUNIT_NS::CompilerOutputter outputter(&result, CPPUNIT_NS::stdCOut());
  outputter.write();

  return result.wasSuccessful() ? 0 : 1;
}

#include "minhash.h"

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include <algorithm>

class FunctionTest : public CPPUNIT_NS::TestFixture {
  //テストクラス
  CPPUNIT_TEST_SUITE(FunctionTest);             //登録のスタート
  CPPUNIT_TEST(test_multi_set_strict_jaccard);  //メンバ関数の登録
  CPPUNIT_TEST(test_mh);
  CPPUNIT_TEST(test_set_intersection);
  CPPUNIT_TEST_SUITE_END();  //登録の終了

 protected:
  //   Function *func;
  void test_multi_set_strict_jaccard();
  void test_mh();
  void test_set_intersection();

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

void FunctionTest::test_multi_set_strict_jaccard() {
  // 多重集合でも機能することを確認する
  std::vector<int> hash1{1, 2};
  std::vector<int> hash2{1, 2, 2};

  CPPUNIT_ASSERT_EQUAL(strict_jaccard(hash1, hash2), 2.0 / 3.0);
}

void FunctionTest::test_mh() {
  // 正常に取れているか確認する。
  std::vector<int> in{0, 0, 1};
  std::vector<int> fx_a{11, 22};
  std::vector<int> fx_b{99, 10, 9};  // 99は使用しない

  CPPUNIT_ASSERT_EQUAL(mh(in, fx_a, fx_b), 29);

  // 要素が3のとき
  in = {0, 1, 2};
  fx_a = {11, 22, 33, 44};
  fx_b = {99, 4, 3, 2, 1};

  CPPUNIT_ASSERT_EQUAL(mh(in, fx_a, fx_b), 27);
}

void FunctionTest::test_set_intersection() {
  // 多重集合でも機能することを確認する
  std::vector<int> set1{1, 2};
  std::vector<int> set2{1, 2, 2};
  std::vector<int> results{1, 2};
  std::vector<int> intersection_in;

  std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(intersection_in));
  bool equal = intersection_in.size() == results.size() && std::equal(intersection_in.cbegin(), intersection_in.cend(), results.cbegin());

  CPPUNIT_ASSERT_EQUAL(equal, true);
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

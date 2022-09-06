#include "minhash.h"

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

class FunctionTest : public CPPUNIT_NS::TestFixture {
  //テストクラス
  CPPUNIT_TEST_SUITE(FunctionTest);             //登録のスタート
  CPPUNIT_TEST(test_multi_set_strict_jaccard);  //メンバ関数の登録
  CPPUNIT_TEST(test_mh);
  CPPUNIT_TEST_SUITE_END();  //登録の終了

 protected:
  //   Function *func;
  void test_multi_set_strict_jaccard();
  void test_mh();

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

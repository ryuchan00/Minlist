// https://www.delftstack.com/ja/howto/c/getrusage-example-in-c/
// getrusage 関数は、プロセスに関する複数のデータポイントを取得し、そのうちの 1つは、struc timeval オブジェクトとして表されるシステム時刻です。
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

enum { NUM_ITERS = 1000000 };

void loopFunc1(size_t num) {
  int tmp = 0;
  for (int i = 0; i < num; ++i) {
    tmp += 1;
  }
}

void *loopFunc2(size_t num) {
  for (int i = 0; i < num; ++i) {
    getpid();
  }
  return NULL;
}

// struct timeval ru_utime; /* 使用されたユーザー時間 */
// struct timeval ru_stime; /* 使用されたシステム時間 */

float diffUserTime(struct rusage *start, struct rusage *end) {
  return (end->ru_utime.tv_sec - start->ru_utime.tv_sec) +
         1e-6 * (end->ru_utime.tv_usec - start->ru_utime.tv_usec);
}

float diffSystemTime(struct rusage *start, struct rusage *end) {
  return (end->ru_stime.tv_sec - start->ru_stime.tv_sec) +
         1e-6 * (end->ru_stime.tv_usec - start->ru_stime.tv_usec);
}

int main() {
  struct rusage start, end;

  // RUSAGE_SELF
  // 呼び出したプロセスの資源使用量、 そのプロセス内の全スレッドが使用している資源の合計を返す。
  getrusage(RUSAGE_SELF, &start);
  loopFunc1(NUM_ITERS);
  getrusage(RUSAGE_SELF, &end);

  printf("loopFunc1 stats:\n");
  printf("  CPU time: %.06f sec user, %.06f sec system\n",
         diffUserTime(&start, &end), diffSystemTime(&start, &end));

  getrusage(RUSAGE_SELF, &start);
  loopFunc2(NUM_ITERS);
  getrusage(RUSAGE_SELF, &end);

  printf("loopFunc2 stats:\n");
  printf("  CPU time: %.06f sec user, %.06f sec system\n",
         diffUserTime(&start, &end), diffSystemTime(&start, &end));

  exit(EXIT_SUCCESS);
  }
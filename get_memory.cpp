#include <stdio.h>
#include <sys/sysinfo.h>

#include <vector>

int main(void) {
  // https://linuxjm.osdn.jp/html/LDP_man-pages/man2/sysinfo.2.html
  struct sysinfo info;

  sysinfo(&info);

  printf("mem_unit:%d\n", info.mem_unit);
  printf("totalram:%ld\n", info.totalram);
  printf("freeram:%ld\n", info.freeram);
  printf("bufferram:%ld\n", info.bufferram);
  printf("totalswap:%ld\n", info.totalswap);
  printf("freeswap:%ld\n", info.freeswap);

  std::vector<int> a(100000, 999999);
  std::vector<std::vector<int>> b;

  for (int i = 0; i < 10000; i++) {
    b.push_back(a);
  }

  struct sysinfo info2;

  sysinfo(&info2);

  printf("mem_unit:%d\n", info2.mem_unit);
  printf("totalram:%ld\n", info2.totalram);
  printf("freeram:%ld\n", info2.freeram);
  printf("bufferram:%ld\n", info2.bufferram);
  printf("totalswap:%ld\n", info2.totalswap);
  printf("freeswap:%ld\n", info2.freeswap);

  return 0;
}
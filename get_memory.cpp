  #include <stdio.h>
  #include <sys/resource.h>
  #include <sys/sysinfo.h>

  #include <vector>

  int main(void) {
    // https://linuxjm.osdn.jp/html/LDP_man-pages/man2/sysinfo.2.html
    struct sysinfo info;

    sysinfo(&info);

    printf("--before process--\n");
    printf("--used sysinfo--\n");
    printf("mem_unit:%d\n", info.mem_unit);
    printf("totalram:%ld\n", info.totalram);
    printf("freeram:%ld\n", info.freeram);
    printf("bufferram:%ld\n", info.bufferram);
    printf("totalswap:%ld\n", info.totalswap);
    printf("freeswap:%ld\n", info.freeswap);

    struct rusage resource;
    getrusage(RUSAGE_SELF, &resource);
    printf("--used getrusage--\n");
    printf("ru_maxrss: %ld\n", resource.ru_maxrss);

    std::vector<int> a(100000, 999999);
    std::vector<std::vector<int>> b;

    for (int i = 0; i < 10000; i++) {
      b.push_back(a);
    }

    struct sysinfo info2;

    sysinfo(&info2);

    printf("--after process--\n");
    printf("--used sysinfo--\n");
    printf("mem_unit:%d\n", info2.mem_unit);
    printf("totalram:%ld\n", info2.totalram);
    printf("freeram:%ld\n", info2.freeram);
    printf("bufferram:%ld\n", info2.bufferram);
    printf("totalswap:%ld\n", info2.totalswap);
    printf("freeswap:%ld\n", info2.freeswap);

    struct rusage resource2;
    getrusage(RUSAGE_SELF, &resource2);
    printf("--used getrusage--\n");
    printf("ru_maxrss: %ld\n", resource2.ru_maxrss);

    return 0;
  }
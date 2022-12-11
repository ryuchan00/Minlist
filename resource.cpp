#include <stdio.h>
#include <sys/resource.h>

int main(int argc, char *argv[]) {
  struct rusage resource;
  getrusage(RUSAGE_SELF, &resource);
  printf("memory: %ld\n", resource.ru_maxrss);
  return 0;
}

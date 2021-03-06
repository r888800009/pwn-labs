#include <stdio.h>
#include <stdlib.h>

/*
gcc -o got_hijack got_hijack.c -no-pie -z lazy
*/

void init() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
}

int64_t data[10];

int main() {
  init();

  int index;
  printf("index:");
  scanf("%d", &index);

  printf("data[%d] = %lld\n", index, data[index]);

  printf("overwrite:");
  scanf("%lld", &data[index]);

  printf("printf %p\n", data[index]);
  puts("puts");
  scanf("%d", &index);
  return 0;
}

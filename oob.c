#include <stdio.h>
#include <stdlib.h>

void shellcode() {
  __asm__("pop %rax");  // fix stack
  system("/bin/sh");
}

int index_get() {
  int index;
  printf("index:");
  scanf("%d", &index);
  return index;
}

int main(int argc, char *argv[]) {
  int index = 123;
  long array[1] = {0};

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  printf("gift %p\n", shellcode);
  printf("ptr %p\n", array);

  index = index_get();

  printf("set:");
  scanf("%p", &array[index]);

  return 0;
}

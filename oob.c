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
  long index = 0;
  long *ptr = &index;

  printf("gift %p\n", shellcode);
  printf("ptr %p\n", ptr);

  index = index_get();

  printf("set:");
  scanf("%p", &ptr[index]);

  return 0;
}

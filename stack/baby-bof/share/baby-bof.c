#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
}

void stack_dump() {
  size_t i;
  puts("\nStack Dump:");
  for (i = 0; i < 17; i++) printf("%d: %p\n", i, (&i)[i]);
  puts("Dump End");
}

// gcc baby-bof.c -o baby-bof
int main(int argc, char **argv) {
  char buf[0x8];
  init();

  stack_dump();

  puts("bof: ");
  read(0, buf, 0x30);

  stack_dump();

  return 0;
}

void shellcode() {
  __asm__("pop %rax");  // fix stack
  system("/bin/sh");
}

void shellcode2() {
  system("/bin/sh");
}


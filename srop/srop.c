#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// gcc srop.c -o srop -g -fno-stack-protector -no-pie

void my_restore_rt() { asm("mov $0xf, %rax; syscall; syscall; ret"); }

int main() {
  char *new_stack = malloc(0x40000);
  char buf[0x10];

  setvbuf(stdout, buf, _IONBF, 0);
  setvbuf(stderr, buf, _IONBF, 0);
  setvbuf(stdin, buf, _IONBF, 0);

  printf("my_restore_rt: %p\n", my_restore_rt);
  printf("new_mmap: %p\n", new_stack);
  read(0, buf, 0x1000);
  puts("done");
  return 0;
}


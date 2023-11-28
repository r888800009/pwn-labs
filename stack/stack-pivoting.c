#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// gcc stack-pivoting.c -o stack-pivoting -no-pie -fno-stack-protector

char data[0x2000] = {0};

void init() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
}

int main(int argc, char **argv) {
  init();
  char buf[0x8];

  puts("Welcome to the stack-based buffer overflow challenge!");
  printf("Please enter your data: ");
  read(0, 0x2000 + data, 0x200);

  printf("Please enter your password: ");
  read(0, buf, 0x18);

  printf("clean rdi, %s!", "rsi");
  return 0;
}

void gadgets() { asm("pop %rdi ; ret"); }

void functions() {
  system("/bin/ls");
  puts("/bin/sh");
  gets(NULL);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void init() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
}

// gcc -o fmtstr_stack fmtstr_stack.c -z lazy

int main() {
  char buf[0x80];
  init();

  for (int i = 0; i < 3; i++) {
    puts("[+] reading");
    read(0, buf, 0x80 - 1);
    puts("[+] printf");
    printf(buf);
  }

  return 0;
}

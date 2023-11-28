#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct challenge {
    char buf[0x200];
    FILE *fp;
} challenge;

void shellcode() {
  __asm__("pop %rax");  // fix stack
  system("/bin/sh");
}

void shellcode2() {
  system("/bin/sh");
}

// gcc baby-file-struct.c -o baby-file-struct
int main(int argc, char **argv) {
  printf("shellcode: %p\n", shellcode);
  printf("shellcode2: %p\n", shellcode2);
  printf("challenge.buf: %p\n", challenge.buf);
  printf("challenge.fp: %p\n", challenge.fp);
  
  // open /etc/passwd
  challenge.fp = fopen("/etc/passwd", "r");
  
  // buffer overflow
  puts("bof: ");
  read(0, challenge.buf, 0x400);

  // close file
  fclose(challenge.fp);
  return 0;
}


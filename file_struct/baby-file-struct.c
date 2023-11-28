#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct challenge {
    char buf[0x200];
    FILE *fp;
} challenge;

// gcc baby-file-struct.c -o baby-file-struct
int main(int argc, char **argv) {
  // open /etc/passwd
  challenge.fp = fopen("/etc/passwd", "r");
  
  // buffer overflow
  puts("bof: ");
  read(0, challenge.buf, 0x400);

  // close file
  fclose(challenge.fp);
  return 0;
}


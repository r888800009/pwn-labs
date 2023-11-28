#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buf[0x200];
FILE *fp;

// gcc baby-file-struct.c -o baby-file-struct
int main(int argc, char **argv) {

  // open /etc/passwd
  fp = fopen("/etc/passwd", "r");
  
  // buffer overflow
  puts("bof: ");
  read(0, buf, 0x400);

  // close file
  fclose(fp);
  return 0;
}


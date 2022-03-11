#include <stdio.h>
#include <stdlib.h>
/// gcc -o stack-frame stack-frame.c -fno-stack-protector
int main() {
  long a = 1;
  puts("hello world");
  return 0;
}


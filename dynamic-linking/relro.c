#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 gcc -o norelro relro.c -z norelro -no-pie
 gcc -o lazy_relro relro.c -z lazy -no-pie
*/
int main() {
  char *buf = malloc(0x100);
  memset(buf, 0, 0x100);
  strcpy(buf, "Hello, World!\n");
  printf("%s", buf);

  int a = 0;
  scanf("%d", &a);
  printf("%d\n", a);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>

// gcc fmt_test.c -o fmt_test
int main() {
  int n = 0, n2 = 0;

  printf("12345%n\n", &n);
  printf("n = %d\n", n);

  printf("1234%n\n", &n);
  printf("n = %d\n", n);

  printf("12%n345%n\n", &n, &n2);
  printf("n = %d\n", n);
  printf("n2 = %d\n", n2);

  printf("%12c%n%8c%n\n", 'a', &n, 'b', &n2);
  printf("n = %d\n", n);
  printf("n2 = %d\n", n2);

  printf("%3$12c\n", 'a', 'b', 'c');

  return 0;
}

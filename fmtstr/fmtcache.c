#include <stdio.h>
#include <stdlib.h>

int main() {
  int n1 = 0;

  puts("cache fmt");
  // 你看到的是 register rsi 的值因此是 0
  // printf("1234;%1$d;%2$n;%1$d;\n", n1, &n1);
  // 這看到的是 stack 實際上存在的值
  printf(";%1$s;%1$n;%1$s;\n", &n1);
  // printf("%1$d\n", n1);

  n1 = 0;
  puts("non-cache fmt");
  printf(";%s;%n;%s;\n", &n1, &n1, &n1);
  printf("%1$d\n", n1);
}

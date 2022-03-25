#include <stdio.h>
#include <stdlib.h>

void func2() {
  int64_t local;
  int64_t *rbp = &local + 3;
  printf("%p\n", rbp);  // %10$p
  // 0x98 = 152
  // printf("%152c%8$hhn%10$lln\n"); 第二個 lln 會寫入原本的位置
  // 所以這個情況下是有 cache 發生的
  // 那試試看 non-cache 的情況
  // 前面先塞 7 個 %c 再塞 %hhn 再塞 1 個 %c 再塞 %lln
  // 152-6=146
  printf("%c%c%c%c%c%c%146c%hhn%c%lln");
}

void func1() { func2(); }

int main(int argc, char *argv[]) {
  func1();
  return 0;
}

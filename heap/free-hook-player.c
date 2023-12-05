#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("%p\n", &system);

  char *free_hook_arg = malloc(0x30);
  printf("set free_hook_arg to");
  scanf("%s", free_hook_arg);

  puts("breakpoint here and set free_hook to system");
  free(free_hook_arg);

  return 0;
}

// gcc -g -o free-hook-player free-hook-player.c
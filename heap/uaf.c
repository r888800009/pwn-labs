#include <stdio.h>
#include <stdlib.h>

char my_name[50];

int main() {
  strcpy(my_name, "UAF");
  char *ptr1, *ptr2, *tmp_ptr;

  // malloc
  tmp_ptr = malloc(0x10);
  ptr1 = malloc(0x10);

  // free
  free(tmp_ptr);
  free(ptr1);

  // use-after-free
  ((size_t *)ptr1)[0] = my_name;  // next
  ((size_t *)ptr1)[1] = 0x0;      // key

  tmp_ptr = malloc(0x10);
  ptr2 = malloc(0x10);

  printf("ptr2: %p\n", ptr2);
  printf("my_name: %p\n", my_name);

  return 0;
}

// gcc -o -g uaf uaf.c

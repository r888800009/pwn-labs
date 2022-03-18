#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

// char data[0x1000];
char *data = NULL;

void init() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  srand(time(NULL));

  data = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC,
              MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  memset(data, 0xc3, 0x1000);  // ret
}

void stack_dump() {
  size_t i;
  puts("\nStack Dump:");
  for (i = 0; i < 17; i++) printf("%d: %p\n", i, (&i)[i]);
  puts("Dump End");
}

void read_shellcode() {
  int rand_offset = rand() % (0x300);
  printf("Address: %p\n", data + rand_offset);
  puts("Shellcode:");
  read(0, data, 0x600);
}

// gcc ret2sc.c -o ret2sc -fno-stack-protector -z execstack
int main(int argc, char **argv) {
  char buf[0x8];
  init();
  read_shellcode();

  stack_dump();
  puts("bof: ");
  read(0, buf, 0x30);
  stack_dump();

  return 0;
}


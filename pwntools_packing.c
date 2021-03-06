#include <stdio.h>
#include <stdlib.h>

// gcc pwntools_packing.c -o pwntools_packing
int main(int argc, char **argv) {
  srand(time(NULL));
  unsigned int a, b;

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  for (int i = 0; i < 100; i++) {
    a = rand();

    printf("%u\n", a);

    read(0, &b, sizeof(b));

    if (a != b) {
      printf("%u != %u\n", a, b);
      exit(1);
    }
  }

  system("/bin/sh");
  return 0;
}


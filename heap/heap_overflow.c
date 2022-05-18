#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char id[10];
  char password[0x20];
} user;

int main() {
  char *overflow = malloc(0x20);
  user *u = malloc(sizeof(user));

  strcpy(&u->id, "admin");
  strcpy(&u->password, "strongpassword");

  puts("Enter your password: ");
  gets(overflow);

  if (strncmp(overflow, u->password, strlen(u->password)) == 0) {
    puts("Welcome!");
    system("/bin/bash");
  } else {
    puts("Wrong password!");
  }

  return 0;
}

// gcc -g -o heap_overflow heap_overflow.c


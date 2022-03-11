#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// gcc fork_canary.c -o ./fork_canary
int main(int argc, char **argv) {
  size_t index;
  size_t *i = &index;
  int canary_offset = 0xd;

  // fork()
  pid_t pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  // if child
  if (pid == 0) {
    printf("child canary?");
    scanf("%p", &index);

    if (index == i[canary_offset])
      puts("canary!");
    else
      puts("not canary!");

  } else {
    // if parent
    printf("parent canary: %p\n", i[canary_offset]);
    // wait for child
    int status;
    waitpid(pid, &status, 0);
  }

  char *buf[10];
  gets(buf);
}

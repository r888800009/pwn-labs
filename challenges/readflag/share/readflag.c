#include <seccomp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

const char *author = "r888800009";

int fd, len;
char flag[100];

void load_flag() {
  fd = open("/flag", O_RDONLY);
  len = read(fd, flag, 100);
  close(fd);
}

void init() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  load_flag();

  scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);

  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(close), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0);

  if (seccomp_load(ctx) < 0) {
    perror("seccomp_load");
    exit(1);
  }

  seccomp_release(ctx);
}

void readflag() {
  write(1, "flag: ", 6);
  write(1, flag, len);
}

/*
void test_exec() {
  char *args[] = {"/bin/sh", NULL};
  execve(args[0], args, NULL);
}
*/

int main() {
  char buf[0x20];
  init();
  printf("Return to readflag(): %p\n", readflag);

  scanf("%48s", buf);
  close(STDIN_FILENO);
  // readflag();
  // test_exec();

  return 0;
}

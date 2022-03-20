#include <seccomp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

const char *author = "r888800009";

void init() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);

  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(openat), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(close), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(newfstatat), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(fstat), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(lseek), 0);

  if (seccomp_load(ctx) < 0) {
    perror("seccomp_load");
    exit(1);
  }
}

void readflag() {
  int fd, len;
  char flag[100];
  write(1, "flag: ", 6);
  fd = open("/flag", O_RDONLY);
  len = read(fd, flag, 100);
  write(1, flag, len);
  close(fd);
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

  scanf("%s", buf);

  // readflag();
  // test_exec();

  return 0;
}

#include <seccomp.h>
#include <stdio.h>
#include <stdlib.h>

void init_seccomp(void) {
  scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);
  if (ctx == NULL) {
    perror("seccomp_init");
    exit(EXIT_FAILURE);
  }

  // allow needed syscalls
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(openat), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(close), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(newfstatat), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(fstat), 0);

  // load seccomp rules
  seccomp_load(ctx);

  // destroy seccomp context
  seccomp_release(ctx);

  return;
}

void init() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
}

char data[0x300];

// gcc rop-orw.c -o rop-orw -fno-stack-protector -lseccomp -no-pie
int main(int argc, char **argv) {
  char buf[0x8];
  init();
  init_seccomp();

  // open /etc/passwd
  int fd = open("/etc/passwd", 0);
  close(fd);

  // leak data address
  printf("data: %p\n", data);

  // leak libc address
  printf("puts libc: %p\n", puts);

  // buf overflow
  puts("buf: ");
  read(0, buf, 0x200);
  return 0;
}


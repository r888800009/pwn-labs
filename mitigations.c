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
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(close), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(newfstatat), 0);

  // load seccomp rules
  seccomp_load(ctx);

  // destroy seccomp context
  seccomp_release(ctx);

  return;
}

// gcc mitigations.c -lseccomp -o mitigations -no-pie
int main(int argc, char **argv) {
  init_seccomp();
  char buf[10];
  gets(buf);
  return 0;
}

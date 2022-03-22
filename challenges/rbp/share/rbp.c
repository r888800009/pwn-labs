#include <seccomp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <unistd.h>

const char *author = "r888800009";
int fd, len;
char flag[100];

void init() {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
}

bool check_size(int size) { return (size <= 0 && size > 0x28); }

void vuln() {
  char buf[0x10];
  size_t my_canary = 0x1337;

  puts("[+] Welcome to the rbp challenge!");
  read(0, buf, 0x28);

  if (my_canary != 0x1337) {
    puts("[-] get out of here");
    exit(0);
  }
}

void chal() {
  char buf[0x10];
  printf("[+] what is your name?\n");
  read(0, buf, 0x10);
  printf("[+] hello %s\n", buf);
  vuln();
}

void open_flag() {
  printf("[+] opening flag file\n");
  fd = open("/flag", O_RDONLY);
}

void read_flag() {
  printf("[+] reading flag\n");
  len = read(fd, flag, 100);
  printf("[+] closing flag file\n");
  close(fd);
}

void print_flag() {
  printf("[+] flag: ");
  write(1, flag, len);
}

void sandbox() {
  printf("[+] sandboxing\n");
  scmp_filter_ctx ctx;
  ctx = seccomp_init(SCMP_ACT_KILL);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(close), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0);
  seccomp_load(ctx);
  seccomp_release(ctx);
}

int main() {
  init();
  open_flag();
  sandbox();
  chal();
  return 0;
}

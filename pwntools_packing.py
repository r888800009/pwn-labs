from pwn import *

c = process("./pwntools_packing")

context.log_level = 'debug'

for i in range(100):
    n = int(c.recvline()[:-1])
    c.send(p32(n))

c.interactive()
c.close()

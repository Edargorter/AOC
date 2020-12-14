#!/usr/bin/env python3 
from sys import argv 

if len(argv) < 2:
    filename = "input"
    print("Using input")
else:
    filename = argv[1]

lines = [line.strip() for line in open(filename, 'r').readlines()]
mem = {}

mask = ""
for line in lines:
    a, b, val = line.split(' ')
    if a == "mask":
        mask = val
    else:
        addr = a.split('[')[1][:-1] 
        print("V prev ", val, end=" ")
        v = bin(int(val.rstrip()))[2:]
        v = list('0'*(36 - len(v)) + v)
        for i in range(len(mask)):
            c = mask[35 - i]
            if c != 'X':
                v[35 - i] = c
        v = int(''.join(v), 2)
        print("V next", v)
        mem[addr] = v

s = 0
for key in mem:
    s += mem[key]

print("PART 1: ", s)

#PART 2

mem.clear()

for line in lines:
    a, b, val = line.split(' ')
    if a == "mask":
        mask = val
    else:
        addr = a.split('[')[1][:-1] 
        v = int(val.rstrip())
        ad = bin(int(addr.rstrip()))[2:]
        ad = list('0'*(36 - len(ad)) + ad)
        indices = []
        for i in range(len(mask)):
            c = mask[35 - i]
            if c != '0':
                ad[35 - i] = c
                if c == 'X':
                    indices.append(35 - i)
        indices.reverse()
        l = len(indices)
        addrs = []
        for n in range(2 ** l):
            bn = bin(n)[2:]
            bn = '0'*(l - len(bn)) + bn
            for j in range(l):
                tmp = ad
                tmp[indices[j]] = bn[j]
                tmp = ''.join([str(k) for k in tmp])
            addrs.append(tmp)

        for add in addrs:
            mem[add] = v

s = 0    
for key in mem:
    s += mem[key]
    
print("PART 2: ", s)

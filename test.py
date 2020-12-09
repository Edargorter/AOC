import os

w = list("aaqaaaa")
alp = [chr(i) for i in range(97,97+26)]
alp += [str(i) for i in range(10)]

found = [2]

while 1:
    for c in alp:
        for i in range(len(w)):
            if i in found:
                continue
            w[i] = c
        print(''.join(w))
        os.system("echo {} | xclip -sel clip".format(''.join(w)))
        input()

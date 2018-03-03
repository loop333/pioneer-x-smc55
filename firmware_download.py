#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
sock.connect(('192.168.1.7', 9000))
sock.settimeout(5)

# cancel previous xmodem download
sock.send(chr(0x18)*20)

sock.send('\r')

# wait prompt
s = ''
while 1:
    data = sock.recv(1024)
    s = s + data
    if 'sds://>' in s:
        print('found prompt')
        break

# or for time saving fburn rd 0 0x00000000 0x01440000
sock.send('fburn rd 0 0x00000000 0x08000000\r')

# wait xmodem
s = ''
while 1:
    data = sock.recv(1024)
    s = s + data
    if 'Start xmodem now!' + chr(0x0A) in s:
        print('start xmodem')
        break

sock.send('C')

f = open('firmware.bin', 'wb')

s = ''
addr = 0
while 1:
    data = sock.recv(1024)
    s = s + data
    if s[0] == chr(0x04):
        print('found EOT')
        sock.send(chr(0x06))
        break
    if len(s) == 133:
        if addr % 0x20000 == 0:
            print('{:08x}'.format(addr))
        sock.send(chr(0x06))
        f.write(s[3:-2])
        s = ''
        addr = addr + 128

f.close()

sock.close()

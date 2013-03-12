import socket
import select
import sys

try:
    listenfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error:
    print 'Failed to create socket'
    sys.exit()

print 'Socket Created'

host = '127.0.0.1'
port = 9000

listenfd.bind((host, port))
listenfd.listen(5)
#conn, addr = listenfd.accept()
input = [listenfd, sys.stdin]
running = 1

while running:
    inputready,outputready,exceptready = select.select(input,[],[])

    for s in inputready:

        if s == listenfd:
            client, address = listenfd.accept()
            input.append(client)
        elif s == sys.stdin:
            junk = sys.stdin.readline()
            running = 0
        else:
            data = s.recv(1024)
            if data:
                print data
                s.send(data)
            else:
                s.close()
                input.remove(s)
listenfd.close()
"""
while 1:
    data = conn.recv(1024)
    print data
    if not data: break
    conn.sendall(data)

conn.close()

"""



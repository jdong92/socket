import socket
import select
import sys

try:
    listenfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error:
    print 'Failed to create socket'
    sys.exit()

print 'manage.py running'

host = '127.0.0.1'
port = 9050
maxline = 4096

listenfd.bind((host, port))
listenfd.listen(5)
input = [listenfd, sys.stdin]
running = 1

while running:

    inputready, outputready, exceptready = select.select(input,[],[])

    for s in inputready:

        if s == listenfd:
            client, address = listenfd.accept()
            input.append(client)
        elif s == sys.stdin:
            quit = sys.stdin.readline()
            running = 0
        else:
            data = s.recv(maxline)
            if (data == '#REPORT'):
                print 'Report'
            if data:
                print data
                s.send(data)
            else:
                s.close()
                input.remove(s)

listenfd.close()


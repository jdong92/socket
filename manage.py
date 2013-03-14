import socket
import select
import sys
import re

try:
    listenfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error:
    print 'Failed to create socket'
    sys.exit()

print 'manage.py running'

host = '127.0.0.1'
port = 9050
maxline = 4096
list_of_num = []

listenfd.bind((host, port))
listenfd.listen(10)
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
            match = re.search(('[0-9]+'),data)
            if (data[0:2] == 'C#'):
                msg = data[2:len(data)] + '#'
                list_of_num.append(msg)
            if (data == 'REPORT'):
                for i in list_of_num:
                    s.send(i)
            if match:
                s.send(match.group(0))
            else:
                s.close()
                input.remove(s)

listenfd.close()


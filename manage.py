import socket
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
conn, addr = listenfd.accept()

while 1:
    data = conn.recv(1024)
    print data
    if not data: break
    conn.sendall(data)

conn.close()



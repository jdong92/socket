import socket
import sys

HOST = '127.0.0.1'
PORT = 9050

try:
    listenfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error:
    print 'Failed to create socket'
    sys.exit()

print 'report.py running'

listenfd.bind((HOST, PORT))
listenfd.listen(1)

conn, addr = listenfd.accept()

print 'Connected by', addr

while 1:
    data = conn.recv(1024)
    if not data: break
    conn.sendall(data)
conn.close()

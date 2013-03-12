import socket
import sys

HOST = '127.0.0.1'
PORT = 9000

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
"""
try:
    s.bind((HOST, PORT))
except socket.error, msg:
    print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.ext()

print 'Socket bind complete'

"""

s.connect((HOST, PORT))
print 'Socket connected to port' , PORT

reply = s.recv(4096)

print reply

import socket
import sys

HOST = '127.0.0.1'
PORT = 9050

try:
    report = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error:
    print 'Failed to create socket'
    sys.exit()

report.connect((HOST, PORT))
print 'report.py running'

#listenfd.bind((HOST, PORT))
#listenfd.listen(1)

#conn, addr = listenfd.accept()

#print 'Connected by', addr

report.send('#REPORT')
    #data = report.recv(1024)
    #print data

report.close()

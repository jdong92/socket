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

if len(sys.argv) > 2:
    print 'Usage: report.py [ip-address] [-k]'
    sys.exit()
if (len(sys.argv) == 2) and (sys.argv[1] == '-k'):
    print '-k option invoked'
    report.send('KILL')
else:
    print 'report.py running'
    report.send('REPORT')
    data = report.recv(4096)
    perfect_num = data.split('#')
    for i in perfect_num:
        print i


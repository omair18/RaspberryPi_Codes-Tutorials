import os
import fcntl

f = open ('/dev/hidraw0', 'rb')
while 1:
	buffer = f.read (8)
	for c in buffer:
		print str(c)

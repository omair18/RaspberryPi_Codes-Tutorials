#!/usr/bin/python
#sudo pip install pyOpenSSL==0.13

from subprocess import *
from time import sleep, strftime
from datetime import datetime
import threading
import time
import gspread
import json
from oauth2client.client import SignedJwtAssertionCredentials

cmd = "nmcli dev | grep cdma | awk {'print $3'}"
connected = "connected"
disconnected = "disconnected"
json_key = json.load(open('test2-5820d57a1857.json'))
scope = ['https://spreadsheets.google.com/feeds']
credentials = SignedJwtAssertionCredentials(json_key['client_email'], json_key['private_key'], scope)
def check_connection(cmd):

	cell_str = 'A'
	cell_id = 1
	gc = gspread.authorize(credentials)
	wks = gc.open("test").sheet1
	wks.update_acell('A10',"1st time login DONE")
	print "1st time login DONE"
	while 1:
		p = Popen(cmd, shell=True, stdout=PIPE)
		output = p.communicate()[0]
		print output
		if output == connected:
			print connected
		elif output == disconnected:
			print disconnected
			print "Should reconnect again and login in gmail"
		cell = cell_str + str(cell_id)
		cell_id = cell_id + 1
		wks.update_acell(cell,"1st time login DONE")
		print cell
                sleep(5)

t = threading.Thread(target=check_connection, args=(cmd,))
t.start()
print "thread has started.. rest of task is here"

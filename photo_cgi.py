#!/usr/bin/env python
import subprocess
print "Content-type: text/html"
print "<title>Picture taking CGI</title>"
print "<p>I'm going to upload the picture!</p>"
subprocess.call(['/home/pi/smile.sh'])

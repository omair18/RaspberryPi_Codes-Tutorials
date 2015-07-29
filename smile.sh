#!/bin/sh
filename=$(date +"%m-%d-%y|||%H%M%S")
fswebcam -r 640*480 -d /dev/video0 $filename.jpg

ffserver -f /root/ffserver.conf & ffmpeg -v 2 -r 5 -s 640x480 -f video4linux2 -i /dev/video1 http://localhost:8090/webcam.ffm

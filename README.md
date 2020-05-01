# gstw
C++ Wrapper for GStreamer

usefor memory leaks:
valgrind --leak-check=yes --suppressions=./gst.supp ./tutorial1

install:
apt-get install libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio

video & audio:
apt-get install libgstreamer-plugins-base1.0-dev

rtsp
sudo apt-get install libgstrtspserver-1.0-dev gstreamer1.0-rtsp
rtsp sample:
https://github.com/GStreamer/gst-rtsp-server/blob/master/examples/test-launch.c

dump dot file
https://embeddedartistry.com/blog/2018/02/22/generating-gstreamer-pipeline-graphs/
dump param during cli invoke:
GST_DEBUG_DUMP_DOT_DIR=/tmp ./myapp
(e.g.) to pdf:
dot -Tpdf result.dot > result.pdf

cmake kit path
https://vector-of-bool.github.io/docs/vscode-cmake-tools/kits.html

JETSON
udp example
    on jetson
    gst-launch-1.0 souphttpsrc location=http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4 ! qtdemux ! queue ! h264parse ! nvv4l2decoder ! 'video/x-raw(memory:NVMM), width=(int)1280, height=(int)720, format=(string)NV12, framerate=(fraction)24/1' ! nvv4l2h264enc ! rtph264pay ! udpsink host=192.168.1.50 port=5000

    on host:
    gst-launch-1.0 udpsrc port=5000 ! application/x-rtp ! rtph264depay ! decodebin ! videoconvert ! autovideosink
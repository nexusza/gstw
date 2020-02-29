# gstw
C++ Wrapper for GStreamer

usefor memory leaks:
valgrind --leak-check=yes --suppressions=./gst.supp ./tutorial1

install:
apt-get install libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio

video & audio:
apt-get install libgstreamer-plugins-base1.0-dev

dump dot file
https://embeddedartistry.com/blog/2018/02/22/generating-gstreamer-pipeline-graphs/
dump param during cli invoke:
GST_DEBUG_DUMP_DOT_DIR=/tmp ./myapp
(e.g.) to pdf:
dot -Tpdf result.dot > result.pdf
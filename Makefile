compile:
	g++ main.cpp -o GIFFER  `pkg-config --cflags --libs opencv` -I/usr/local/include/opencv4

compile:
	g++ main.cpp -o GIFFER `pkg-config --cflags --libs opencv` -lpthread
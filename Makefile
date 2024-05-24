detect: detect.c
	gcc -o detect detect.c `pkg-config --cflags --libs opencv`
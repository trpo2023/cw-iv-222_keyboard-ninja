ninja_interface: ninja_interface.c
		gcc -o ninja_interface ninja_interface.c `pkg-config --cflags --libs gtk+-3.0`
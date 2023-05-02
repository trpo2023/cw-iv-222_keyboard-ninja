new_interface: new_interface.c
		gcc -o new_interface new_interface.c `pkg-config --cflags --libs gtk+-3.0`
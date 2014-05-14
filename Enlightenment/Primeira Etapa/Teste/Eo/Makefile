

all: 
	gcc -o main_01 main_01.c simple_simple.c simple_mixin.c simple_interface.c `pkg-config --libs --cflags eo`
	gcc -o main_02 main_02.c simple_simple.c simple_mixin.c simple_interface.c `pkg-config --libs --cflags eo`

clean:
	rm -f main_01 main_02 *~

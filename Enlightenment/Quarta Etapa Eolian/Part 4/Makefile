
CFLAGS=`pkg-config --cflags eo,eo-cxx,eina-cxx` -DEFL_BETA_API_SUPPORT -I.
LDFLAGS=`pkg-config --libs eo,eo-cxx,eina-cxx` -pthread 

compile: interface.o simple.o
	g++ ${CFLAGS} ${LDFLAGS} -o main main.cc simple.o interface.o -std=c++11 -leo

all: 
	/opt/e/dev/bin/eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa/Part 3/" -I/opt/e/dev/share/eolian/include/eo-1/ --gc -o simple.eo.c simple.eo 
	/opt/e/dev/bin/eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa/Part 3/" -I/opt/e/dev/share/eolian/include/eo-1/ --gh -o simple.eo.h simple.eo 
	/opt/e/dev/bin/eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa/Part 3/" -I/opt/e/dev/share/eolian/include/eo-1/ --gh -o interface.eo.h interface.eo 
	/opt/e/dev/bin/eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa/Part 3/" -I/opt/e/dev/share/eolian/include/eo-1/ --gc -o interface.eo.c interface.eo 
	/opt/e/dev/bin/eolian_cxx -I"/home/luciana/Public/Enlightenment/Quarta Etapa/Part 3/" -I/opt/e/dev/share/eolian/include/eo-1/ -I./simple.eo -o simple.eo.hh
	/opt/e/dev/bin/eolian_cxx -I"/home/luciana/Public/Enlightenment/Quarta Etapa/Part 3/" -I/opt/e/dev/share/eolian/include/eo-1/ -I./interface.eo -o interface.eo.hh 

	make compile
#gcc -DEFL_BETA_API_SUPPORT -o main main.c simple.c interface.c `pkg-config --cflags --libs eo,eo-cxx` -pthread

clean:
	rm *.hh *.o *.eo.c *.eo.h

.PHONY: all clean

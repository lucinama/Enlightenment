
CFLAGS=`pkg-config --cflags eo eo-cxx eina-cxx` -DEFL_BETA_API_SUPPORT -I.
LDFLAGS=`pkg-config --libs eo eo-cxx eina-cxx` -pthread 

all: 
	eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa/Part 1/" -I/home/luciana/Enlightenment/local/share/eolian/include/eo-1/ --gc -o eolian_1.eo.c eolian_1.eo 
	eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa/Part 1/" -I/home/luciana/Enlightenment/local/share/eolian/include/eo-1/ --gh -o eolian_1.eo.h eolian_1.eo
	gcc ${CFLAGS} -o main main.cc eolian_eo.c ${LDFLAGS}
	which eolian_gen

clean:
	rm -f *~ *.eo.c *.eo.h main

.PHONY: all clean

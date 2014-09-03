
CFLAGS=`pkg-config --cflags eo eo-cxx eina-cxx` -DEFL_BETA_API_SUPPORT -I.
LDFLAGS=`pkg-config --libs eo eo-cxx eina-cxx` -pthread 

all: 
	eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa Eolian/Eo Events/" -I/home/luciana/Enlightenment/local/share/eolian/include/eo-1/ --gc -o simple.eo.c simple.eo 
	eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa Eolian/Eo Events/" -I/home/luciana/Enlightenment/local/share/eolian/include/eo-1/ --gh -o simple.eo.h simple.eo
	gcc ${CFLAGS} -o main main.c simple.c ${LDFLAGS}
	which eolian_gen

clean:
	rm -f *~ *.eo.c *.eo.h main

.PHONY: all clean

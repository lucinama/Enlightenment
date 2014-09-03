
CFLAGS=`pkg-config --cflags eo eo-cxx eina-cxx` -DEFL_BETA_API_SUPPORT -I.
LDFLAGS=`pkg-config --libs eo eo-cxx eina-cxx` -pthread 

all: 
	eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa Eolian/Part 1/Linguagem Atualizada/" -I/home/luciana/Enlightenment/local/share/eolian/include/eo-1/ --gc -o eolian_1_novo.eo.c eolian_1_novo.eo 
	eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa Eolian/Part 1/Linguagem Atualizada/" -I/home/luciana/Enlightenment/local/share/eolian/include/eo-1/ --gh -o eolian_1_novo.eo.h eolian_1_novo.eo
	/opt/e/dev/bin/eolian_cxx -I"/home/luciana/Public/Enlightenment/Quarta Etapa Eolian/Part 1/Linguagem Atualizada/" -I/opt/e/dev/share/eolian/include/eo-1/ -I./eolian_1_novo.eo -o eolian_1_novo.eo.hh 
	gcc ${CFLAGS} -o main main.cc eolian_eo_novo.c ${LDFLAGS}
	which eolian_gen

clean:
	rm -f *~ *.eo.c *.eo.h main

.PHONY: all clean

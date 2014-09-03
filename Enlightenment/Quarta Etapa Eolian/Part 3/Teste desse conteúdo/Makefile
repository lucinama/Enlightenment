
CFLAGS=`pkg-config --cflags eo,eo-cxx,eina-cxx` -DEFL_BETA_API_SUPPORT -I.
LDFLAGS=`pkg-config --libs eo,eo-cxx,eina-cxx` -pthread 

all: 
	which eolian_gen
	eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa Eolian/Part 3/Teste desse conteúdo/" -I/home/luciana/Enlightenment/local/share/eolian/include/eo-1/ --gc -o simple.eo.c simple.eo 
	eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa Eolian/Part 3/Teste desse conteúdo/" -I/home/luciana/Enlightenment/local/share/eolian/include/eo-1/ --gh -o simple.eo.h simple.eo
	eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa Eolian/Part 3/Teste desse conteúdo/" -I/opt/e/dev/share/eolian/include/eo-1/ --gh -o interface.eo.h interface.eo 
	eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa Eolian/Part 3/Teste desse conteúdo/" -I/home/luciana/Enlightenment/local/share/eolian/include/eo-1/ --gc -o interface.eo.c interface.eo 
	eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa Eolian/Part 3/Teste desse conteúdo/" -I/home/luciana/Enlightenment/local/share/eolian/include/eo-1/ --gc -o mixin.eo.c mixin.eo
	eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa Eolian/Part 3/Teste desse conteúdo/" -I/home/luciana/Enlightenment/local/share/eolian/include/eo-1/ --gh -o mixin.eo.h mixin.eo
	eolian_cxx -I"/home/luciana/Public/Enlightenment/Quarta Etapa Eolian/Part 3/Teste desse conteúdo/" -I/home/luciana/Enlightenment/local/share/eolian/include/eo-1/ -I./simple.eo -o simple.eo.hh
	eolian_cxx -I"/home/luciana/Public/Enlightenment/Quarta Etapa Eolian/Part 3/Teste desse conteúdo/" -I/home/luciana/Enlightenment/local/share/eolian/include/eo-1/ -I./interface.eo -o interface.eo.hh 
	eolian_cxx -I"/home/luciana/Public/Enlightenment/Quarta Etapa Eolian/Part 3/Teste desse conteúdo/" -I/home/luciana/Enlightenment/local/share/eolian/include/eo-1/ -I./mixin.eo -o mixin.eo.hh 
	g++ ${CFLAGS} -o main main.cc simple.c mixin.c interface.c ${LDFLAGS} -std=c++11
	which eolian_gen

clean:
	rm f *~ *.hh *.o *.eo.c *.eo.h main

.PHONY: all clean

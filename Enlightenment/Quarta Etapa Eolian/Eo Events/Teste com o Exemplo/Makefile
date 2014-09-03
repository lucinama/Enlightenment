
CFLAGS=`pkg-config --cflags eo,eo-cxx,eina-cxx` -DEFL_BETA_API_SUPPORT -I.
LDFLAGS=`pkg-config --libs eo,eo-cxx,eina-cxx` -pthread 

compile: simple.o
	g++ ${CFLAGS} ${LDFLAGS} -o main main.c simple.o

all: 
	/opt/e/dev/bin/eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa/Eo Events/Teste com o Exemplo/" -I/opt/e/dev/share/eolian/include/eo-1/ --gc -o simple.eo.c simple.eo 
	/opt/e/dev/bin/eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa/Eo Events/Teste com o Exemplo/" -I/opt/e/dev/share/eolian/include/eo-1/ --gh -o simple.eo.h simple.eo 

	make compile
#gcc -DEFL_BETA_API_SUPPORT -o main main.c simple.c `pkg-config --cflags --libs eo,eo-cxx` -pthread

clean:
	rm *.hh *.o *.eo.c *.eo.h

.PHONY: all clean

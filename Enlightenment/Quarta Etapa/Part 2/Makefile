all:
	/opt/e/dev/bin/eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa/Part 2/" -I/opt/e/dev/share/eolian/include/eo-1/ --gc -o simple.eo.c simple.eo 
	/opt/e/dev/bin/eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa/Part 2/" -I/opt/e/dev/share/eolian/include/eo-1/ --gh -o simple.eo.h simple.eo 
	/opt/e/dev/bin/eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa/Part 2/" -I/opt/e/dev/share/eolian/include/eo-1/ --gh -o interface.eo.h interface.eo 
	/opt/e/dev/bin/eolian_gen --eo -I"/home/luciana/Public/Enlightenment/Quarta Etapa/Part 2/" -I/opt/e/dev/share/eolian/include/eo-1/ --gc -o interface.eo.c interface.eo 
	gcc -DEFL_BETA_API_SUPPORT -o main main.c simple.c interface.c `pkg-config --cflags --libs eo` -pthread

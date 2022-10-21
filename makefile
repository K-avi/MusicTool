
all:
	gcc main.c scalegen.c init.c scaleloop.c harmo.c misc.c parsing.c user_info.c globals.c  copy.c -o MusicTool


clean:
		rm -f MusicTool

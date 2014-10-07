all:
	gcc -o rosh main.c env.c input.c

debug:
	gcc -g -o rosh main.c env.c input.c
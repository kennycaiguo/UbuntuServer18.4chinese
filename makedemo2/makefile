CC=gcc

all:getmax getmin
getmax: getmax_main.c getmax.o
	$(CC) getmax_main.c getmax.o -o getmax
getmin:getmin_main.c getmin.o
	$(CC) getmin_main.c getmin.o -o getmin
getmax.o:getmax.c
	$(CC) -c getmax.c -o getmax.o
getmin.o:getmin.c
	$(CC) -c getmin.c -o getmin.o
clean:
	rm *.o getmax getmin

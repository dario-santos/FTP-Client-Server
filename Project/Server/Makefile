CC=cc
FLAGS=-c -Wall
LIBS=-lm -lpthread
OBS=source_server.o msg.o fila.o server.o connection.o ftp.o send_struct.o lock.o

all : source_server 


msg.o : msg.h msg.c
	$(CC) $(FLAGS) msg.c

fila.o : fila.h fila.c
	$(CC) $(FLAGS) fila.c

ftp.o : ftp.h fifo.h ftp.c
	$(CC) $(FLAGS) ftp.c

lock.o : lock.h lock.c
	$(CC) $(FLAGS) lock.c

send_struct.o : send_struct.h lock.h send_struct.c
	$(CC) $(FLAGS) send_struct.c

connection.o : fifo.h connection.h connection.c
	$(CC) $(FLAGS) connection.c

source_server.o : server.h fifo.h source_server.c
	$(CC) $(FLAGS) source_server.c

server.o : send_struct.h server.h ftp.h connection.h lock.h fila.h fifo.h server.c
	$(CC) $(FLAGS) server.c


source_server : $(OBS)
	$(CC)  -o source_server  $(OBS) $(LIBS)

clean limpar:
	rm -f *.o
	echo "Limpeza dos ficheiros exectuaveis, objectos e gedit tralha"
	
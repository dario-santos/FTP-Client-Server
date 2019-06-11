CC=cc
FLAGS=-c -Wall
LIBS=-lm
OBS=client.o menu.o connection.o request_struct.o ftp.o

all : client

client.o : fifo.h menu.h client.c
	$(CC) $(FLAGS) client.c

connection.o : fifo.h connection.h connection.c
	$(CC) $(FLAGS) connection.c

request_struct.o : request_struct.h request_struct.c
	$(CC) $(FLAGS) request_struct.c

ftp.o : ftp.h ftp.c
	$(CC) $(FLAGS) ftp.c

menu.o : fifo.h ftp.h menu.h request_struct.h menu.c
	$(CC) $(FLAGS) menu.c

client : $(OBS)
	$(CC)  -o client  $(OBS) $(LIBS)

clean limpar:
	rm -f *.o
	echo "Limpeza dos ficheiros exectuaveis, objectos e gedit tralha"

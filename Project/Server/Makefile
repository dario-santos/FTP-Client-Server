CC=cc
FLAGS=-c -Wall
LIBS=-lm -lpthread
OBS=msg.o fila.o source_server.o ftp.o lock.o server.o connection.o send_struct.o

all : source_server 


msg.o : msg.h msg.c
	$(CC) $(FLAGS) msg.c

fila.o : fila.h fila.c
	$(CC) $(FLAGS) fila.c

ftp.o : ftp.h ftp.c
	$(CC) $(FLAGS) ftp.c

lock.o : lock.h lock.c
	$(CC) $(FLAGS) lock.c

send_struct.o : send_struct.h lock.h send_struct.c
	$(CC) $(FLAGS) send_struct.c

connection.o : connection.h connection.c
	$(CC) $(FLAGS) connection.c

source_server.o : server.h MainConnection.h source_server.c
	$(CC) $(FLAGS) source_server.c

server.o : send_struct.h connection.h server.h fila.h MainConnection.h lock.h ftp.h server.c
	$(CC) $(FLAGS) server.c


source_server : $(OBS)
	$(CC)  -o source_server  $(OBS) $(LIBS)

clean limpar:
	rm -f *.o
	echo "Limpeza dos ficheiros exectuaveis, objectos e gedit tralha"
	
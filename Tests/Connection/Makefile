CC=cc
FLAGS=-c -Wall
LIBS=-lm
OBS=connection_teste.o connection.o

all : connection_teste

connection_teste.o : connection.h connection_teste.c
	$(CC) $(FLAGS) connection_teste.c

connection.o : connection.h connection.c
	$(CC) $(FLAGS) connection.c

connection_teste : $(OBS)
	$(CC)  -o connection_teste  $(OBS) $(LIBS)

clean limpar:
	rm -f *.o
	echo "Limpeza dos ficheiros exectuaveis, objectos e gedit tralha"


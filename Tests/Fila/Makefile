CC=cc
FLAGS=-c -Wall
LIBS=-lm
OBS=fila_teste.o msg.o fila.o

all : fila_teste

fila_teste.o : fila.h fila_teste.c
	$(CC) $(FLAGS) fila_teste.c

msg.o : msg.h msg.c
	$(CC) $(FLAGS) msg.c

fila.o : fila.h fila.c
	$(CC) $(FLAGS) fila.c

fila_teste : $(OBS)
	$(CC)  -o fila_teste  $(OBS) $(LIBS)

clean limpar:
	rm -f *.o
	echo "Limpeza dos ficheiros exectuaveis, objectos e gedit tralha"


CC=cc
FLAGS=-c -Wall
LIBS=-lm
OBS=msg_teste.o msg.o

all : msg_teste 

msg_teste.o : msg.h msg_teste.c
	$(CC) $(FLAGS) msg_teste.c

msg.o : msg.h msg.c
	$(CC) $(FLAGS) msg.c

msg_teste : $(OBS)
	$(CC)  -o msg_teste  $(OBS) $(LIBS)

clean limpar:
	rm -f *.o
	echo "Limpeza dos ficheiros exectuaveis, objectos e gedit tralha"

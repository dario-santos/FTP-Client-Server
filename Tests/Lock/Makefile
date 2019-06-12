CC=cc
FLAGS=-c -Wall
LIBS=-lm -lpthread
OBS=lock_teste.o lock.o

all : lock_teste


lock.o : lock.h lock.c
	$(CC) $(FLAGS) lock.c

lock_teste.o : lock.h lock_teste.c
	$(CC) $(FLAGS) lock_teste.c


lock_teste : $(OBS)
	$(CC)  -o lock_teste $(OBS) $(LIBS)


clean limpar:
	rm -f *.o
	echo "Limpeza dos ficheiros exectuaveis, objectos e gedit tralha"
	
GCC_FLAGS = -Wall -g

all : voc-quizz

wordDB.o : wordDB.c wordDB.h
	gcc ${GCC_FLAGS} -c wordDB.c

question.o : question.c question.h wordDB.h
	gcc ${GCC_FLAGS} -c question.c

main.o : main.c wordDB.h question.h
	gcc ${GCC_FLAGS} -c main.c

voc-quizz : main.o question.o wordDB.o
	gcc ${GCC_FLAGS} -o voc-quizz main.o question.o wordDB.o

clean :
	rm *.o voc-quizz

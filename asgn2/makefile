PROG = quiz  
CC = g++  
FLAGS = -Wall -g
OBJS = quiz.o question.o main.o
   
quiz: $(OBJS)  
	$(CC) $(FLAGS) -o $(PROG) $(OBJS)
   
quiz.o: quiz.cpp quiz.h  
	$(CC) $(FLAGS) -c quiz.cpp  
   
question.o: question.cpp question.h  
	$(CC) $(FLAGS)  -c question.cpp  

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp
   
clean:  
	rm $(PROG) $(OBJS)

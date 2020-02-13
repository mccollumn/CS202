PROG = quiz3
CC = g++  
FLAGS = -Wall -g -std=c++11
OBJS = quiz.o question.o questiontf.o questionmc.o questionsa.o main.o
   
quiz: $(OBJS)  
	$(CC) $(FLAGS) -o $(PROG) $(OBJS)
   
quiz.o: quiz.cpp quiz.h  
	$(CC) $(FLAGS) -c quiz.cpp  
   
question.o: question.cpp question.h  
	$(CC) $(FLAGS)  -c question.cpp  

questiontf.o: questiontf.cpp questiontf.h  
	$(CC) $(FLAGS)  -c questiontf.cpp  

questionmc.o: questionmc.cpp questionmc.h  
	$(CC) $(FLAGS)  -c questionmc.cpp  

questionsa.o: questionsa.cpp questionsa.h  
	$(CC) $(FLAGS)  -c questionsa.cpp  

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp
   
clean:  
	rm $(PROG) $(OBJS)

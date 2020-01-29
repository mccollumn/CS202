# builds hello program from multiple source files  
   
PROG = stringTest  
CC = g++  
FLAGS = -Wall -g
OBJS = mystring.o stringTest.o  
   
stringTest: $(OBJS)  
	$(CC) $(FLAGS) -o $(PROG) $(OBJS)
   
stringTest.o: stringTest.cpp mystring.h  
	$(CC) $(FLAGS) -c stringTest.cpp  
   
mystring.o: mystring.cpp mystring.h  
	$(CC) $(FLAGS)  -c mystring.cpp  
   
clean:  
	rm $(PROG) $(OBJS)

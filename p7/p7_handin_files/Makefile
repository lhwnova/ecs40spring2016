containers.out : container.o linkedlist.o main.o sortedlinkedlist.o sortedvector.o vector.o  
	g++ -ansi -Wall -g -o containers.out container.o linkedlist.o main.o sortedlinkedlist.o sortedvector.o vector.o  

container.o : container.cpp container.h 
	g++ -ansi -Wall -g -c container.cpp

linkedlist.o : linkedlist.cpp linkedlist.h 
	g++ -ansi -Wall -g -c linkedlist.cpp

main.o : main.cpp container.h vector.h sortedvector.h linkedlist.h sortedlinkedlist.h 
	g++ -ansi -Wall -g -c main.cpp

sortedlinkedlist.o : sortedlinkedlist.cpp sortedlinkedlist.h 
	g++ -ansi -Wall -g -c sortedlinkedlist.cpp

sortedvector.o : sortedvector.cpp sortedvector.h 
	g++ -ansi -Wall -g -c sortedvector.cpp

vector.o : vector.cpp vector.h sortedvector.h 
	g++ -ansi -Wall -g -c vector.cpp

clean : 
	rm -f containers.out container.o  linkedlist.o  main.o  sortedlinkedlist.o  sortedvector.o  vector.o   

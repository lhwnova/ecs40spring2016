airline.out : flight.o main.o plane.o utilities.o  
	g++ -g -ansi -Wall -o airline.out flight.o main.o plane.o utilities.o  

flight.o : flight.cpp flight.h 
	g++ -g -ansi -Wall -c flight.cpp

main.o : main.cpp flight.h utilities.h 
	g++ -g -ansi -Wall -c main.cpp

plane.o : plane.cpp plane.h utilities.h 
	g++ -g -ansi -Wall -c plane.cpp

utilities.o : utilities.cpp utilities.h 
	g++ -g -ansi -Wall -c utilities.cpp

clean : 
	rm -f airline.out flight.o  main.o  plane.o  utilities.o   

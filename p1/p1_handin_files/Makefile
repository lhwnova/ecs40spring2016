all : airline.out

clean:
	rm *.o
	rm airline.out


airline.out: main.o flight.o plane.o utilities.o
	g++ -Wall -g main.o flight.o plane.o utilities.o -o airline.out


main.o: main.cpp
	g++ -Wall -g -c main.cpp 


utilities.o: utilities.cpp
	g++ -Wall -g -c utilities.cpp


plane.o: plane.cpp
	g++ -Wall -g -c plane.cpp


flight.o: flight.cpp
	g++ -Wall -g -c flight.cpp



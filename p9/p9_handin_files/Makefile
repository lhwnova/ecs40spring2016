all: BST.out BST2.out

BST.out : main.o
	g++ -DNDEBUG -ansi -Wall -g -o BST.out main.o

BST2.out: main2.o
	g++ -ansi -Wall -g -o BST2.out main2.o

main.o : main.cpp BinarySearchTree.h BinarySearchTree.cpp
	g++ -DNDEBUG -ansi -Wall -g -c main.cpp -o main.o

main2.o: main.cpp BinarySearchTree.h BinarySearchTree.cpp
	g++ -ansi -Wall -g -c main.cpp -o main2.o

clean : 
	rm -f BST2.out BST.out main2.o main.o 

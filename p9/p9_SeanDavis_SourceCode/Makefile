all: BST.out BST2.out

BST.out : main.o   
	g++ -ansi -Wall -o BST.out main.o

BST2.out : main2.o
	g++ -ansi -Wall -o BST2.out main2.o

main.o : main.cpp BinarySearchTree.h BinarySearchTree.cpp
	g++ -ansi -Wall -DNDEBUG -c main.cpp

main2.o : main.cpp BinarySearchTree.h BinarySearchTree.cpp
	g++ -ansi -Wall -c main.cpp -o main2.o

clean : 
	rm -f BST.out BST2.out main.o main2.o  

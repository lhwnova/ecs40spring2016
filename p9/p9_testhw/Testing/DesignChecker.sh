#!  /bin/bash

testerDirectory="/home/ssdavis/40/p8/Testing"

if [ $# -ne 1 ]; then
  >&2 echo "usage DesignChecker.sh: $testerDirectory/DesignChecker.sh scrabble_directory "
  exit
fi

if [[ $1 =~ Testing ]]; then # Use from this directory is not allowed
  >&2 echo "You may not use Testing as your own source directory!"
  exit
fi

cd $1

rm -f designResults.txt *.o
designError=0
dos2unix *.cpp *.h &> /dev/null


if grep "/\*" BinarySearchTree.cpp  &> /dev/null ; then
  cat temp >> designResults.txt
  echo 'Fatal design error: "/*" found. ' >> designResults.txt
  (( ++designError ))
fi

#if egrep "[^a-zA-Z][0-9]+" BinarySearchTree.cpp  | grep -v "const *int" | egrep -v "( 0| 1[^0-9]|cout)" &> /dev/null  ; then
#  echo 'Fatal design error: Constant other than 0 and 1 found outside of static const.'  >> designResults.txt
#  egrep "[^a-zA-Z][0-9]+" BinarySearchTree.cpp  | grep -v "const *int" | egrep -v "( 0| 1[^0-9]|cout)" >> designResults.txt
#  (( ++ designError ))
#fi  

if [[ `awk '/#include/, /^{/' BinarySearchTree.cpp  | egrep -v "\(|\)|const|typedef" | egrep "(void|int|char|double|float)" | wc -l ` -ne 0 ]] ; then
 echo 'Fatal design error: "Global variable found above first function/class in a file.'  >> designResults.txt
awk '/#include/, /^{/' *.cpp *.h | egrep -v "\(|\)|const" | egrep "(void|int|char|double|float)" >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/^}/, /^{/' BinarySearchTree.cpp  | egrep -v "\(|\)|^}|const|typedef" | egrep "(void|int|char|double|float)" | wc -l ` -ne 0 ]] ; then
 echo 'Fatal design error: "Global variable found between functions in a file.'  >> designResults.txt
awk '/^}/, /^{/' *.cpp *.h | egrep -v "\(|\)|^}|const" | egrep "(void|int|char|double|float)" >> designResults.txt
  (( ++ designError ))
fi

if grep "goto" *.cpp *.h  &> /dev/null ; then
  echo 'Fatal design error: "goto" found in files.'  >> designResults.txt
  (( ++ designError ))
fi

if egrep -v '^ *#include *(< *iostream|< *cassert|" *BinarySearchTree.)' BinarySearchTree.* | grep "#include" &> /dev/null ; then
  echo 'Fatal design error: #include ofheader file other than iostream, BinarySearchTree., or cassert found.' >> designResults.txt
  (( ++ designError ))
fi

if grep "\[" BinarySearchTree.* ; then
  echo 'Fatal design error: Found [ in BinarySearchTree.*.'  >> designResults.txt
  (( ++ designError ))
fi

if egrep -v "(#include|assert)" BinarySearchTree.* | egrep "(==| >|<=|!=)" &> /dev/null; then
  echo 'Comparison other than "<" found in BinarySearchTree.*.' >> designResults.txt
  (( ++ designError ))
fi

# non-fatal design errors from here on


echo $designError  # Only standard out

if ! grep "insert *(BSTNode<T> *\*t, *const *T *&value *)" BinarySearchTree.cpp >& /dev/null ; then
  echo '"insert(BSTNode<T> *t, const T &value)" not found in BinarySearchTree.cpp' >> designResults.txt
fi

if ! grep "remove *(BSTNode<T> *\* *& *t, *const *T *&value *)" BinarySearchTree.cpp >& /dev/null ; then
  echo '"remove(BSTNode<T> * &t, const T &value)" not found in BinarySearchTree.cpp' >> designResults.txt
fi

if ! grep "find *(.*BSTNode<T> *\*.*,.*T.*)" BinarySearchTree.cpp >& /dev/null ; 
then
  echo 'recursive find not found in BinarySearchTree.cpp' >> designResults.txt
fi

if ! grep "inOrder *(.*BSTNode<T> *\*.*)" BinarySearchTree.cpp >& /dev/null ;                   
then
  echo 'recursive inOrder not found in BinarySearchTree.cpp' >> designResultls.txt
fi

if ! grep "findMin *(.*BSTNode<T> *\*.*)" BinarySearchTree.cpp >& /dev/null ;     
then
  echo 'recursive findMin not found in BinarySearchTree.cpp' >> designResults.txt
fi

if ! grep "makeEmpty *(.*BSTNode<T> *\*.*)" BinarySearchTree.cpp >& /dev/null ;     
then
  echo 'recursive makeEmpty not found in BinarySearchTree.cpp' >> designResults.txt
fi

if ! grep "postOrder *(.*BSTNode<T> *\*.*)" BinarySearchTree.cpp >& /dev/null ;       
then
  echo 'recursive postOrder not found in BinarySearchTree.cpp' >> designResults.txt
fi


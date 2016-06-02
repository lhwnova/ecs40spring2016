#!  /bin/bash

testerDirectory="/home/ssdavis/40/p6/Testing"

if [ $# -ne 2 ]; then
  >&2 echo "usage DesignChecker.sh: $testerDirectory/DesignChecker.sh container_directory operation_score"
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


if grep "/\*" *.h *vector.cpp *list.cpp &> /dev/null ; then
  cat temp >> designResults.txt
  echo 'Fatal design error: "/*" found. ' >> designResults.txt
  (( ++designError ))
fi

if egrep "[^a-zA-Z][0-9]+" *vector.cpp *list.cpp *.h | grep -v "const *int" | egrep -v "( 0| 1[^0-9]|cout)"  &> /dev/null ; then
  echo 'Fatal design error: Constant other than 0 and 1 found outside of static const.'  >> designResults.txt
  egrep "[^a-zA-Z][0-9]+" *vector.cpp *list.cpp *.h | grep -v "const *int" | egrep -v "( 0| 1[^0-9]|cout)" >> designResults.txt
  (( ++ designError ))
fi  

if [[ `awk '/#include/, /^{/' *.cpp *.h | egrep -v "\(|\)|const" | egrep "(void|int|char|double|float)" | wc -l ` -ne 0 ]] ; then
 echo 'Fatal design error: "Global variable found above first function/class in a file.'  >> designResults.txt
awk '/#include/, /^{/' *.cpp *.h | egrep -v "\(|\)|const" | egrep "(void|int|char|double|float)" >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/^}/, /^{/' *.cpp *.h | egrep -v "\(|\)|^}|const" | egrep "(void|int|char|double|float)" | wc -l ` -ne 0 ]] ; then
 echo 'Fatal design error: "Global variable found between functions in a file.'  >> designResults.txt
awk '/^}/, /^{/' *.cpp *.h | egrep -v "\(|\)|^}|const" | egrep "(void|int|char|double|float)" >> designResults.txt
  (( ++ designError ))
fi

if grep "goto" *.cpp *.h  &> /dev/null ; then
  echo 'Fatal design error: "goto" found in files.'  >> designResults.txt
  (( ++ designError ))
fi


# non-fatal design errors from here on

const2=` grep "static *const *int .*= 2" sortedvector.h | sed \s/[^A-Z_]//g`
found=0

for constant in $const2 ; do
  if [[ `awk '/SortedVector::resize/, /^}/' sortedvector.cpp | egrep "capacity *(\(|= |\*= )" | grep $constant | 
wc -l ` -eq 1 ]] ; then
     (( ++ found ))
  fi
done

if [ $found -ne 1 ] ; then
  echo "capacity not doubled in size in SortedVector::resize()." >> designResults.txt
fi

if ! grep "^Container *:: *Container *(int .*[A-Za-z]* *)" container.cpp &> /dev/null ; then
  echo "Conainer constructor with only int not found in container.cpp" >> designResults.txt
fi

if  grep -v "Container *:: *Container *(int .*[A-Za-z]* *)" container.cpp | grep "^Container *:: *Container" &> /dev/null ; then
  echo "Second Container constructor found in container.cpp" >> designResults.txt
fi

if ! grep "^Container *:: *~Container" container.cpp  &> /dev/null ; then
  echo "Container destructor not found in container.cpp" >> designResults.txt
fi

if ! grep "^ *virtual int\* *insert.*= 0" container.h  &> /dev/null ; then
  echo "Pure virtual insert method not found in container.h" >> designResults.txt
fi

if ! grep "^ *virtual int\* *erase.*= 0" container.h  &> /dev/null ; then
  echo "Pure virtual erase method not found in container.h" >> designResults.txt
fi

if ! grep "^ *virtual int\* *find.*= 0" container.h  &> /dev/null ; then
  echo "Pure virtual find method not found in container.h" >> designResults.txt
fi

if ! awk '/protected:/, /public/' sortedvector.h | grep "resize" &> /dev/null ; then
  echo "protected resize() method not found in sortedvector.h" >> designResults.txt
fi

if ! grep "^SortedVector *:: *~SortedVector" sortedvector.cpp  &> /dev/null ; then
  echo "SortedVector destructor not found in sortedvector.cpp" >> designResults.txt
fi

if ! grep "^ *virtual *int\* insert" sortedvector.h  &> /dev/null ; then
  echo "virtual insert method not found in sortedvector.h" >> designResults.txt
fi

if ! grep "^ *virtual *int\* erase" sortedvector.h  &> /dev/null ; then
  echo "virtual erase method not found in sortedvector.h" >> designResults.txt
fi

if ! grep "^ *virtual *int\* find" sortedvector.h  &> /dev/null ; then
  echo "virtual find method not found in sortedvector.h" >> designResults.txt
fi

if  egrep "(!=|==|<=|>=)" sortedvector.cpp  &> /dev/null ; then
  echo '"!=" or "==" or "<=" or ">=" found in sortedvector.cpp' >> designResults.txt
fi

if ! grep "^const *int& *SortedVector::operator *\[.*)*const" sortedvector.cpp  &> /dev/null ; then
  echo "const operator[] not found in sortedvector.cpp" >> designResults.txt
fi

 if grep "Vector *:: *Vector" vector.cpp  &> /dev/null ; then
   echo "Vector constructor found in vector.cpp" >> designResults.txt
 fi

if grep "Vector *:: *~Vector" vector.cpp  &> /dev/null ; then
  echo "Vector destructor found in vector.cpp" >> designResults.txt
fi

if ! grep "^ *int\* insert" vector.h  &> /dev/null ; then
  echo "non-virtual insert method not found in vector.h" >> designResults.txt
fi

if ! grep "^ *int\* erase" vector.h  &> /dev/null ; then
  echo "non-virtual erase method not found in vector.h" >> designResults.txt
fi

if ! grep "^ *int\* find" vector.h  &> /dev/null ; then
  echo "non-virtual find method not found in vector.h" >> designResults.txt
fi

if  egrep "(!=|==)" vector.cpp  &> /dev/null ; then
  echo '"!=" or "==" found in vector.cpp' >> designResults.txt
fi

if grep "^const *int& *Vector::operator *\[.*)*const" vector.cpp  &> /dev/null ; then
  echo "const operator[] found in vector.cpp" >> designResults.txt
fi

if ! grep "^ *int.*& *Vector *:: *operator *\[" vector.cpp  &> /dev/null ; then
  echo "non-const operator[] not found in vector.cpp" >> designResults.txt
fi

if ! grep "^LinkedList *:: *~LinkedList" linkedlist.cpp  &> /dev/null ; then
  echo "LinkedList destructor not found in linkedlist.cpp" >> designResults.txt
fi

if ! grep "^ *virtual *int\* insert" linkedlist.h  &> /dev/null ; then
  echo "virtual insert method not found in linkedlist.h" >> designResults.txt
fi

if ! grep "^ *virtual *int\* erase" linkedlist.h  &> /dev/null ; then
  echo "virtual erase method not found in linkedlist.h" >> designResults.txt
fi

if ! grep "^ *virtual *int\* find" linkedlist.h  &> /dev/null ; then
  echo "virtual find method not found in linkedlist.h" >> designResults.txt
fi

if  egrep "(!=|==)" linkedlist.cpp  &> /dev/null ; then
  echo '"!=" or "==" found in linkedlist.cpp' >> designResults.txt
fi

if ! grep "^ *int\* *LinkedList::operator *++ *( *)" linkedlist.cpp  &> /dev/null ; then
  echo "pre-increment operator++ not found in linkedlist.cpp" >> designResults.txt
fi

if ! grep "^ *int\* *LinkedList::operator *-- *( *)" linkedlist.cpp  &> /dev/null ; then
  echo "pre-increment operator-- not found in linkedlist.cpp" >> designResults.txt
fi

if grep "^SortedLinkedList *:: *SortedLinkedList" sortedlinkedlist.cpp  &> /dev/null ; then
  echo "SortedLinkedList constructor found in sortedlinkedlist.cpp" >> designResults.txt
fi

if grep "^SortedLinkedList *:: *~SortedLinkedList" sortedlinked.cpp  &> /dev/null ; then
  echo "SortedLinkedList destructor found in sortedlinkedlist.cpp" >> designResults.txt
fi

if grep "^*int\* *LinkedList::operator *++ *( *)" sortedlinkedlist.cpp  &> /dev/null ; then
  echo "pre-increment operator++  found in sortedlinkedlist.cpp" >> designResults.txt
fi

if  grep "^*int\* *LinkedList::operator *-- *( *)" sortedlinkedlist.cpp  &> /dev/null ; then
  echo "pre-increment operator-- found in sortedlinkedlist.cpp" >> designResults.txt
fi

if ! grep "^ *int\* insert" sortedlinkedlist.h  &> /dev/null ; then
  echo "non-virtual insert method not found in sortedlinkedlist.h" >> designResults.txt
fi

if ! grep "^ *int\* erase" sortedlinkedlist.h  &> /dev/null ; then
  echo "non-virtual erase method not found in sortedlinkedlist.h" >> designResults.txt
fi

if ! grep "^ *int\* find" sortedlinkedlist.h  &> /dev/null ; then
  echo "non-virtual find method not found in sortedlinkedlist.h" >> designResults.txt
fi

if  egrep "(!=|==|>=|<=)" sortedlinkedlist.cpp  &> /dev/null ; then
  echo '"!=" or "==" or ">=" or "<=" found in sortedlinkedlist.cpp' >> designResults.txt
fi

if ! grep "getSize.*const" container.h &> /dev/null ; then
  echo "getSize() const not found in container.h"  >> designRestuls.txt
fi



echo $designError  # Only standard out

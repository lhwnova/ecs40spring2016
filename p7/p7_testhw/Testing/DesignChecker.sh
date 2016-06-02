#!  /bin/bash

testerDirectory="/home/ssdavis/40/p7/Testing"

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


if grep "/\*" vector.cpp vector.h &> /dev/null ; then
  cat temp >> designResults.txt
  echo 'Fatal design error: "/*" found. ' >> designResults.txt
  (( ++designError ))
fi

if egrep "[^a-zA-Z][0-9]+" vector.cpp vector.h | grep -v "const *int" | egrep -v "( 0| 1[^0-9]|cout)" &> /dev/null  ; then
  echo 'Fatal design error: Constant other than 0 and 1 found outside of static const.'  >> designResults.txt
  egrep "[^a-zA-Z][0-9]+" vector.cpp vector.h | grep -v "const *int" | egrep -v "( 0| 1[^0-9]|cout)" >> designResults.txt
  (( ++ designError ))
fi  

if [[ `awk '/#include/, /^{/' vector.cpp vector.h | egrep -v "\(|\)|const" | egrep "(void|int|char|double|float)" | wc -l ` -ne 0 ]] ; then
 echo 'Fatal design error: "Global variable found above first function/class in a file.'  >> designResults.txt
awk '/#include/, /^{/' *.cpp *.h | egrep -v "\(|\)|const" | egrep "(void|int|char|double|float)" >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/^}/, /^{/' vector.cpp vector.h | egrep -v "\(|\)|^}|const" | egrep "(void|int|char|double|float)" | wc -l ` -ne 0 ]] ; then
 echo 'Fatal design error: "Global variable found between functions in a file.'  >> designResults.txt
awk '/^}/, /^{/' *.cpp *.h | egrep -v "\(|\)|^}|const" | egrep "(void|int|char|double|float)" >> designResults.txt
  (( ++ designError ))
fi

if grep "goto" *.cpp *.h  &> /dev/null ; then
  echo 'Fatal design error: "goto" found in files.'  >> designResults.txt
  (( ++ designError ))
fi

if egrep -v '^ *#include *(< *iostream|" *vector\.)' vector.cpp vector.h | grep "#include" &> /dev/null ; then
  echo 'Fatal design error: #include of header file other than vector.* or iostream found in vector.*' >> designResults.txt
fi


# non-fatal design errors from here on


echo $designError  # Only standard out

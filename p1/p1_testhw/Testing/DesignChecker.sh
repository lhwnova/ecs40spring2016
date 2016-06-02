#!  /bin/bash

testerDirectory="/home/ssdavis/40/p1/Testing"

if [ $# -ne 2 ]; then
  >&2 echo "usage DesignChecker.sh: $testerDirectory/DesignChecker.sh airline_directory operation_score"
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

grep "/\*" *.h *.cpp > temp
if [ -s temp ]; then
  cat temp >> designResults.txt
  echo 'Fatal design error: "/*" found. ' >> designResults.txt
  (( ++designError ))
fi

if [[ `awk '/typedef struct/, /} *Flight;/' flight.h | grep "int flightNum;" | wc -l ` -ne 1 ]] ; then
 echo 'Fatal design error: "int flightNum;" not found in typedef struct Flight in flight.h.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/typedef struct/, /} *Flight;/' flight.h | grep "char origin\[.*\];" | wc -l ` -ne 1 ]] ; then
 echo 'Fatal design error: "char origin[...];" not found in typedef struct Flight in flight.h.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/typedef struct/, /} *Flight;/' flight.h | grep "char destination\[.*\];" | wc -l ` -ne 1 ]] ; then
 echo 'Fatal design error: "char destination[...];" not found in typedef struct Flight in flight.h.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/typedef struct/, /} *Flight;/' flight.h | grep "Plane \*plane;" | wc -l ` -ne 1 ]] ; then
 echo 'Fatal design error: "Plane *plane;" not found in typedef struct Flight in flight.h.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/typedef struct/, /} *Flight;/' flight.h  | grep ";" | wc -l ` -ne 5 ]] ; then
 echo 'Fatal design error: More than 5 semi-colons found in typedef struct Flight in flight.h.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/typedef struct/, /} *Plane;/' plane.h | grep "int rows;" | wc -l ` -ne 1 ]] ; then
 echo 'Fatal design error: "int rows;" not found in typedef struct Plane in plane.h.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/typedef struct/, /} *Plane;/' plane.h | grep "int width;" | wc -l ` -ne 1 ]] ; then
 echo 'Fatal design error: "int width;" not found in typedef struct Plane in plane.h.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/typedef struct/, /} *Plane;/' plane.h | grep "int reserved;" | wc -l ` -ne 1 ]] ; then
 echo 'Fatal design error: "int reserved;" not found in typedef struct Plane in plane.h.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/typedef struct/, /} *Plane;/' plane.h | grep "char \*\*\*passengers;" | wc -l ` -ne 1 ]] ; then
 echo 'Fatal design error: "char ***passengers;" not found in typedef struct Plane in plane.h.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/typedef struct/, /} *Plane;/' plane.h | grep ";" | wc -l ` -gt 5 ]] ; then
 echo 'Fatal design error: more than five semi-colons found in typedef struct Plane in plane.h.'  >> designResults.txt
  (( ++ designError ))
fi

if [[  `awk -F\; '/main/,/^}/ {print $0}' main.cpp | grep ";" | wc -l ` -gt 8 ]] ; then
  echo 'Fatal design error: More than eight semi-colons in main().'  >> designResults.txt
  (( ++ designError ))
fi 

if  egrep "(flightNum[^A-Za-z]|origin|destination)" main.cpp plane.cpp utilities.cpp plane.h utilities.h &> /dev/null ; then
  echo 'Fatal design error: Element of Flight found outside of flight.cpp and flight.h '  >> designResults.txt
  (( ++ designError ))
fi 

if egrep "(rows|width|reserved|passengers)" main.cpp flight.cpp utilities.cpp flight.h utilities.h  &> /dev/null ; then
  echo 'Fatal design error: Element of Plane found outside of plane.cpp and plane.h '  >> designResults.txt
  (( ++ designError ))
fi 


if [[ `egrep "plane *= *(\( *Plane *\* *\) *malloc|new *Plane)" flight.cpp | wc -l` -ne 1 ]] ; then
  echo 'Fatal design error: Dynamic allocation of Plane not found in flight.cpp '  >> designResults.txt
  (( ++ designError ))
fi

if [[ `egrep "passengers *= *(\( *char *\*\*\* *\) *malloc|new *char\*\*)" plane.cpp | wc -l` -ne 1 ]] ; then
  echo 'Fatal design error: Dynamic allocation of passengers not found in plane.cpp '  >> designResults.txt
  (( ++ designError ))
fi

if grep "[0-9]" *.cpp *.h | grep -v "#define" | egrep -v "( 0| 1|printf|cout|reservations2)"  &> /dev/null ; then
  echo 'Fatal design error: Constant other than 0 and 1 found outside of #define.'  >> designResults.txt
  (( ++ designError ))
fi  

if [[ `awk '/#include/, /^{/' *.cpp *.h | egrep -v "\(|\)" | egrep "(void|int|char|double|float|Plane|Flight)" | wc -l ` -ne 0 ]] ; then
 echo 'Fatal design error: "Global variable found above first function/typedef in a file.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/^}/, /^{/' *.cpp *.h | egrep -v "\(|\)|^}" | egrep "(void|int|char|double|float|Plane|Flight)" | wc -l ` -ne 0 ]] ; then
 echo 'Fatal design error: "Global variable found between functions in a file.'  >> designResults.txt
  (( ++ designError ))
fi

if grep "goto" *.cpp *.h  &> /dev/null ; then
  echo 'Fatal design error: "goto" found in files.'  >> designResults.txt
  (( ++ designError ))
fi




# non-fatal design errors from here on

echo $designError  # Only standard out


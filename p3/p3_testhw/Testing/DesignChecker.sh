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

if [[ `awk '/class *Flight/, /} *;/' flight.h | grep "int flightNum;" | wc -l ` -ne 1 ]] ; then
 echo 'Fatal design error: "int flightNum;" not found in class Flight in flight.h.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/class *Flight/, /} *;/' flight.h | grep "char origin\[.*\];" | wc -l ` -ne 1 ]] ; then
 echo 'Fatal design error: "char origin[...];" not found in class Flight in flight.h.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/class *Flight/, /} *Flight;/' flight.h | grep "char destination\[.*\];" | wc -l ` -ne 1 ]] ; then
 echo 'Fatal design error: "char destination[...];" not found in class Flight in flight.h.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/class *Flight/, /} *;/' flight.h | grep "Plane \*plane;" | wc -l ` -ne 1 ]] ; then
 echo 'Fatal design error: "Plane *plane;" not found in class Flight in flight.h.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/class *Plane/, /} *;/' plane.h | grep "int rows;" | wc -l ` -ne 1 ]] ; then
 echo 'Fatal design error: "int rows;" not found in class *Flight Plane in plane.h.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/class *Plane/, /} *;/' plane.h | grep "int width;" | wc -l ` -ne 1 ]] ; then
 echo 'Fatal design error: "int width;" not found in class *Flight Plane in plane.h.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/class *Plane/, /} *;/' plane.h | grep "int reserved;" | wc -l ` -ne 1 ]] ; then
 echo 'Fatal design error: "int reserved;" not found in class *Flight Plane in plane.h.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/class *Plane/, /} *;/' plane.h | grep "char \*\*\*passengers;" | wc -l ` -ne 1 ]] ; then
 echo 'Fatal design error: "char ***passengers;" not found in class *Flight Plane in plane.h.'  >> designResults.txt
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


if egrep "(stdio|stdlib|struct)" *.h *cpp >& /dev/null ; then
  echo 'Fatal design error: stdlib, stdio, or struct found in a file.'  >> designResults.txt
  (( ++ designError ))
fi

if grep "[0-9]" *.cpp *.h | grep -v "#define" | egrep -v "( 0| 1|cout|reservations2)"  &> /dev/null ; then
  echo 'Fatal design error: Constant other than 0 and 1 found outside of #define.'  >> designResults.txt
  grep "[0-9]" *.cpp *.h | grep -v "#define" | egrep -v "( 0| 1|cout|reservations2)" >> designResults.txt
  (( ++ designError ))
fi  

if [[ `awk '/#include/, /^{/' *.cpp *.h | egrep -v "\(|\)" | egrep "(void|int|char|double|float)" | wc -l ` -ne 0 ]] ; then
 echo 'Fatal design error: "Global variable found above first function/class in a file.'  >> designResults.txt
  (( ++ designError ))
fi

if [[ `awk '/^}/, /^{/' *.cpp *.h | egrep -v "\(|\)|^}" | egrep "(void|int|char|double|float)" | wc -l ` -ne 0 ]] ; then
 echo 'Fatal design error: "Global variable found between functions in a file.'  >> designResults.txt
  (( ++ designError ))
fi

if grep "goto" *.cpp *.h  &> /dev/null ; then
  echo 'Fatal design error: "goto" found in files.'  >> designResults.txt
  (( ++ designError ))
fi




# non-fatal design errors from here on

if ! grep "(.*ofstream.*) *const" flight.h &> /dev/null ; then
  echo "Missing const from Flight method that writes reservations2.txt"  >> designResults.txt
fi

if grep "getFlightNumber" flight.h &> /dev/null && ! grep "getFlightNumber.*const" flight.h &> /dev/null ; then
  echo "Missing const from Flight::getFlightNumber() method"  >> designResults.txt
fi

if grep "printFlightInfo" flight.h &> /dev/null && ! grep "printFlightInfo.*const" flight.h &> /dev/null ; then
  echo "Missing const from Flight::printFlightInfo() method"  >> designResults.txt
fi


if ! grep "(.*ofstream.*) *const" plane.h &> /dev/null ; then
  echo "Missing const from Plane method that writes reservations2.txt"  >> designResults.txt
fi

if grep "showGrid" plane.h &> /dev/null && ! grep "showGrid.*const" plane.h &> /dev/null ; then
  echo "Missing const from Plane::showGrid() method"  >> designResults.txt
fi

if grep "getRow" plane.h &> /dev/null && ! grep "getRow.*const" plane.h &> /dev/null ; then
  echo "Missing const from Plane::getRows() method"  >> designResults.txt
fi



echo $designError  # Only standard out


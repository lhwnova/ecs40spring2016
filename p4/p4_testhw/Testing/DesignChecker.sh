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


if  egrep "(flightNum[^A-Za-z]|origin|destination)" main.cpp utilities.cpp flights.cpp flights.h utilities.h &> /dev/null ; then
  echo 'Fatal design error: Element of Flight found outside of flight.cpp and flight.h '  >> designResults.txt
  (( ++ designError ))
fi 

if egrep "(rows|width|reserved|passengers)" main.cpp flight.cpp passengers.h passengers.cpp utilities.cpp flight.h utilities.h  &> /dev/null ; then
  echo 'Fatal design error: Element of Plane found outside of plane.cpp and plane.h '  >> designResults.txt
  (( ++ designError ))
fi 


if egrep "(stdio|stdlib|struct)" *.h *cpp >& /dev/null ; then
  echo 'Fatal design error: stdlib, stdio, or struct found in a file.'  >> designResults.txt
  (( ++ designError ))
fi

if egrep "[^a-zA-Z][0-9]+" *.cpp *.h | grep -v "const *int" | egrep -v "( 0| 1[^0-9]|cout)"  &> /dev/null ; then
  echo 'Fatal design error: Constant other than 0 and 1 found outside of static const.'  >> designResults.txt
  egrep "[^a-zA-Z][0-9]+" *.cpp *.h | grep -v "const *int" | egrep -v "( 0| 1[^0-9]|cout)" >> designResults.txt
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

if ! grep "(.*ofstream.*) *const" plane.cpp &> /dev/null ; then
  echo "Missing const from Plane method that writes flights2.csv"  >> designResults.txt
  echo "You will lose 2 points." >> designResults.txt
fi

const2=` grep "static *const *int .*= 2" flights.h | sed \s/[^A-Z_]//g`
found=0

for constant in $const2 ; do
  if [[ `awk '/::Flights/, /^}/' flights.cpp | egrep "capacity *(\(|= )" | grep $constant | wc -l ` -eq 1 ]] ; then 
     (( ++ found ))
  fi
done


if [ $found -ne 1 ] ; then
  echo "capacity not initialized to 2 in Flight constructor." >> designResults.txt
  echo "You will lose 2 points." >> designResults.txt
fi

found=0

for constant in $const2 ; do
  if [[ `awk '/::insert/, /^}/' flights.cpp | egrep "capacity *(\(|= |\*= )" | grep $constant | 
wc -l ` -eq 1 ]] ; then
     (( ++ found ))
  fi
done

if [ $found -ne 1 ] ; then
  echo "capacity not doubled in size in Flights::insert." >> designResults.txt
  echo "You will lose 2 points." >> designResults.txt
fi

if  egrep "Passenger ([^(]*,|.*\[)" *.cpp ; then
  echo "Found more than one Passenger declared in a function." >> designResults.txt
  echo "You will lose 2 points." >> designResults.txt
fi

if ! grep "addPassenger.*) *const" flights.h >& /dev/null ; then
  echo "Flights::addPassenger() not const" >> designResults.txt
fi

if ! grep "removePassenger.*) *const" flights.h >& /dev/null ; then
  echo "Flights::removePassenger() not const" >> designResults.txt
fi

if ! grep "addPassenger.*) *const" flight.h >& /dev/null ; then
  echo "Flight::addPassenger() not const" >> designResults.txt
fi

if ! grep "removePassenger.*) *const" flight.h >& /dev/null ; then
  echo "Flight::removePassenger() not const" >> designResults.txt
fi


echo $designError  # Only standard out



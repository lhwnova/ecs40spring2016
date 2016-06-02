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

if ! awk '/class *Plane/, /^};/' plane.h | grep "LinkedList *\* *passengers;" &> /dev/null ; then
  echo 'Fatal design error: "LinkedList *passengers;" not found in plane.h'  >> designResults.txt 
  (( ++ designError ))
fi

# non-fatal design errors from here on

if ! grep "(.*ofstream.*) *const" plane.cpp &> /dev/null ; then
  echo "Missing const from Plane method that writes flights2.csv"  >> designResults.txt
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
fi

found=0

for constant in $const2 ; do
  if [[ `awk '/::operator *\+=/, /^}/' flights.cpp | egrep "capacity *(\(|= |\*= )" | grep $constant | 
wc -l ` -eq 1 ]] ; then
     (( ++ found ))
  fi
done

if [ $found -ne 1 ] ; then
  echo "capacity not doubled in size in Flight::operator+=." >> designResults.txt
fi

if  egrep "Passenger ([^(]*,|.*\[)" *.cpp  &> /dev/null ; then
  echo "Found more than one Passenger declared in a function." >> designResults.txt
fi

if grep "EMPTY" plane.cpp | grep -v "LinkedList::EMPTY"  &> /dev/null ; then
  echo "Found non-LinkedList EMPTY in plane.cpp." >> designResults.txt
fi

if ! grep "LinkedList::~LinkedList" linkedlist.cpp &> /dev/null ; then
  echo "LinkedList destructor not found in linkedlist.cpp" >> designResults.txt
fi

if ! grep "LinkedList::initialize" linkedlist.cpp &> /dev/null ; then
  echo "LinkedList::initialize not found in linkedlist.cpp" >> designResults.txt
fi

if grep "LinkedList::LinkedList" linkedlist.cpp  &> /dev/null ; then
  echo "LinkedList constructor found in linkedlist.cpp" >> designResults.txt
fi

if ! grep "LinkedList::operator *\[.*) *$" linkedlist.cpp  &> /dev/null ; then
  echo "non-const LinkedList::operator[] not found in linkedlist.cpp" >> designResults.txt
fi

if ! grep "LinkedList::operator *\[.*) *const *$" linkedlist.cpp &> /dev/null ; then
  echo "const LinkedList::operator[] not found in linkedlist.cpp" >> designResults.txt
fi

if ! grep "Passenger::operator *==.*int" passenger.cpp &> /dev/null ; then
  echo "Passenger equality operator (==) that takes an int not found in passenger.cpp" >> designResults.txt
fi

if ! grep "Passenger::operator *==.*const *char" passenger.cpp &> /dev/null  ; then
  echo "Passenger equality operator (==) that takes a const char* not found in passenger.cpp" >> designResults.txt
fi

if ! grep "Passenger::operator *!" passenger.cpp &> /dev/null  ; then
  echo "Passenger negation operator (!) not found in passenger.cpp" >> designResults.txt
fi

if ! grep "operator *<<" passenger.cpp  &> /dev/null ; then
  echo "operator<< not found in passenger.cpp" >> designResults.txt
fi

if grep "friend *class *Plane" passenger.h &> /dev/null ; then
  echo '"friend class Plane" found in passenger.h' >> designResults.txt
fi

if grep "friend *Plane" passenger.h &> /dev/null ; then
  echo '"friend Plane" found in passenger.h' >> designResults.txt
fi

if grep "showPassengers" plane.cpp flight.cpp &> /dev/null \
  || ! grep "operator *<<" plane.cpp &> /dev/null \
  || ! grep "<<.*this" plane.cpp &> /dev/null ; then
  echo "showPassengers found or Plane insertion operator (<<) not found in plane.cpp, or not used in plane.cpp" >> designResults.txt
fi

if grep "Plane::Plane.*stream" plane.cpp &> /dev/null \
  || ! grep "operator *>>" plane.cpp &> /dev/null \
  || ! grep ">>.*plane" flight.cpp &> /dev/null ; then
  echo "Plane(*stream) found or Plane extraction operator (>>) not found in plane.cpp, or not used in flight.cpp" >> designResults.txt
fi

if grep "addPassengers" plane.cpp flight.cpp &> /dev/null \
  || ! grep "operator *++ *( *)" plane.cpp &> /dev/null \
  || ! grep "++.*plane" flight.cpp &> /dev/null ; then
  echo "addPassengers found or Plane pre-increment operator (++) not found in plane.cpp, or not used in flight.cpp" >> designResults.txt
fi

if grep "removePassengers" plane.cpp flight.cpp &> /dev/null \
  || ! grep "operator *-- *( *int.*)" plane.cpp &> /dev/null \
  || ! grep "plane.*--" flight.cpp &> /dev/null ; then
  echo "removePassengers found or Plane post-decrement operator (--) not found in plane.cpp, or not used in flight.cpp" >> designResults.txt
fi

if grep "removePlane" plane.cpp flight.cpp &> /dev/null \
  || ! grep "operator *!" plane.cpp &> /dev/null \
  || ! grep "!.*plane" flight.cpp &> /dev/null ; then
  echo "removePlane found or Plane negate operator (!) not found in plane.cpp, or not used in flight.cpp" >> designResults.txt
fi

if ! grep "operator *<<" linkedlist.cpp &> /dev/null \
  || ! grep "<< *passengers" plane.cpp &> /dev/null ; then
  echo "LinkedList insertion operator (<<) not found in linkedlist.cpp, or not used in plane.cpp" >> designResults.txt
fi

if grep "addPassenger" flight.cpp &> /dev/null \
  || ! grep "operator *++ *( *int.*)" flight.cpp &> /dev/null \
  || ! grep "flight.*++" flights.cpp &> /dev/null ; then
  echo "addPassenger found or Flight post-increment operator (++) not found in flight.cpp, or not used in flights.cpp" >> designResults.txt
fi

if grep "printFlightInfo" flight.cpp flights.cpp &> /dev/null \
  || ! grep "operator *<<" flight.cpp &> /dev/null \
  || ! grep "<<.*flight" flights.cpp &> /dev/null ; then
  echo "printFlightInfo found or Flight insertion operator (<<) not found in flight.cpp, or not used in flights.cpp" >> designResults.txt
fi

if grep "readFlight" flight.cpp flights.cpp &> /dev/null \
  || ! grep "operator *>>" flight.cpp &> /dev/null \
  || ! grep ">>.*flight" flights.cpp &> /dev/null ; then
  echo "readFlight found or Flight extraction operator (>>) not found in flight.cpp, or not used in flights.cpp" >> designResults.txt
fi

if grep "removeFlight" flight.cpp &> /dev/null \
  || ! grep "operator *!" flight.cpp &> /dev/null \
  || ! grep "!.*flight" flights.cpp &> /dev/null ; then
  echo "removeFlight found or Flight negation operator (!) not found in flight.cpp, or not used in flights.cpp" >> designResults.txt
fi


if grep "removePassenger" flight.cpp &> /dev/null \
  || ! grep "operator *-- *( *)" flight.cpp &> /dev/null \
  || ! grep "\-\-.*flight" flights.cpp &> /dev/null ; then
  echo "removePassenger found or Flight pre-decrement operator (--) not found in flight.cpp, or not used in flights.cpp" >> designResults.txt
fi

if grep "Flights *:: *addFlight" flights.cpp &> /dev/null \
  || ! grep "operator *++ *( *)" flights.cpp &> /dev/null \
  || ! grep "++.*flight" main.cpp &> /dev/null ; then
  echo "addFlight found or Flights pre-increment operator (++) not found in flights.cpp, or not used in main.cpp" >> designResults.txt
fi

if grep "insert" flights.cpp main.cpp &> /dev/null \
  || ! grep "operator *+=" flights.cpp &> /dev/null \
  || ! grep "flight.*+=" flights.cpp &> /dev/null ; then
  echo "insert found or Flights += operator not found in flights.cpp, or not used in flights.cpp" >> designResults.txt
fi

if grep "removeFlight" flights.cpp main.cpp &> /dev/null \
  || ! grep "operator *-- *( *int *)" flights.cpp &> /dev/null \
  || ! grep "flight.*--" main.cpp &> /dev/null ; then
  echo "removeFlight found or Flights post-decrement operator (--) not found in flights.cpp, or not used in main.cpp" >> designResults.txt
fi

if grep "readFlights" flights.cpp main.cpp &> /dev/null \
  || ! grep "operator *>>" flights.cpp &> /dev/null \
  || ! grep ">>.*flight" main.cpp &> /dev/null ; then
  echo "readFlights found or Flights extraction operator (>>>) not found in flights.cpp, or not used in main.cpp" >> designResults.txt
fi

if [[ `awk '/class *Passenger/, /} *;/' passenger.h | grep "(" |  wc -l ` -gt 8 ]] ; then
 echo 'More than eight methods in Passenger class in passenger.h'  >> designResults.txt
fi


if ! grep "operator *<<.*const *Passenger" passenger.h &> /dev/null  ; then
  echo "Passenger insertion operator (<<) with const Passenger not found in passenger.h" >> designResults.txt
fi

if ! grep "(.*const *char" plane.h &> /dev/null  ; then
  echo '"(const char" not found in plane.h when it would be needed to find a Passenger' >> designResults.txt
fi

if ! grep "char.*) *const" plane.h &> /dev/null  ; then
  echo "const function to find a passenger by name not found in plane.h" >> designResults.txt
fi

if ! grep "operator *<<.*const *Flight" flight.h &> /dev/null  ; then
  echo "Flight insertion operator (<<) with const Flight not found in flight.h" >> designResults.txt
fi

echo $designError  # Only standard out


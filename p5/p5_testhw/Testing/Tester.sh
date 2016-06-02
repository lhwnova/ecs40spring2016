#! /bin/bash

testerDirectory="/home/ssdavis/40/p5/Testing"

if [ $# -ne 1 ]; then
  echo "usage Tester.sh: $testerDirectory/Tester.sh airline.out_directory" 1>&2
  exit
fi

if [[ $1 =~ Testing ]]; then # Use from this directory is not allowed
  echo "You may not use Testing as your own source directory!"  1>&2
  exit
fi

if [[ ! -e $1/airline.out ]]; then # airline.out not found
  echo "airline.out not found in $1!"  1>&2
  exit
fi

echo $1 1>&2
cd $1
rm -f *.dat flights*.csv out*.txt # &> /dev/null
cp $testerDirectory/passengers.dat $testerDirectory/flights.csv $testerDirectory/*.out .
chmod 444 passengers.dat flights.csv
fileNum=1
opScore=0
echo Operation testing:  1>&2

while [[ $fileNum -lt 3 ]]; do
  echo $fileNum  1>&2
  echo "File#: $fileNum " >> operationsResults.txt
  rm -f passengers[23].dat 
  (airline.out < $testerDirectory/in$fileNum.txt | tail -100 > out$fileNum.txt )&
  sleep 3
  pkill airline.out &> /dev/null
  rm core &> /dev/null

  if [[ -s out$fileNum.txt ]]; then
    diff out$fileNum.txt $testerDirectory/out$fileNum.txt > temp

    if [ -s temp ] ; then
      echo "Standard Out Not OK" >> operationsResults.txt
      cat temp >> operationsResults.txt
    else
      echo "Standard Out OK" >> operationsResults.txt
      (( opScore += 1 ))
    fi
  else
    echo "No output created so zero for operation." >> operationsResults.txt
  fi

  if [ -s passengers2.dat ]; then
    PrintDatFileCL.out passengers2.dat > passengers2-$fileNum.txt 
    diff  passengers2-$fileNum.txt $testerDirectory/passengers2-$fileNum.txt  > temp
    if [ -s temp ] ; then
      echo "passengers2.dat Not OK" >> operationsResults.txt
      cat temp >> operationsResults.txt
    else
      echo "passengers2.dat OK" >> operationsResults.txt
      (( opScore += 1 ))
    fi
  else
    echo "passengers2.dat not found." >> operationsResults.txt
  fi
  

  if [ -s passengers3.dat ]; then
    PrintDatFileCL.out  passengers3.dat > passengers3-$fileNum.txt 
    diff  passengers3-$fileNum.txt $testerDirectory/passengers3-$fileNum.txt > temp
    if [ -s temp ]; then
      echo "passengers3.dat Not OK" >> operationsResults.txt
      cat temp >> operationsResults.txt
    else
      echo "passengers3.dat OK" >> operationsResults.txt
      (( opScore += 1 ))
    fi
  else
    echo "passengers3.dat not found." >> operationsResults.txt
  fi

  if [ -s flights2.csv ]; then
    mv flights2.csv flights2-$fileNum.csv &> /dev/null
    if ! diff  flights2-$fileNum.csv $testerDirectory/flights2-$fileNum.csv >& /dev/null ; then
      echo "flights2.csv Not OK" >> operationsResults.txt
      echo "Yours:" >> operationsResults.txt
         cat flights2-$fileNum.csv >> operationsResults.txt
      echo -e "\n\nSean's:" >> operationsResults.txt
      echo  cat $testerDirectory/flights2-$fileNum.csv >> operationsResults.txt
    else
      echo "flights2.csv OK" >> operationsResults.txt
      (( opScore += 1 ))
    fi
  else
    echo "flights2.csv not found." >> operationsResults.txt
  fi

  fileNum=$((fileNum + 1))
done  # while less than 3

while [[ $fileNum -lt 6 ]]; do
  echo $fileNum  1>&2
  echo "File#: $fileNum " >> operationsResults.txt
  rm -f out$fileNum.txt  
  (airline.out < $testerDirectory/in$fileNum.txt | tail -100 > out$fileNum.txt )&
  sleep 3
  pkill airline.out &> /dev/null
  rm core &> /dev/null

  if [[ -s out$fileNum.txt ]]; then
    diff out$fileNum.txt $testerDirectory/out$fileNum.txt > temp

    if [ -s temp ] ; then
      echo "Standard Out Not OK" >> operationsResults.txt
      echo "Yours:" >> operationsResults.txt
      cat temp >> operationsResults.txt
    else
      echo "Standard Out OK" >> operationsResults.txt
      (( opScore += 2 ))
    fi
  else
    echo "No output created so zero for operation." >> operationsResults.txt
  fi

  fileNum=$((fileNum + 1))
done  # while less than 6

echo 6  1>&2
echo "Memory leak check:" >> operationsResults.txt
rm -f out$fileNum.txt >& /dev/null
(valgrind airline.out < $testerDirectory/in6.txt >& out$fileNum.txt )&
sleep 2
pkill airline.out >& /dev/null
pkill valgrind >& /dev/null
rm core >& /dev/null
rm vgcore* >& /dev/null

if [[ -s out$fileNum.txt ]]; then
  if grep "lost.*[1-9]" out$fileNum.txt >& /dev/null ; then
    echo "Memory leak found." >> operationsResults.txt
  else
    echo "OK"  >> operationsResults.txt
    (( opScore += 2 ))
  fi
else
  echo "Program did not terminate normally so memory leak could not checked." >> operationsResults.txt
fi

echo $opScore   # this is the only line that goes to stdout


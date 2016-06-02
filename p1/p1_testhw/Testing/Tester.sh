#! /bin/bash

testerDirectory="/home/ssdavis/40/p1/Testing"

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

cd $1
cp $testerDirectory/reservations.txt .
fileNum=1
opScore=0
echo Operation testing:  1>&2

while [[ $fileNum -lt 17 ]]; do
  echo $fileNum  1>&2
  echo "File#: $fileNum " >> operationsResults.txt
  rm -f out$fileNum.txt  
  (airline.out < $testerDirectory/in$fileNum.txt | tail -40 > out$fileNum.txt )&
  sleep 2
  pkill airline.out &> /dev/null
  rm core &> /dev/null
  if [[ -s out$fileNum.txt ]]; then
    diff out$fileNum.txt $testerDirectory/out$fileNum.txt > temp

    if [ -s temp ] ; then
      echo "Not OK" >> operationsResults.txt
      echo "Yours:" >> operationsResults.txt
      cat out$fileNum.txt >> operationsResults.txt
      echo -e "\n\nSean's:" >> operationsResults.txt
      cat  $testerDirectory/out$fileNum.txt >> operationsResults.txt
    else
      echo "OK" >> operationsResults.txt
      (( opScore += 1 ))
    fi
  else
    echo "No output created so zero for operation." >> operationsResults.txt
  fi

  fileNum=$((fileNum + 1))
done  # while less than 17

while [[ $fileNum -lt 19 ]]; do
  echo $fileNum  1>&2
  echo "File#: $fileNum " >> operationsResults.txt
  rm -f out$fileNum.txt >& /dev/null
  (airline.out < $testerDirectory/in$fileNum.txt >& /dev/null)&
  sleep 2
  pkill airline.out >& /dev/null
  rm core >& /dev/null
  cat reservations2.txt > out$fileNum.txt
  if [[ -s out$fileNum.txt ]]; then
    diff out$fileNum.txt $testerDirectory/out$fileNum.txt > temp

    if [ -s temp ] ; then
      echo "Not OK" >> operationsResults.txt
      echo "Yours:" >> operationsResults.txt
      cat out$fileNum.txt >> operationsResults.txt
      echo -e "\n\nSean's:" >> operationsResults.txt
      cat  $testerDirectory/out$fileNum.txt >> operationsResults.txt
      break
    else
      echo "OK" >> operationsResults.txt
      (( opScore += 4 ))
    fi
  else
    echo "No reservations2.txt created so zero for operation." >> operationsResults.txt
  fi

  fileNum=$((fileNum + 1))
done  # while less than 19 

echo 19  1>&2
echo "Memory leak check:" >> operationsResults.txt
rm -f out$fileNum.txt >& /dev/null
(valgrind airline.out < $testerDirectory/in18.txt >& out$fileNum.txt )&
sleep 2
pkill airline.out >& /dev/null
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


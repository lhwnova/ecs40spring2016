#! /bin/bash

testerDirectory="/home/ssdavis/40/p6/Testing"

if [ $# -ne 1 ]; then
  echo "usage Tester.sh: $testerDirectory/Tester.sh containers.out_directory" 1>&2
  exit
fi

if [[ $1 =~ Testing ]]; then # Use from this directory is not allowed
  echo "You may not use Testing as your own source directory!"  1>&2
  exit
fi

if [[ ! -e $1/containers.out ]]; then # containers.out not found
  echo "containers.out not found in $1!"  1>&2
  exit
fi

echo $1 1>&2
cd $1
rm -f out*.txt  &> /dev/null
mv main.cpp TheirMain.cpp
cp  $testerDirectory/file*.txt $testerDirectory/main[1-5].cpp .
fileNum=1
opScore=0
files=([1]=sortedvector.o [2]=vector.o [3]=linkedlist.o [4]=sortedlinkedlist.o)

echo Operation testing:  1>&2

while [[ $fileNum -lt 5 ]]; do
  echo $fileNum  1>&2

  echo "File#: $fileNum " >> operationsResults.txt

  if ! grep "${files[$fileNum]}" Makefile >& /dev/null ; then
    echo "${files[$fileNum]} not found in Makefile so this test skipped."  >> operationsResults.txt
    fileNum=$(( fileNum + 1 ))
    continue
  fi

  rm *.o *.out &> /dev/null
  cp main$fileNum.cpp main.cpp
  make >& /dev/null

  if ! [ -e containers.out ] ; then
    echo "Does not compile." >> operationsResults.txt
    fileNum=$(( fileNum + 1 ))
    continue
  fi
 
  (containers.out file$fileNum.txt | head -100 >& out$fileNum.txt )&
  sleep 1
  pkill containers.out &> /dev/null
  rm core &> /dev/null

  if [[ -s out$fileNum.txt ]]; then
    diff out$fileNum.txt $testerDirectory/out$fileNum.txt > temp

    if [ -s temp ] ; then
      echo "Not OK" >> operationsResults.txt
      cat temp >> operationsResults.txt
    else
      echo "OK" >> operationsResults.txt
      (( opScore += 5 ))
    fi
  else
    echo "No output created so zero for operation." >> operationsResults.txt
  fi

  fileNum=$(( fileNum + 1 ))
done  # while less than 5

echo $fileNum  1>&2
echo "Memory leak check:" >> operationsResults.txt
rm -f out$fileNum.txt >& /dev/null


rm *.o *.out &> /dev/null
cp main$fileNum.cpp main.cpp
make >& /dev/null
if ! [ -e containers.out ] ; then
  echo "main() using all four containers does not compile." >> operationsResults.txt
else # main() compiles
  (valgrind containers.out $testerDirectory/file$fileNum.txt >& out$fileNum.txt )&
  sleep 2
  pkill containers.out >& /dev/null
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
fi # else compiles

mv TheirMain.cpp main.cpp
echo $opScore   # this is the only line that goes to stdout


#! /bin/bash

testerDirectory="/home/ssdavis/40/p9/Testing"

if [ $# -ne 1 ]; then
  echo "usage Tester.sh: $testerDirectory/Tester.sh BST.out_directory" 1>&2
  exit
fi

if [[ $1 =~ Testing ]]; then # Use from this directory is not allowed
  echo "You may not use Testing as your own source directory!"  1>&2
  exit
fi

if [[ ! -e $1/BST.out ]]; then # BST.out not found
  echo "BST.out not found in $1!"  1>&2
  exit
fi

echo $1 1>&2
cd $1
rm -f out*.txt  &> /dev/null

cp $testerDirectory/File*.txt .

fileNum=1
opScore=0

echo Operation testing:  1>&2

while [ $fileNum -lt 18 ] ; do
  echo $fileNum  1>&2

  echo "File#: $fileNum " >> operationsResults.txt
  (BST.out File$fileNum.txt | head -10 >& out$fileNum.txt )&
  sleep 1
  pkill BST.out &> /dev/null
  rm core &> /dev/null

  if [ -s out$fileNum.txt ] ; then
    diff out$fileNum.txt $testerDirectory/out$fileNum.txt > temp

    if [ -s temp ] ; then
      echo "Not OK" >> operationsResults.txt
      cat temp >> operationsResults.txt
    else
      echo "OK" >> operationsResults.txt
      (( opScore += 1 ))
    fi
  else
    echo "No output created so zero for operation." >> operationsResults.txt
  fi

  fileNum=$(( fileNum + 1 ))
done  # while less than 18

fileNum=11

if [ -e BST2.out ] ; then
  while [ $fileNum -lt 18 ] ; do
    echo $fileNum  1>&2

    echo "File#: $fileNum " >> operationsResults.txt
    (BST2.out File$fileNum.txt >& temp )&
    sleep 1
    pkill BST2.out &> /dev/null
    rm core &> /dev/null
    cat temp | awk '{for (i = 3; i < NF; i++) printf "%s ", $i}' > outD$fileNum.txt

    if [ -s outD$fileNum.txt ] ; then
      diff outD$fileNum.txt $testerDirectory/outD$fileNum.txt > temp

      if [ -s temp ] ; then
        echo "Not OK" >> operationsResults.txt
        cat temp >> operationsResults.txt
      else
        echo "OK" >> operationsResults.txt
        (( opScore += 1 ))
      fi
    else
      echo "No output created so zero for operation." >> operationsResults.txt
    fi

    fileNum=$(( fileNum + 1 ))
  done  # while less than 18
else
  echo "No BST2.out found." >> operationsResults.txt
fi

  echo $fileNum  1>&2
  echo "Memory leak check:" >> operationsResults.txt
  (valgrind BST.out $testerDirectory/file$fileNum.txt >& out$fileNum.txt )&
  sleep 1
  pkill BST.out >& /dev/null
  pkill valgrind >& /dev/null
  rm core >& /dev/null
  rm vgcore* >& /dev/null

  if [[ -s out$fileNum.txt ]]; then
    if grep "lost.*[1-9]" out$fileNum.txt >& /dev/null ; then
      echo "Memory leak found." >> operationsResults.txt
    else
      echo "OK"  >> operationsResults.txt
      (( opScore += 4 ))
    fi
  else
    echo "Program did not terminate normally so memory leak could not checked." >> operationsResults.txt
  fi


echo $opScore   # this is the only line that goes to stdout


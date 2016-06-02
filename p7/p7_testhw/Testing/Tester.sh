#! /bin/bash

testerDirectory="/home/ssdavis/40/p7/Testing"

if [ $# -ne 1 ]; then
  echo "usage Tester.sh: $testerDirectory/Tester.sh templates.out_directory" 1>&2
  exit
fi

if [[ $1 =~ Testing ]]; then # Use from this directory is not allowed
  echo "You may not use Testing as your own source directory!"  1>&2
  exit
fi

if [[ ! -e $1/templates.out ]]; then # templates.out not found
  echo "templates.out not found in $1!"  1>&2
  exit
fi

echo $1 1>&2
cd $1
rm -f out*.txt  &> /dev/null

cp $testerDirectory/file*.txt .

fileNum=1
opScore=0

echo Operation testing:  1>&2

while [[ $fileNum -lt 9 ]]; do
  echo $fileNum  1>&2

  echo "File#: $fileNum " >> operationsResults.txt
  (templates.out file$fileNum.txt | head -100 >& out$fileNum.txt )&
  sleep 1
  pkill templates.out &> /dev/null
  rm core &> /dev/null

  if [[ -s out$fileNum.txt ]]; then
    diff out$fileNum.txt $testerDirectory/out$fileNum.txt > temp

    if [ -s temp ] ; then
      echo "Not OK" >> operationsResults.txt
      cat temp >> operationsResults.txt
    else
      echo "OK" >> operationsResults.txt
      (( opScore += 4 ))
    fi
  else
    echo "No output created so zero for operation." >> operationsResults.txt
  fi

  fileNum=$(( fileNum + 1 ))
done  # while less than 9

  echo $fileNum  1>&2
  echo "Memory leak check:" >> operationsResults.txt
  (valgrind templates.out $testerDirectory/file$fileNum.txt >& out$fileNum.txt )&
  sleep 2
  pkill templates.out >& /dev/null
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


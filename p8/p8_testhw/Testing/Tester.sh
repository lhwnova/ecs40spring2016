#! /bin/bash

testerDirectory="/home/ssdavis/40/p8/Testing"

if [ $# -ne 1 ]; then
  echo "usage Tester.sh: $testerDirectory/Tester.sh scrabble.out_directory" 1>&2
  exit
fi

if [[ $1 =~ Testing ]]; then # Use from this directory is not allowed
  echo "You may not use Testing as your own source directory!"  1>&2
  exit
fi

if [[ ! -e $1/scrabble.out ]]; then # scrabble.out not found
  echo "scrabble.out not found in $1!"  1>&2
  exit
fi

echo $1 1>&2
cd $1
rm -f out*.txt  &> /dev/null

cp $testerDirectory/File*.txt $testerDirectory/words.txt .

fileNum=1
opScore=0

echo Operation testing:  1>&2

while [ $fileNum -lt 13 ] ; do
  echo $fileNum  1>&2

  echo "File#: $fileNum " >> operationsResults.txt
  (scrabble.out File$fileNum.txt | head -10 >& out$fileNum.txt )&
  sleep 2
  pkill scrabble.out &> /dev/null
  rm core &> /dev/null

  if [ -s out$fileNum.txt ] ; then
    diff out$fileNum.txt $testerDirectory/out$fileNum.txt > temp

    if [ -s temp ] ; then
      echo "Not OK" >> operationsResults.txt
      cat temp >> operationsResults.txt
    else
      echo "OK" >> operationsResults.txt
      (( opScore += 3 ))
    fi
  else
    echo "No output created so zero for operation." >> operationsResults.txt
  fi

  fileNum=$(( fileNum + 1 ))
done  # while less than 13


echo $opScore   # this is the only line that goes to stdout


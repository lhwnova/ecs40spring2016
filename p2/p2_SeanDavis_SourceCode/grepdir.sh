#! /bin/bash

if [ $# -lt 2 ] || [ ! -d $1 ] ; then
  echo "usage: grepdir.sh directory pattern [-grep option]*"
  exit
fi

directory=$1
shift
pattern=$1
shift

for option in $* ; do
  if [[  "$option" != -* ]] ; then
    echo "usage: grepdir.sh directory pattern [-grep option]*"
    exit
  fi 
  
done

find $directory -type f -exec grep "$pattern" $* {} \;




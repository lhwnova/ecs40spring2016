#!/bin/bash

if [ $# -lt 2 ]; then
  echo "usage: grepdir.sh directory pattern [-grep option]*"
  exit
fi

path=$1
shift
pattern=$1
shift

if [[ ! -d "$path" ]] ; then
  echo "usage: grepdir.sh directory pattern [-grep option]*"
  exit
fi

option=''
for arg in $@; do
  if [[ "$arg" != -* ]] ; then
    echo "usage: grepdir.sh directory pattern [-grep option]*"
    exit
  fi
  option=$option" "$arg
done

find  $path -type f -exec grep $option $pattern {} \;

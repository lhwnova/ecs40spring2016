#! /bin/bash
# Author: Sean Davis

if [ $# -ne 3 ] || [ ! -d $1 ] || [ ! -d $2 ] || [ -f $3 ] ; then
  echo "usage: cpdirs.sh source_directory1 source_directory2 dest_directory"
  exit
fi

if [ ! -e $3 ] ; then
  mkdir $3
fi
  
for file in `ls $1` ; do
  if [ -f $1/$file ] ; then
    if [ ! -f $2/$file ] || [ $1/$file -nt $2/$file ] ; then
      cp $1/$file $3
    fi
  fi
done

for file in `ls $2` ; do
  if [ -f $2/$file ] ; then
    if [ ! -f $1/$file ] || [ $2/$file -nt $1/$file ] ; then
      cp $2/$file $3
    fi
  fi
done

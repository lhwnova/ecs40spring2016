#!/bin/bash

dir1=$1
dir2=$2
dir3=$3

if [ $# -ne 3 ] || [ ! -d "$dir1" ] || [ ! -d "$dir2" ] || [ -f "$dir3" ] ; then
  echo "usage: cpdirs.sh source_directory1 source_directory2 dest_directory"
  exit
fi

if [[ ! -e "$dir3" ]]; then
	mkdir $dir3
fi

homepath=`pwd`

for file1 in `ls $dir1`
do
  if [[ -f "$homepath/$dir1/$file1" ]]; then
    cp $homepath/$dir1/$file1 $homepath/$dir3
  fi
done

for file2 in `ls $dir2`
do
  if [[ -f "$homepath/$dir2/$file2" ]]; then
    cp $homepath/$dir2/$file2 $homepath/$dir3
  fi
done


for file1 in `ls $dir1`
do
  for file2 in `ls $dir2`
  do
    if [[ -f "$homepath/$dir2/$file2" ]] && [[ -f "$homepath/$dir1/$file1" ]] && [[ $file1 = $file2 ]]; then
      if [ $homepath/$dir1/$file1 -nt $homepath/$dir2/$file2 ]; then
      	cp -f $homepath/$dir1/$file1 $homepath/$dir3
      else
  	cp -f $homepath/$dir2/$file2 $homepath/$dir3
      fi
    fi
  done
done

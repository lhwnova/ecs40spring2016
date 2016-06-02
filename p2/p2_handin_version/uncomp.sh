#!/bin/bash

if [ $# -eq 0 ] ; then
	echo "usage: uncomp.sh {filelist}+"
  	exit
fi

for arg in $@; 
do
	case $arg in
		*.tar.gz) tar -xzf $arg ;;
		*.tgz) tar -xzf $arg ;;
                *.gz) gzip -d $arg ;;
		*.tar) tar xopf  $arg ;;
		*.zip) unzip -q $arg ;;
		*) echo "uncomp.sh: $arg has no compression extension."
	esac
	shift
done

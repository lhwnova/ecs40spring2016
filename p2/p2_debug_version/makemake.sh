#!/bin/bash

if [ $# -lt 1 ] ; then
  echo -e "Executable name required.\nusage: makemake.sh executable_name"
  exit
fi

execName=$1


shift

option='-ansi -Wall -g -c'
temp=''
for arg in $@; do
  temp=$temp" "$arg
done
option=$option$temp

optionGcc='-ansi -Wall -g -o'

echo -n "$execName :" > Makefile
for object in `ls *.cpp`
do
  echo -n " ${object%.cpp}.o" >> Makefile
done
echo -ne "\n" >> Makefile

echo -en "\tg++ $optionGcc $execName$temp" >> Makefile
for object in `ls *.cpp`
do
  echo -n " ${object%.cpp}.o" >> Makefile
done
echo -e "\n" >> Makefile


for object in `ls *.cpp`
do
  echo -n "${object%.cpp}.o : $object "  >> Makefile
  echo "`grep '^#include\s*"' $object | awk -F '"' '{ print $2 }' | tr '\n' ' '`" >> Makefile
  echo -ne "\tg++ $option $object" >> Makefile
  echo -e "\n" >> Makefile
done


echo "clean : " >> Makefile
echo -en "\trm -f $execName" >> Makefile
for object in `ls *.cpp`
do
	echo -n " ${object%.cpp}.o " >> Makefile
done
echo -ne "\n" >> Makefile>efile

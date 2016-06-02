#! /pkg/bin/bash
# Author: Sean Davis

if [ $# -eq 0 ] ; then
  echo 'usage: uncomp {filelist}+'
  exit 1
fi

for arg in $@ ; do
  case $arg in
    *.tgz) tar -xzf $arg ;;
    *.tar.gz) tar -xzf $arg ;;
    *.tar) tar -xf $arg ;;
    *.gz) gunzip $arg ;;
    *.zip) unzip -q $arg ;;
    *) echo uncomp: $arg has no compression extension.
  esac
done #for
 

#!/bin/sh

if [ -z "$1" ];
then echo "First parameter must be disc image"; exit 1;
fi;

if [ -z "$2" ];
then echo "Second parameter must be mount path"; exit 1;
fi;

hdiutil attach "$1" -mountpoint "$2"
cp -r -v img/* "$2"
hdiutil detach "$2"

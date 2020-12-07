#!/bin/bash
#@(#) Adds every file that has main function to a Makefile.am

cd src
../../../tools/automake/update_makefile.sh
cd ..

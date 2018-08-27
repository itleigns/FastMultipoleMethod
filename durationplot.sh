#!/bin/bash
make measuretimeforplot
if [ -e result.dat ]
then
    rm -f result.dat
fi
make GenerateData.exe
for i in 10 100 1000 10000 100000
do
    echo $i | mono GenerateData.exe | ./measuretimeforplot >> result.dat
done
gnuplot duration.plt
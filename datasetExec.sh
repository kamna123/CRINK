#!/bin/bash

FOLDER=/users/cse/mt/kamna/
FILES=("CSphd")

for f in ${FILES[@]}
do

for ((j=128;j<512;j*=2))
do
        for ((i=0;i<10;i++))
        do
                ./$1 $j 1 $i $FOLDER$f.mtx
                sleep 1
        done
done

for ((j=1;j<65536;j*=2))
do
        for ((i=0;i<10;i++))
        do
                ./$1 512 $j $i $FOLDER$f.mtx
                sleep 1
        done
done

for ((i=0;i<10;i++))
do
        ./$1 512 65535 $i $FOLDER$f.mtx
        sleep 1
done
done


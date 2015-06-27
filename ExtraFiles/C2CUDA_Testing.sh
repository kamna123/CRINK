#!/bin/bash

#for ((k=7000000;k<=10000000;k=k+3000000))
#do

#FILES=/users/mti/anjanas/Documents/CUDA/benchmarks/*
FOLDER=/users/cse/mt/sakansha/testing/Benchmarks/
FILES=("CSphd" "HEP-th-new")

for f in ${FILES[@]}
do

for ((j=128;j<512;j*=2))
do
	for ((i=0;i<10;i++))
	do
		./test $j 1 $i $FOLDER$f.mtx
		sleep 1
	done
done

for ((j=1;j<65536;j*=2))
do
	for ((i=0;i<10;i++))
	do
		./test 512 $j $i $FOLDER$f.mtx
		sleep 1
	done
done

for ((i=0;i<10;i++))
do
	./test 512 65535 $i $FOLDER$f.mtx
	sleep 1
done
done

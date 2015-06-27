#!/bin/bash
rm y.tab.c
lex src/ansiC.l
yacc -d -y src/cuda.y
rm bin/text
gcc -o bin/text src/dependency_abstraction_2.c src/Loop_Normalization.c src/AffineTest.c src/fdisplay_2.c src/CodeGen_1_only_WAW.c src/GCD_Banerjee_Test.c src/Omega_Test.c src/Dependence_Testing_Interface.c src/ExtendedCS.c src/Cycle_Shrinking.c src/CodeGen_ExtendedCycleShrinking.c src/CodeGen_CycleShrinking.c src/CodeGen_AffineKernel_Interface.c y.tab.c
c_extension=".c"
cu_extension=".cu"
fileName=$2$c_extension
./bin/text $1 $fileName $3 $4
fileName=$2$cu_extension
if [ "$5" == "-DTIME" -a "$6" == "-DDATASET" ]
then    nvcc $5 $6 output/$fileName -o $2
else
        if ["$5" == "-DTIME"]
        then    nvcc $5 output/$fileName -o $2
        else
                if ["$6" == "-DDATASET"]
                then    nvcc $6 output/$fileName -o $2
                else
                        nvcc output/$fileName -o $2
                fi
        fi
fi
./datasetExec.sh $2


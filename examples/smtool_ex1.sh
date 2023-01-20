#!/bin/bash 


./smtool -scale "invert { 0 2 4 5 7 9 11}"
./smtool -scale "comp { 0 2 4 5 7 9 11}"
./smtool -scale "intv vector { 0 2 4 5 7 9 11}"
./smtool -scale "nearby { 0 1 2 3 5 6 8}"


./smtool -chprog "toscale [II, V,I]"
./smtool -chprog "rand"

./smtool -read "examples/command_ex3.txt"
#being able to read the commands in a Mtool file from smtool might be the most 
#significant feature 


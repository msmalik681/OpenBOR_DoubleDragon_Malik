#!/bin/bash
path="$( dirname "$( which "$0" )" )"
cd "$path"

for i in *.wav ; do 
./wav2bor "$i" "./${i%%.*}".bor
done

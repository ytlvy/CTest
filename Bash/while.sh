#!/bin/bash

#n=1
#while [ $n -le 10 ]
#do
#echo "$n"
#	n=$(( $n + 1 ))
#done


#for (( n=1; n<=10; ++n ))
#do
#	echo "$n"
#done

for n in {1..9} ## See Brace expansion in Chapter 4
do
	x=$RANDOM
	[ $x -le 20000 ] && continue
	echo "n=$n x=$x"
done
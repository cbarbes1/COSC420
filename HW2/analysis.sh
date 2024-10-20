#!/bin/bash

mpicc -lm -o trap trapezoids.c
gcc -lm -o serial trapezoidsSerial.c

if [[ -r "output.txt" ]]; then
	rm output.txt
fi

echo "Serial"
./serial 1.0 20.0 10000000

echo "Run 1"
mpirun -np 2 trap 1.0 20.0 10000000

echo "Run 2"
mpirun -np 4 trap 1.0 20.0 10000000

echo "Run 3"
mpirun -np 8 trap 1.0 20.0 10000000

echo "Run 4"
mpirun -np 10 trap 1.0 20.0 10000000

echo "Run 5"
mpirun -np 12 trap 1.0 20.0 10000000

echo "Run 6"
mpirun -np 14 trap 1.0 20.0 10000000

echo "Run 7"
mpirun -np 16 trap 1.0 20.0 10000000

echo "Run 8"
mpirun -np 18 trap 1.0 20.0 10000000

echo "Run 9"
mpirun -np 20 trap 1.0 20.0 10000000

filename="output.txt"

if [[ -r "$filename" ]]; then
	serial=$(head -n 1 "$filename")
	echo $serial
	tail -n +2 "$filename" | while read -r p min max avg; do 
		echo $p $min $max $avg
		echo "Speedup"
		speedup=$(echo "scale=4; $serial/$max" | bc)
		echo $speedup
		echo "Efficiency"
		efficiency=$(echo "scale=4; $speedup/$p" | bc)
		echo $efficiency

		echo "Serial Fraction"
		one=1.0
		bot=$(echo "scale=4; $p/$speedup" | bc)
		numer=$(echo "scale=4; $bot - $one" | bc)
		numer=$(echo "$numer" | bc -l)
		numer=$(echo "if ($numer < 0) -($numer) else $numer" | bc -l)

		denom=$(echo "scale=4; $p - $one" | bc)
		fs=$(echo "scale=4; $numer/$denom" | bc)
		echo $fs

		echo "Parallel Fraction"
		echo $(echo "scale=4; $one-$fs" | bc)
	done
else
	echo "Error using output.txt"
	exit 1
fi

rm output.txt


if [[ -r "output.txt" ]]; then
	rm output.txt
fi

echo "Serial"
./serial 1.0 20.0 10000

echo "Run 1"
mpirun -np 2 trap 1.0 20.0 20000

echo "Run 2"
mpirun -np 4 trap 1.0 20.0 40000

echo "Run 3"
mpirun -np 8 trap 1.0 20.0 80000

echo "Run 4"
mpirun -np 10 trap 1.0 20.0 100000

echo "Run 5"
mpirun -np 12 trap 1.0 20.0 120000

echo "Run 6"
mpirun -np 14 trap 1.0 20.0 140000

echo "Run 7"
mpirun -np 16 trap 1.0 20.0 160000

echo "Run 8"
mpirun -np 18 trap 1.0 20.0 180000

echo "Run 9"
mpirun -np 20 trap 1.0 20.0 200000

filename="output.txt"

if [[ -r "$filename" ]]; then
	serial=$(head -n 1 "$filename")
	echo $serial
	tail -n +2 "$filename" | while read -r p min max avg; do 
		echo $p $min $max $avg
		echo "Speedup"
		
		speedup=$(echo "scale=4; $p * ($serial/$max)" | bc)
		echo $speedup
		echo "Efficiency"
		efficiency=$(echo "scale=4; $speedup/$p" | bc)
		echo $efficiency

		echo "Serial Fraction"
		one=1.0
		bot=$(echo "scale=4; $p/$speedup" | bc)
		numer=$(echo "scale=4; $bot - $one" | bc)
		numer=$(echo "$numer" | bc -l)
		numer=$(echo "if ($numer < 0) -($numer) else $numer" | bc -l)

		denom=$(echo "scale=4; $p - $one" | bc)
		fs=$(echo "scale=4; $numer/$denom" | bc)
		echo $fs

		echo "Parallel Fraction"
		echo $(echo "scale=4; $one-$fs" | bc)
	done
else
	echo "Error using output.txt"
	exit 1
fi

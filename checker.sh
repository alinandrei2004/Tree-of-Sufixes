#!/bin/bash
#//////////////////////////////////////////////////////
#	Created by Lucian Grigore on 25.04.2024
#	Copyright (c) 2024 Lucian Grigore. All rights reserved.
#	Checker Tema 2 - Structuri de date și algoritmi
#	Arbori de sufixe
#	Facultatea de Automatica si Calculatoare
#	Anul Universitar 2023-2024, Seria CD
#/////////////////////////////////////////////////////
rm -rf tests/output/*
result1=0
result2=0
result3=0
result4=0
result=0
bonus=0
depunctari=0
ZERO=0
BEST=95
VALGRIND="valgrind --leak-check=full --track-origins=yes -q --log-file=rezultat_valgrind.txt"
RANKS=(3 2 7 1 5 4 6 4 2 4)
make build

echo "Cerinta 1"
for i in {0..5}
do
	fileIn="tests/input/cerinta1/test"$i".in"
	mkdir tests/output/cerinta1 > /dev/null 2>&1
	fileOut="tests/output/cerinta1/test.out"
	refOut="tests/ref/cerinta1/test"$i".ref"
	./tema2 -c1 $fileIn $fileOut > /dev/null 2>&1
	diff $fileOut $refOut > /dev/null
	EXIT_CODE=$?
	if [ $EXIT_CODE -eq $ZERO ]
	then
		if (( i < 10 )); then
			echo "Statistici_Test  $i ................................................. PASS"
		else
			echo "Statistici_Test $i ................................................. PASS"
		fi
		result=$(awk "BEGIN {print $result+5; exit}")
		result1=$(awk "BEGIN {print $result1+5; exit}")
		if (( i < 5)); then
			$VALGRIND ./tema2 -c1 $fileIn $fileOut > /dev/null 2>&1
			if [[ -z $(cat rezultat_valgrind.txt) ]]; then
				printf "VALGRIND ........................................................... PASS\n"
				bonus=$(echo "$bonus + 1.0" | bc -l)
			else
				printf "VALGRIND ........................................................... FAIL\n"				
			fi
		fi
	else
		if (( i < 10 )); then
			echo "Statistici_Test  $i ................................................. FAIL"
		else
			echo "Statistici_Test $i ................................................. FAIL"
		fi
	fi
done

echo "Cerinta 2"
for i in {0..9}
do
	fileIn="tests/input/cerinta2/test"$i".in"
	mkdir tests/output/cerinta2 > /dev/null 2>&1
	fileOut="tests/output/cerinta2/test.out"
	refOut="tests/ref/cerinta2/test"$i".ref"
	./tema2 -c2 ${RANKS[$i]} $fileIn $fileOut > /dev/null 2>&1
	diff $fileOut $refOut > /dev/null
	EXIT_CODE=$?
	if [ $EXIT_CODE -eq $ZERO ]
	then
		if (( i < 10 )); then
			echo "Statistici_Test  $i ................................................. PASS"
		else
			echo "Statistici_Test $i ................................................. PASS"
		fi
		result=$(awk "BEGIN {print $result+2; exit}")
		result2=$(awk "BEGIN {print $result2+2; exit}")
		if (( i < 5)); then
			$VALGRIND ./tema2 -c2 ${RANKS[$i]} $fileIn $fileOut > /dev/null 2>&1
			if [[ -z $(cat rezultat_valgrind.txt) ]]; then
				printf "VALGRIND ........................................................... PASS\n"
				bonus=$(echo "$bonus + 1.0" | bc -l)
			else
				printf "VALGRIND ........................................................... FAIL\n"				
			fi
		fi
	else
		if (( i < 10 )); then
			echo "Statistici_Test  $i ................................................. FAIL"
		else
			echo "Statistici_Test $i ................................................. FAIL"
		fi
	fi
done

echo "Cerinta 3"
for i in {0..9}
do
	fileIn="tests/input/cerinta3/test"$i".in"
	mkdir tests/output/cerinta3 > /dev/null 2>&1
	fileOut="tests/output/cerinta3/test.out"
	refOut="tests/ref/cerinta3/test"$i".ref"
	./tema2 -c3 $fileIn $fileOut > /dev/null 2>&1
	diff $fileOut $refOut > /dev/null
	EXIT_CODE=$?
	if [ $EXIT_CODE -eq $ZERO ]
	then
		if (( i < 10 )); then
			echo "Statistici_Test  $i ................................................. PASS"
		else
			echo "Statistici_Test $i ................................................. PASS"
		fi
		result=$(awk "BEGIN {print $result+2; exit}")
		result3=$(awk "BEGIN {print $result3+2; exit}")
		if (( i < 5)); then
			$VALGRIND ./tema2 -c3 $fileIn $fileOut > /dev/null 2>&1
			if [[ -z $(cat rezultat_valgrind.txt) ]]; then
				printf "VALGRIND ........................................................... PASS\n"
				bonus=$(echo "$bonus + 1.0" | bc -l)
			else
				printf "VALGRIND ........................................................... FAIL\n"				
			fi
		fi
	else
		if (( i < 10 )); then
			echo "Statistici_Test  $i ................................................. FAIL"
		else
			echo "Statistici_Test $i ................................................. FAIL"
		fi
	fi
done

echo "Cerinta 4"
for i in {0..4}
do
	fileIn="tests/input/cerinta4/test"$i".in"
	mkdir tests/output/cerinta4 > /dev/null 2>&1
	fileOut="tests/output/cerinta4/test.out"
	refOut="tests/ref/cerinta4/test"$i".ref"
	./tema2 -c4 $fileIn $fileOut > /dev/null 2>&1
	diff $fileOut $refOut > /dev/null
	EXIT_CODE=$?
	if [ $EXIT_CODE -eq $ZERO ]
	then
		if (( i < 10 )); then
			echo "Statistici_Test  $i ................................................. PASS"
		else
			echo "Statistici_Test $i ................................................. PASS"
		fi
		result=$(awk "BEGIN {print $result+5; exit}")
		result4=$(awk "BEGIN {print $result4+5; exit}")
		if (( i < 5)); then
			$VALGRIND ./tema2 -c4 $fileIn $fileOut > /dev/null 2>&1
			if [[ -z $(cat rezultat_valgrind.txt) ]]; then
				printf "VALGRIND ........................................................... PASS\n"
				bonus=$(echo "$bonus + 1.0" | bc -l)
			else
				printf "VALGRIND ........................................................... FAIL\n"				
			fi
		fi
	else
		if (( i < 10 )); then
			echo "Statistici_Test  $i ................................................. FAIL"
		else
			echo "Statistici_Test $i ................................................. FAIL"
		fi
	fi
done

echo "Cerinta 1 : "$result1
echo "Cerinta 2 : "$result2
echo "Cerinta 3 : "$result3
echo "Cerinta 4 : "$result4
echo "Total     : "$result
echo "Bonus     : "$bonus
total=${result%.*}
if (( total == BEST )); then
	echo "Felicitari! Ai punctajul maxim: "$BEST"p! :)"
else
	echo "Ai acumulat "$result"p din maxim 95p! :("
fi
make clean > /dev/null 2>&1

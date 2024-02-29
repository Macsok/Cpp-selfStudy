#!/bin/bash

#-----------------------
#	expr
echo 2 + 3 is $(expr 2 + 3)
expr "2 * 3"
echo 2 * 3 is $(expr 2 + 3)

#-----------------------
#	double (( ))
a=$(( 5 + 4 ))
echo $a
(( a++ ))
echo $a
b=$(( 6 * 5 ))
echo 6 * 5 = $b

#-----------------------
#	Dlugosc zmiennej
napis="Hello World"
liczba=6543
echo napis length ${#napis}, liczba length ${#liczba}

#-----------------------
#	Funkcje
echo Podaj dwie liczby:
read num1 num2
if [ $num1 -gt $num2 ]
then
	echo Pierwsza liczba jest wieksza!
else
	echo Druga liczba jest wieksza!
fi

echo "Podaj wiek (spacja) wage:"
read wiek waga
if [ $wiek -gt 17 ] && [ $waga -gt 10 ]
then
	echo OK!
else
	echo NOT OK!
fi

#-----------------------
#	Petle
names="Andy Rob Carly"

for name in $names
do
	echo $name
done

for value in {1..7}
do
	echo $value
done

echo DONE!

for (( num = 1; num <= 5; num++ ))
do
	expr $num + 1
done

#-----------------------
#	Funkcje

echo Silnia z:
read x
silnia () {
	if [ $1 == 1 ] || [ $1 == 0 ]; then
		echo 1
	else
		wynik=$(($1 * $(silnia $(( $1-1 )))))
	fi
	echo $wynik
}
silnia x

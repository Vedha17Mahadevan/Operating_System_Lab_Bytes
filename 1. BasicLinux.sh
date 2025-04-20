#!/bin/bash

str="Hello World"
echo $str

a=8
b=2
s=$((a+b))
echo Sum of $a and $b is $s

echo "Enter the first number : "
read num1
echo "Enter the second number : "
read num2
if [ $num1 -gt $num2 ]
then
	echo $num1 is greater than $num2
elif [ $num1 -eq $num2 ]
then
	echo $num1 equal to $num2
else
	echo $num1 less than $num2
fi

echo "Enter the first number : "
read num1
echo "Enter the second number : "
read num2
echo "Enter the third number : "
read num3
if [ $num1 -gt $num2 ] && [ $num1 -gt $num3 ]
then
	echo $num1 is Greatest
elif [ $num2 -gt $num1 ] && [ $num2 -gt $num3 ]
then
	echo $num2 is the Greatest
else
	echo $num3 is the Greatest
fi

echo "Enter limit : "
read lim

num=1

echo "Natural Numbers : "

while [ $num -le $lim ]
do 
	echo $num
	num=$((num+1))
done

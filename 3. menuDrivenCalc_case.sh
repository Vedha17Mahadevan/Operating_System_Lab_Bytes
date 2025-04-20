#!/bin/bash

echo "Menu Driven Calculator"

echo "Enter the First number : "
read num1
echo "Enter the Second number : "
read num2

echo "Choose Operation : "
echo "1. Addition"
echo "2. Subtraction"
echo "3. Multiplication"
echo "4. Division"
echo "5. Modulus"

echo "Enter your choice (1/2/3/4/5) : "
read ch

case $ch in
	1) echo Sum is $((num1+num2));; 
	2) echo Difference is $((num1-num2));; 
	3) echo Product is $((num1*num2));; 
	4) if [ $num2 -eq 0 ]
			then 
				echo "Division not possible"
		  else 
		  	echo Quotient is $((num1/num2))
		  fi;;
	5) if [ $num2 -eq 0 ]
			then 
				echo "Division not possible"
		  else 
		  	echo Modulus is $((num1%num2))
		  fi;;
	*) echo "Invalid Choice!";;
esac

	


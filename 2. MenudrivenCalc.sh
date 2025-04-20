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

if [ $ch -ge 1 ] && [ $ch -le 5 ]
then
	while [ $ch -ge 1 ] && [ $ch -le 5 ]
	do
		if [ $ch -eq 1 ]
		then 
			echo Sum is $((num1+num2))
		break
		elif [ $ch -eq 2 ]
		then
			echo Difference is $((num1-num2))
		break
		elif [ $ch -eq 3 ]
		then
			echo Product is $((num1*num2))
		break
		elif [ $ch -eq 4 ]
		then
			if [ $num2 -eq 0 ]
			then 
				echo "Division not possible"
			else 
			  	echo Quotient is $((num1/num2))
			fi
		break
		elif [ $ch -eq 5 ]
		then 
			if [ $num2 -eq 0 ]
			then 
				echo "Division not possible"
			else 
			  	echo Modulus is $((num1%num2))
			fi
		break
		else
			echo "Invalid Choice"
		break
		fi
	done
else 
	echo "Invalid Choice"
fi


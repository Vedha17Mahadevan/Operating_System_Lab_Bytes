##B23CS1262
##VEDHA MAHADEVAN
##Natural Numbers

#!/bin/bash

echo "Enter limit : "
read lim

num=1

echo "Natural Numbers : "

while [ $num -le $lim ]
do 
	echo $num
	num=$((num+1))
done

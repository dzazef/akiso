#!/bin/bash
if [ -z ${1+x} ] || [ -z ${2+x} ] ; then
	echo "Uncorrect parameters"
	kill -9 $$
fi
x=0;
v1=$(date +'%d_%m_%Y_%H_%M_%S')
lynx -dump $1 > "${v1}.txt"
while [ $x -eq "0" ]
do
	sleep $2
	v2=$(date +'%d_%m_%Y_%H_%M_%S')
	lynx -dump $1 > "${v2}.txt"
	df=$(diff "${v1}.txt" "${v2}.txt")
	dfc=${#df}
	if [ $dfc -ne "0" ] ; then
		echo "Znaleziono różnicę"
		echo "Strona oryginalna: ${v1}.txt"
		echo "Strona zmieniona: ${v2}.txt"
		echo "Opis różnicy: ${v2}diff.txt"
		echo $df > "${v2}diff.txt"
		x=1
	else
		rm "${v2}.txt"
	fi
done 

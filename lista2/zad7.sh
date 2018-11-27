#!/bin/bash
for name in $PWD/*
do 
	if [ -f "$name" ];
	then
		file="$(basename "$name")"
		if [[ "$file" =~ "." ]]; 
		then 
			ext=".${file##*.}"
		else
			ext=""
		fi
		file="${file%.*}"
		file="$(echo $file | sed 's/.*/\L&/' )"
		if [ "$(basename "$name")" != "${file}${ext}" ];
		then
			mv -i "$name" "${file}${ext}"
		fi
	fi
done


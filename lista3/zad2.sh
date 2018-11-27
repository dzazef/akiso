#!/bin/bash
printf "%-7s%-7s%-7s%-7s%-7s%-7s%-4s%-20s\n" "PPID" "PID" "PGID" "SID" "STATE" "UID" "OF" "NAME" #of - open files
for namepath in `ls /proc | sort -V`;
do 
	s='^[0-9]+$'
	if [ -d "/proc/$namepath" ];
	then
		name="$(basename "$namepath")"
		if [[ $name =~ $s ]] ; 
		then
				ppid=$(cat "/proc/$name/status" | grep -w PPid: | cut -f 2)
				pid=$(cat "/proc/$name/status" | grep -w Pid: | cut -f 2)
				pgid=$(cat "/proc/$name/status" | grep -w NSpgid: | cut -f 2)
				sid=$(cat "/proc/$name/status" | grep -w NSsid: | cut -f 2)
				state=$(cat "/proc/$name/status" | grep -w State: | cut -d ' ' -f 1 | cut -f 2)
				uid=$(cat "/proc/$name/status" | grep -w Uid: | cut -f 2)
				if [[ -d "/proc/$name/fd" && -x "/proc/$name/fd" ]]; then
					openf=$(ls /proc/$name/fd | wc -l)
				else
					openf=0
				fi
				pname=$(cat "/proc/$name/status" | grep -w Name: | cut -f 2-)
				printf "%-7s%-7s%-7s%-7s%-7s%-7s%-4s%-20s\n" $ppid $pid $pgid $sid $state $uid $openf "$pname" 
		fi
	fi
done

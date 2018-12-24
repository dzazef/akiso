#!/bin/bash
#funcion called on program end
end() {
	printf "\033c"
	tput cnorm
	kill -9 $$
}
#returns uptime
get_time() {
	uptime=$(cat /proc/uptime | cut -d ' ' -f 1 | cut -d '.' -f 1)
	d=$((uptime/86400))
	uptime=$((uptime%86400))
	h=$((uptime/3600))
	uptime=$((uptime%3600))
	m=$((uptime/60))
	s=$((uptime%60))
	printf "%sd %sh %sm %ss\n" $d $h $m $s
}
#returns battery usage
get_batteryusage() {
	if [ -f "/sys/class/power_supply/BAT0/uevent" ] ; then 
		percent=$(cat /sys/class/power_supply/BAT0/uevent | grep "POWER_SUPPLY_CAPACITY=" | cut -d '=' -f 2)
	else
		percent=0
	fi
	echo $percent
}

get_loadavg() {
	cat /proc/loadavg | cut -d ' ' -f -3
}

get_int_usage() { #in bytes
	num_dev=$(cat /proc/net/dev | wc -l)
	bytes=0
	for i in `seq 3 $num_dev`
	do
		act_bytes=$(cat /proc/net/dev | sed -n ${i}p | cut -d ':' -f 2 | sed -r 's/^[^0-9]*([0-9]+).*$/\1/')
		bytes=$(( $bytes + $act_bytes ))
	done
	echo $bytes
}
#get columns and lines
get() {
	cols=$(tput cols)
	lines=$(tput lines)
}
getspeed() {
		s1=$(printf "%s" "$(get_int_usage)")
		sleep 1
		s2=$(printf "%s" "$(get_int_usage)")
		sp=$((s2-s1))
}
#set dynamic scale
scale() {
	getspeed
	sp1=$sp
	for (( i=0; $i < ${#arr[*]}; i++ )) ; do
		if [ ${arr[$i]} -gt $sp1 ] ; then
			sp1=${arr[$i]}
		fi
	done
	if [ $sp1 -gt "10485760" ] ; then
		scale='100 MB/s'
		scaleid=104857600
	elif [ $sp1 -gt "5242880" ] ; then
		scale='10 MB/s'
		scaleid=10485760
	elif [ $sp1 -gt "1048576" ] ; then
		scale='5 MB/s'
		scaleid=5242880
	elif [ $sp1 -gt "102400" ] ; then
		scale='1 MB/s'
		scaleid=1048576
	elif [ $sp1 -gt "10240" ] ; then
		scale='100 KB/s'
		scaleid=102400
	else
		scale='10 KB/s'
		scaleid=10240 
	fi
	tput cup 0 0 && printf "%-3s" $scale
	tput cup $(( $lines - 4 )) 0 && echo "0"
}
#draw graphs
graph() {
	for (( i=${#arr[*]}; $i > 0; i-- )) ; do 
		arr[$i]=${arr[$(( $i - 1 ))]}
	done
	if [ ${#arr[*]} -gt $(( $cols - 8)) ] ; then
		unset arr[$(( ${#arr[*]} - 1 ))]
	fi
	arr[0]=$sp
	numcol=$(( $lines - 4 ))
	arrsize=$(( ${#arr[*]} - 1 ))
	for i in `seq 0 $arrsize` ; do
		value=$(( ${arr[$i]} * $numcol / $scaleid ))
		for (( j=0; j < $value; j++)) ; do
			tput cup $(( $lines - 4 - $j)) $(( $cols - $i)) && echo -e "\e[91m▮\e[39m"
		done
		for j in `seq $(( $value )) $numcol` ; do
			tput cup $(( $lines - 4 - $j)) $(( $cols - $i)) && echo " "
		done
	done
	tput cup $(( $lines - 2)) 10 && echo "Load: $(get_loadavg)    Battery: $(get_batteryusage)%    Uptime: $(get_time)       "
}
get
printf "\033c"
tput civis
trap end SIGINT SIGTERM
export sp
for (( i=0; i < $(( $cols + 1 )); i++ )) ; do
	tput cup $(( $lines - 3)) $i && echo "─"
done
	
while true;
do 
	scale
	graph
done
































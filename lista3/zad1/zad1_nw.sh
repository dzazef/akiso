#!/bin/bash
end() {
	clear
	kill -9 $$
}
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

get_batteryusage() {
	psef=$(cat /sys/class/power_supply/BAT1/uevent | grep "POWER_SUPPLY_ENERGY_FULL=" | cut -d '=' -f 2)
	psen=$(cat /sys/class/power_supply/BAT1/uevent | grep "POWER_SUPPLY_ENERGY_NOW=" | cut -d '=' -f 2)
	psen=$((psen*100))
	percent=$((psen/psef))
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
	clear
	cols=$(tput cols)
	lines=$(tput lines)
}
#static elements
draw() {
	get
	for (( i=0; $i < $lines; i++ )) ; do
		tput cup $i $(( $cols / 2 )) && echo "│"
	done
	for (( i=0; $i <= $cols; i++ )) ; do
		tput cup $(( $lines / 2)) $i && echo "─"
	done
	tput cup $(( $lines / 2)) $(( $cols / 2 )) && echo "┼"
	tput cup 0 $(( $cols / 4 - 6 )) && echo "Battery usage"
	tput cup 0 $(( $cols * 3 / 4 - 3)) && echo "Uptime"
	tput cup $(( $lines / 2 + 1)) $(( $cols / 4 - 2 )) && echo "Load"
	tput cup $(( $lines / 2 + 1)) $(( $cols * 3 / 4 - 2 )) && echo "Sieć"
	tput cup 1 0 && echo "100" #max battery usage
	tput cup $(( $lines / 2 - 1)) 0 && echo "0" #min battery usage
	tput cup $(( $lines - 2 )) 0 && echo "0" # min load average
}
#set dynamic scale
scale() {
	loadmax=$(( $(printf "%s" "$(get_loadavg)" | cut -d '.' -f 1) + 1 ))
	#for item in ${array[*]} ; do
	#	if [ $(( $(echo $item | cut -d '.' -f 1) + 1)) -gt $loadmax ] ; then
	#		loadmax=$(( $(echo $item | cut -d '.' -f 1) + 1))
	#	fi
	#done
	tput cup $(( $lines / 2 + 2)) 0 && echo $(($loadmax))
}
#draw graphs
graph() {
	for (( i=${#arr[*]}; $i > 0; i-- )) ; do 
		arr[$i]=${arr[$(( $i - 1 ))]}
	done
	if [ ${#arr[*]} -gt $(( $cols / 2 - 3 )) ] ; then
		unset arr[$(( ${#arr[*]} - 1 ))]
	fi
	arr[0]=$(printf "%s" "$(get_loadavg)" | cut -d ' ' -f 1)
	numcol=$(( $lines - $lines / 2 - 4 ))
	for (( i=0; $i < ${#arr[*]}; i++ )) ; do 
		value=$(bc -l <<< "${arr[$i]}*$numcol/$loadmax")		
		value=$(echo $value | cut -d '.' -f 1)
		for (( j=0; $j < $(( $value + 1 )); j++ )) ; do
		if [ $(( $lines - 2 - $j)) -ge $(( $lines / 2 + 2)) ] ; then
			tput cup $(( $lines - 2 - $j)) $(( $cols / 2 - 1 - $i)) && echo "▮"
		fi
		done 
		for (( j=$(( $value + 1 )); $j < $(( $numcol + 1 )); j++ )) ; do
			tput cup $(( $lines - 2 - $j)) $(( $cols / 2 - 1 - $i)) && echo " "
			:
		done 		
	done	
}
tput civis
trap draw WINCH
trap end SIGINT SIGTERM
draw

while true;
do 
	scale
	graph
done
































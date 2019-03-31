#!/bin/bash

isLeap() {
	if (( ($1 % 4 == 0 && $1 % 100 != 0) || $1 % 400 == 0 )); then
		return 1
	else
		return 0
	fi
}

check_leap() {
	read -p "연도(1~9999)를 입력하세요: "
	if [[ $REPLY =~ ^[1-9][0-9]{0,3}$ ]]; then
		isLeap $REPLY
		local ret=$?
		if (( ret == 1 )); then
			echo "윤년입니다."
		else
			echo "윤년이 아닙니다."
		fi
	else
		echo -n "잘못 입력하셨습니다. "
	fi
	echo "아무 키나 누르세요..."
	read
}

disp_month() {
	read -p "연도(1~9999)와 월 입력하세요(예: 2016 2): " year month
	if  [[ ( $year =~ ^[1-9][0-9]{0,3}$ ) && ( $month =~ ^1[0-2]$|^[1-9]$ ) ]]; then
		local start_day_cnt=1
		for (( i = 1; i < $year; ++i )); do
			isLeap $i
			#local ret=$?
			(( start_day_cnt = start_day_cnt + 1 + $? ))
			(( start_day_cnt = start_day_cnt % 7 ))
		done

		local arr_day=(0 31 28 31 30 31 30 31 31 30 31 30 31)
		isLeap $year
		if (( $? == 1 )); then
			arr_day[2]=29 
		fi

		for (( i = 1; i <= $month; ++i )); do
			(( start_day_cnt = start_day_cnt + arr_day[i] ))
		done
		(( start_day_cnt = start_day_cnt % 7 ))

		echo " Su Mo Tu We Th Fr Sa"
		for (( i = 0; i < start_day_cnt; ++i )); do
			echo -n "   "
		done

		local cnt=$start_day_cnt
		for (( i = 1; i <= arr_day[month]; ++i )); do
			if (( cnt == 7 )); then
				echo
				(( cnt = 0 ))
			fi
			printf " %2d" $i
			(( cnt++ ))
		done
		echo
	else 
		echo -n "잘못 입력하셨습니다. "
	fi
	echo "아무 키나 누르세요..."
	read
}

day_of_week() {

	read -p "연과 월 그리고 일을 입력하세요(예: 2016 8 15): "
	if [[ ! $REPLY =~ ^[1-9][0-9]{0,3}\ 1?[0-9]\ [1-3]?[0-9]$ ]]; then
		echo "잘못 입력하셨습니다. 아무 키나 누르세요..."
		read
		return
	fi

	local cnt=0
	local year
	local month
	local day
	for i in $REPLY; do
		if (( ++cnt == 1 )); then
			year=$i
		elif (( cnt == 2)); then
			month=$i
		elif (( cnt == 3)); then
			day=$i
		fi
	done




	local feb_max=28
	local isleap=0
	if (( ($year % 4 == 0 && $year % 100 != 0) || $year % 400 == 0 )); then
		(( isleep = 1 ))
		(( feb_max = 29 ))
	fi

	local day_max
	if (( $i == 2 )); then
		(( day_max = feb_max ))
	elif (( $i == 1 || $i == 3 || $i == 5 || $i == 7 || $i == 8 || $i == 10 || $i == 12 )); then
		(( day_max = 31 ))
	else
		(( day_max = 30 ))
	fi

	
	local day_cnt=0
	for i in {1..12}; do
		if (( $i == $month )); then
			break
		fi
		if (( $i == 2 )); then
			((day_cnt = day_cnt + feb_max))
		elif (( $i == 1 || $i == 3 || $i == 5 || $i == 7 || $i == 8 || $i == 10 || $i == 12 )); then
			((day_cnt = day_cnt + 31))
		else 
			((day_cnt = day_cnt + 30))
		fi
	done
	((day_cnt = day_cnt % 7))


	((day_cnt++))
	local cnt=$day_cnt
	local start=1

	while true; do 
		if (( start == day )); then 
			break
		fi
		if (( cnt == 7 )); then
			(( cnt = 0 ))
		fi
		if (( $day_cnt != 0 )); then
			(( day_cnt-- ))
		else 
			(( start++ ))
			(( cnt++ ))
		fi
	done
	(( cnt = cnt % 7 ))

	case $cnt in
		0) echo -n "일" ;;
		1) echo -n "월" ;;
		2) echo -n "화" ;;
		3) echo -n "수" ;;
		4) echo -n "목" ;;
		5) echo -n "금" ;;
		6) echo -n "토" ;;
		*) ;;
	esac
	echo "요일입니다."
	echo "아무 키나 누르세요..."
	read
	return
}

disp_time() {
	trap "echo 아무 키나 누르세요...; read; return" SIGINT
	while true; do
		clear
		echo "$(date +%Y)년 $(date +%m)월 $(date +%d)일 $(date +%T) 입니다."
		echo "메뉴로 돌아가려면 'CTRL + C'를 입력하세요."
	done
	exit
	# 구현하세요.
}

select_menu() {
	clear
	echo "# 달력 프로그램 #"
	echo "-----------------"
	echo "1. 윤년 확인"
	echo "2. 달력 출력"
	echo "3. 요일 확인"
	echo "4. 현재 시간 출력"
	echo "-----------------"
	read -p "입력(0. 종료): "
}

while true; do
	select_menu;
	case $REPLY in
		0) exit 0;;
		1) check_leap;;
		2) disp_month;;
		3) day_of_week;;
		4) disp_time;;
		*) echo "잘못 입력하셨습니다.";read;;
	esac
done



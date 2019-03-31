#!/bin/bash

printAnykey() {
	local anyKeyComment="아무 키나 누르세요..."
	if [[ $1 ]]; then
		echo "${1} $anyKeyComment"
	else 
		echo $anyKeyComment
	fi
	read
}

insert() {
	read -p "이름: "
	if [[ ! $REPLY ]]; then
		printAnykey "이름을 입력하지 않았습니다."
	elif [[ $(find . -type f -name "$REPLY") ]]; then 
		printAnykey "이미 존재하는 이름입니다."
	else
		local name=$REPLY
		read -p "전화번호: "
		echo $REPLY > $name
		printAnykey "등록되었습니다."
	fi
}
search() {
	read -p "이름: "
	if [[ ! $REPLY ]]; then
		printAnykey "이름을 입력하지 않았습니다."
	elif [[ $(find . -type f -name "$REPLY") ]]; then 
		echo "$REPLY $(grep . "$REPLY")"
		printAnykey 
	else
		printAnykey "그런 이름은 없습니다."
	fi
}
delete() {
	read -p "이름: "
	if [[ ! $REPLY ]]; then
		printAnykey "이름을 입력하지 않았습니다."
	elif [[ $(find . -type f -name "$REPLY") ]]; then 
		rm $REPLY 
		printAnykey "삭제되었습니다."
	else
		printAnykey "그런 이름은 없습니다."
	fi
}

while true; do
	echo "# ./myphonebook"
	echo "1. 등록"
	echo "2. 검색"
	echo "3. 삭제"
	
	read -p "입력(0. 종료): "
	
	case $REPLY in
		1) insert;;
		2) search;;
		3) delete;;
		0) exit;;
		*) echo "잘못된 입력입니다."
			echo "";;
	esac
done



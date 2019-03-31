### 내장 명령어의 help
- $ help <명령어>

### 쉘스크립트 주의사항
- 공백 위치
- 백슬래시

### 쉘 스크립트임을 표시하는 해시뱅
- '#!'

### 종료 명령 exit
- 용법: $ exit <종료 코드>
- 시그널에 의해 명령이 종료되었을 때 종료 상태는 128 + 시그널 값

### 변수
- 대입 연산자 '=': 앞 뒤에 공백이 없어야 연산자로 작동한다
- 사용할 때는 '$' 기호 사용, 선언시엔 반드시 '$' 미사용

### 명령어 치환: 명령어 결과를 문자열로
- $(..): str=$(date)
- \`\`: str=\`date\`

### 단어 세기 wc
- -l 옵션을 쓰면 라인 수를 출력해줌

### 파일 쓰기
- \>: 덮어 쓰기
- \>>: 이어 쓰기


### 입력 read
- 프롬프트화 옵션: -p

### 정수형 변수
- 선언: declare -i(ex. $ declare -i num=10)
- i 옵션 필요
- 반드시 정수형만(4byte int와 동일)

### 일반 변수 Vs. 정수형 변수
```bash
$ declare -i num1=0
$ num1=10+32
$ echo $num1
> 42

$ num2=0
$ num2=10+32
$ echo $num2
> 10+32
```

### let: 연산 결과 저장용 변수 선언
- $ let ret=1+1
- 수식 사이에 공백 없어야 함

### expr: 수식 연산
- 무조건 띄워야 함

### 수식 연산 ()

### bc: 부동 소수점을 처리하는 명령어
- ex. $ echo $(echo "scale=4; $n1 / $n2" | bc)
```bash
bc << EOF
echo
EOF
```

### 문자열 처리: expr, {}
- 길이: $ expr length "hello"
- 검색: $ expr index "hello" "el"
(인덱스는 1부터 시작)
- 부분 문자열 추출: $ expr substr "hello" 1 3
(시작 위치, 길이는 1부터 시작)

- 길이: $ {#str}
- 추출: $ {str:1:3}
(인덱스는 0부터 시작)
(길이를 안 쓰면 끝까지 추출함)
- 부분문자열 삭제(앞에서 최단): ${str#A*F}
- 부분문자열 삭제(앞에서 최장): ${str##A*F}

- 부분문자열 삭제(뒤에서 최단): ${str%A*F}
- 부분문자열 삭제(뒤에서 최장): ${str%%A*F}

- 처음일치하는 부분문자열 치환: ${문자열/부분문자열/치환문자열}
- 일치하는 모든 부분문자열 치환: ${문자열//부분문자열/치환문자열}

- 맨 앞에서 일치하는 부분문자열을 치환: ${문자열/#부분문자열/치환문자열}

- 맨 뒤에서 일치하는 부분문자열을 치환: ${문자열/%부분문자열/치환문자열}

### if
- 세미콜론으로 then을 올릴 수 있음
- 조건식에는 'test'를 안쓰고 '[]'를 쓸 수 있음
- '[]'를 쓸 때는 꼭 안에 양 옆에 띄어써야 함([....]: X, [ ... ]: O)
- 조건식에 명령어가 올 수 있으며 이때 종료 결과가 0이면 True로 판단
```bash
if pwd
then
	#...
fi
```

### 합성명령어: \[\[ expression \]\]
- 정규 표현식에 만족하는지를 판별하는 연산자: =~

### 산술명령식 \(\(\)\)
- 띄어쓰기 영향을 안 받으므로 권장

### case 분기문
- *: default
- 항상 각 case 부분을 ';;' 또는 ';&'로 끝내야 함
(';&': fall through)
- 패턴 부분은 정규표현식으로 매칭
```bash
case $REPLY in
	0) echo ..
		;;
	1) echo ..
		;;
	[a-z]) echo ..
		;;
	??) echo ..
		;;
	*) echo ..
		;;
```

### 삼항 연산자
- 수식 내에서 '='를 쓰려면 괄호로 묶어야 함

### 반복문 while
```bash
while <condition>
do
	printf ....
done
```
- break
- continue

### 반복문 until
- 조건이 거짓인 동안 반복

### 반복문 for
- in으로 띄어쓰기 단위로 사용 가능
- ((;;))로 c의 for처럼 사용 가능

### 배열
- 선언 & 초기화:
	-- arr=(1 2 3 4)
	-- arr=([10]="ten" [0]="zero" [33]="33")
- 참조: arr[1]
- 전체 출력: $ echo ${arr[*]}
- 사이즈: $ echo ${#arr[@]}
- 원소 삭제: $ unset arr[1]

### 변수 삭제: unset
- $ unset ${arr[*]}
- $ unset name

### 함수
```bash
# 선언
function func1 {
	...
}

func2() {
	...
}

# 변수 선언
func() {
	v1=10 			# global
	local v2=10 	# local 
	...
}

# 호출
func
func() # (X): 호출시 괄호 안 씀


# 인자 사용
func_with_arg() {
	echo $1 $2 $3
	# 인자의 수정은 불가능
	echo ${10}	# 그냥 $10으로 쓰면 $1만 처리됨
}

func_with "str1" "str2" "str3"

# 쉬프트
func_shift() {
	while [ -n "$1" ]; do
		echo $1
		shift 	# 인자를 하나씩 밀어냄
	done
}
func_shift "str1" "str2" "str3"
arr=("str1" "str2" "str3")
func_shift ${arr[*]}

# 매개변수 일괄 처리
func_shift() {
	# $*: 매개변수를 하나의 문자열로 확장
	while name in "$*"; do
		echo $name
	done

	# $@: 매개변수를 단위로 나눠서 확장
	while name in "$@*"; do
		echo $name
	done
}

# return
func() {
	# 종료 상태를 나타내는 값 이외의 값을 전달할 때는 echo
	echo "hello"
	echo "3.14"
	return 0
}
echo $(func)
echo $?   # return 값
```
- 재귀도 가능
- 함수 호출은 또 하나의 쉘이 돌아가는 것과 같다고 보면 됨

### 옵션처리
```bash
# getopts
while getopts "al" opt; do
	case $opt in
		a) echo ...;;
		l) echo ...;;
		*) echo ...;;
	esac
done

# 옵션 인자
	# 옵션 문자열의 시작을 ':'로 하면 잘못된 옵션에 대해 에러를 출력하지 않음
	# 옵션 문자 뒤에 ':'를 쓰면 OPTARG 변수로 인자를 받을 수 있음
while getopts ":a:l" opt; do
	case $opt in
		a) echo ...;;
		l) echo ...;;
		*) echo ...;;
	esac
done
```

### 시그널 반응: trap
```bash
# trap 지정
trap "echo 'get intrupt'" SIGINT

# 쉘 종료(비정상이더라도) 시 수행할 사항을 지정
trap "echo 'get intrupt'" EXIT

# trap 해제
trap -- SIGINT
```
- SIGKILL, SIGSTOP, SIGCONT는 재정의할 수 없다

### 디버깅
```bash
# 전체
#!/bin/bash -x

# 부분
set -x
...
set +x
```

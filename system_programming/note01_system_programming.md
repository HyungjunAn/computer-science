### System Programming
- OS 자원을 직접적으로 활용하는 프로그램을 작성

### OS별 C API
- Unix(Linux): System Call
- Windows: Windows API

### File System
- Linux에서 모든 것은 'File'이다.
- 파일 인터페이스(open, read, write, close 등)를 통해 모든 것을 다룰 수 있다
- VFS(Virtual File System): 
- 아스키 파일과 이진 파일을 동등하게 취급함(ex. fopen의 "r")
- 구조
```
Partition 1
Partition 2
	Boot Block: 부팅 정보
	Super Block: 현재 파티션의 메타 정보
	i-node List(i-node: 각 파일에 대한 메타 정보)
		i_node 1
	 	i_node 2
	 	i_node 3
	 	...
	 Data Block: 실제 데이터 저장 공간
Partition 3 
...
```

### OS의 진화
- 과거: 직접 장치를 사용하는데 주력
- 현대: 자원의 관리를 전적으로 OS가 담당

### User 모드와 Kernel 모드
- 일반 App은 User 모드로 실행됨
- Kernel의 코드는 반드시 Kernel 모드에서만 실행됨
- User 모드에서 Kernel 모드로의 변경을 위해서는 trap을 통한 System Call이 필요하다

### App이 직접 System Call을 할 것인가 C Lib을 통해 할 것인가
- 직접 System Call
	- Buffer 처리 등을 직접 프로그래머가 할 수 있음 
- Lib(Library Buffer)을 통한 System Call
	- System Call을 통한 오버헤드(문맥교환)을 줄일 수 있음
		(*) Buffer

```
# 표준 입출력의 Buffer 정책
1. Line: stdin, stdout
2. Full: fprintf()
3. No: stderr
!!: stdout의 라인 버퍼를 막기 위해서는 fflush가 필요
!!: fflush(stdin)은 Windows에서만 동작함, 표준이 아님
```

### fgetc의 리턴 타입 int
- 리턴 타입이 char일 경우, 바이너리 파일에 대해 제대로 동작하지 않을 수 있음
(하필 EOF와 똑같은 0xFF가 있을 수 있기 때문 [feat. 정수 승계])

### 파일 구조체가 가진 두 가지 정보
- 라이브러리 버퍼의 포인터
- offset: 어디까지 파일을 읽었는지에 대한 정보
- 구조
```
fp
	_flages
	_IO_read_ptr
	_IO_read_end
	_IO_read_base
	_fileno(file descriptor)
```

### printf에서 자리수를 변수로 조정 가능
```
printf("%*d %*d\n",
            width1, cnt1, width2, cnt2);
```

### system programming의 기본 헤더: unistd.h

### kernel 함수 manpage
- vim에서 커서를 위치시킨 후  "2, Shift + k"

### Linux 내부의 file 관리 구조
```
process
	-> task_sturct(files)
		-> struct files
			.fd_array: 
				0(stdin)
				1(stdout)
				2(stderr)
					-> struct file
						-> offset
							-> file
```

### 왜 File descriptor는 file\*가 아니라 정수형으로 관리하나
- 메모리에 Kernel이 사용하는 공간과 User가 사용할 공간이 분리되어 있음

### 라이브러리를 사용하지 않고 시스템 콜을 통해 다룰 때에도 오프셋을 지원함
- 오프셋을 변경하는 함수도 있음
	- fseek: 표준 라이브러리의 파일 오프셋을 변경
	- lseek: 커널의 파일 오프셋을 변경
	(표준 라이브러리의 오프셋은 라이브러리 버퍼가 관리하는 오프셋임, 커널의 오프셋과는 개념이 다름)

### read의 flag 옵션
- O\_CREAT: 없을때 생성,  세 번째 인자에 접근 권한을 8진수로 줘야함
- O\_RDONLY: 읽기 전용
- O\_WRONLY: 쓰기 전용
- O\_TRUNC: 열 때 파일 사이즈를 0으로 만듦

### dup()
- 인자로 전달받은 디스크립터를 가장 낮은 곳에 복사한다.
- 리다이렉션 등을 구현하기 위해서는 호출 전에 0, 1, 2 fd 등을 close 하면 됨
```
// 입력의 리다이렉션
close(0);
dup(fd);
```

### 디렉토리
- 현재 디렉토리 안에 있는 파일의 이름, 아이노드 번호를 저장함

### 디렉토리를 다루는 라이브러리 함수 struct dirent, DIR, readdir()
```c
struct dirent* p;
DIR* dp;
dp = opendir(/**/);
while ((p = readdir(dp)) != NULL) {
	printf("%s\n", p->d_name);
}
```
### 심볼릭 링크에서 stat Vs. lstat
- stat: 가리키는 대상의 정보가 나옴
- lstat: 현재 자신의 정보가 나옴
(lstat을 권장)

### 파일 타입, 권한 정보가 담긴 mode\_t

### block dev & char dev
- Block dev ex) HDD, 
- block dev, char dev는 major, minor 정보가 있음

### non zero 값을 1로 바꾸는 꿀팁 '!!'
```
a = 3;
a = !!a // a = 1
```
### 특수퍼미션 [1][2][3]
- 1: set user id bit: 프로세스 주체가 해당 파일의 소유자 권한을 가짐
- 2: set group id bit: 프로세스 주체가 해당 파일의 그룹 권한을 가짐
- 3: set sticky bit: 소유자만 삭제 가능

###  Hardlink
- link 카운트를 통해 실제 데이터를 삭제할지 여부를 판단할 수 있음
- inode 정보는 파티션의 수퍼 블록에 존재함
(그래서 파티션이 다르면 하드링크할 수 없다)

###  Symboliclink
- 마치 해당 폴더 경로가 있는 것 처럼 동작함

### 파일의 삭제 시점
- 파일에는 연결 계수(하드링크, nlink)와 참조 계수(오픈한 프로세스 수, count)가 있음
- inode의 파괴 시점은 연결 계수와 참조 계수가 모두 '0'이될 때

### 자식은 부모에게 파일 디스크럽터를 물려받음

### exit
- 자원을 반환해주고 프로세스를 종료시킴
- C 컴파일러는 main이 return되는 곳에서 자동으로 exit 함수를 호출한다
- 자식 프로세스가 exit되면 pid 정보 유지를 위해 완전히 없어지지는 않는다

### \_exit
- 자식의 종료상태 정보는 부모에게 전달될 필요가 있음(wait())
- status 값은 하위 8bit만 사용
- 성공 수행: 0, 에러: 0 이외를 반환

### wait
- 죽은 자식 프로세스 하나를 없앰, 없앤 자식 프로세스의 pid를 반환
- 자식이 없다면 0 반환
- 죽은 자식이 없고 아직 살아있는 자식이 있다면 죽은 자식이 생길때까지 대기
- wait 종료 후 인자의 값
	- 상위 8bits: 정상 종료
	- 하위 8bits: 비정상 종료

### 자식 프로세스가 좀비가 되지 않도록 부모는 wait를 항상 호출해야함

### 에러 표출 함수: perror

### 라이브러리 함수 system이 호출하는 exec 계열 함수
```c
// l(리스트형), v(벡터형)
// p: 패스 포함 유무(쓰는 것이 정신건강에 도움)
// e: 환경 변수

execl()
execlp()
execle()
execv()
execvp()
execvpe()

// 최종적으로 호출되는 함수:
execve()
```
- exec 계열은 해당 프로세스를 대상 프로세스로 대체함: 즉 호출 이후의 코드는 무의미해짐

### 새로운 프로세스의 속성
- open 시 FD\_CLOEXEC가 설정되지 않은 경우 자식 프로세스와 부모 프로세스는 파일 디스크립터를 공유함
- 시그널 처리는 default로 복원 
- 무시(SIG\_IGN)되고 있던 시그널은 계속 무시됨

### 제어 터미널을 갖는 프로세스들은 제어 터미널이 종료될 때 모두 죽게 된다.

### 새 세션 생성 setsid()
- 그룹 리더가 아닌 프로세스에 대해 새 세션을 생성
- 제어 터미널을 갖지 않음(데몬이 가능)
- 사용 시 fork 호출 후 부모를 종료시키고 자식에서 setsid를 호출

### 데몬 프로세스 Vs. 백그라운드 프로세스
- 데몬: 제어 터미널을 가지지 않는 백그라운드 프로세스
(제어터미널이 없는 프로세스는 세션ID가 0임)
(Windows에서는 데몬 프로세스를 '서비스'라 부름)

### Thread
- 가상 메모리를 공유한 프로세스
	- Windows: 원래 쓰레드 기반
	- Linux: 원래는 프로세스 기반
- 프로세스가 사용하는 메모리는 항상 연속적이어야 한다
- 어떤 프로세스가 먼저 종료될지는 알 수 없다
- 과거에는 프로세스가 물리 메모리를 직접 사용했기에 단편화를 피할 수 없었음
- 가상 메모리 기법
	- Windows: 세그먼트
	- Linux:   페이징
- 현대 OS에서 프로세스가 사용하는 논리 메모리는 연속이지만 실제 물리 메모리가 연속일 필요는 없다
- CPU MMU: 물리, 가상 주소 간 변환에 사용되는 하드웨어 유닛
(맵핑 시 발생하는 오버헤드를 줄여줌)
- Linux는 Thread를 만들때 Process와 마찬가지로 task struct가 만들어지지만 똑같은 페이지 테이블을 공유하게 된다


### Process vs Thread
- Process
1. 자신만의 주소 공간을 가짐
2. 시그널 처리의 주체는 쓰레드가 아니라 프로세스
3. 둘 이상의 프로세스가 데이터를 교환하려면 IPC가 필요

- Thread
1. 자신을 생성한 프로세스의 주소 공간을 공유
2. 데이터 교환시 IPC가 필요 없다
3. 동기화 문제 발생
4. 하나의 스레드가 비정상 종료할 경우 프로세스가 종료된다.

### Pthread
- pthread 헤더 추가 후 gcc 빌드 시 -lphtread 옵션이 필요하다
- thread도 종료를 대기해야 함
- 메인 스레드는 pid와 스레드 id가 같다
- 메인 함수가 반환하면 프로세스는 종료한다.
- 프로세스 내의 모든 스레드가 종료되어야 프로세스가 종료된다.

### 쓰레드 종료 후 리턴 값을 확인하는 함수: pthread\_join()

### gcc 컴파일 시 -D옵션으로 define을 지정할 수 있음
	$ gcc main.c -DDEBUG

### CAS(Compare and Swap) 연산
- Mutex 변수의 값 할당, 해제가 원자적으로 이뤄져야 하므로 CPU가 CAS라는 연산을 제공함

### Push & Pull 두 종류의 해결법이 있음
- Pull: 계속해서 확인
	- 반응 빠름 / CPU 계속 점유
- Push: 자고 있다가 명령이 떨어지면 수행
	- 반응 느림 / 계속 점유하지 않음

### Dead Lock 회피
- 재귀 함수의 재귀 호출부 전에 단순히 lock을 하면 안됨
- recursive mutex lock이 필요함
- 생산자 소비자 패턴에서
	- pthread\_cond\_signal()

### 여러 개의 Lock을 사용할 때
- 반드시 같은 순서로 Lock을 해야하고
- Lock을 한 반대 순서로 unLock을 해야 함

### Spin Lock Vs. Sleep Lock
- Spin: 계속 확인
- Sleep: 깨워줄때까지 딴짓

### 생산자 소비자 패턴
- Buffer는 상호 배제가 구현되어야 한다.
- pthread\_cond\_wait()는 대기상태 전에 unlock을 하고 대기 후 lock을 건다
- pthread\_cond\_signal()은 pthread\_cond\_wait()가 호출되게 한다.
```c
// Thread 1
pthread_mutex_lock();
decode();
pthread_cond_signal();
pthread_mutex_unlock();

// Thread 2
pthread_mutex_lock();
pthread_cond_wait();
	- unlock
	- waiting
	- lock
play();
pthread_mutex_unlock();

```

### 재진입 가능 함수
- 스레드 안전
- 재귀 함수로 돌릴 수 있다
- 정적 메모리를 사용하지 않는다

### 스레드 안전 함수
- 두 개 이상의 스레드가 같은 함수를 동시에 호출할 때 정상 동작하는 함수를 의미

### 재진입 불가능 함수를 재진입 가능으로 바꾸는 기법 2가지
- Linux: 재진입 가능 버전의 함수를 별도로 제공
- Windows: 각 스레드의 고유한 정적 메모리를 만듦
	- TLS(Thread Local Storage)
	- TSS(Thread Specific Storage)
	- 만드는 방법 2가지
		- 정적: 컴파일러가 지원하는 확장 명령
			(gcc의 경우 static 뒤에 '__thread' 추가)
		- 동적: pthread 라이브러리 함수를 통해 가능
	- 전역, 정적 변수에 대해서만 가능함

### Signal
- Signal에 반응 세 가지
	- 무시, 보류, 종료, 특정함수 호출 
- 프로세스간 동기화에 사용
- 중복 발생된 시그널은 누적되지 않는다

### 재정의되지 않는 Signal
- SIGKILL, SIGSTOP

### kill 함수
- signal 0을 전송하면 해당 pid의 프로세스가 존재하는지를 파악할 수 있음

### sleep 함수는 내부적으로 프로세스를 INTERUPTIBLE 상태가 됨
- Ctrl + C를 날리면 깨어나게 됨

### alarm

### Signal Set
- sigemptyset()
- sigfillset()
- sigaddset()
- sigdelset()
- sigismember()

### Signal Block
- 시그널 자체를 아예 받지 않음

### Signal Pending
- sigpending()함수를 통해 Block 중에 받았던 signal을 알아낼 수 있음
- Signal 핸들러가 signal을 처리하고 나면 해당 set bit가 0으로 바뀐다

### Pipe
- 프로세스간 단방향 통신
- 각자가 사용하지 않는 파일 디스크럽터는 close해야 한다.
	- 해당 프로세스가 없어질 때 file 구조체가 없어질 수 있기 때문

### Message Queue
- 사용자 정의 msg의 첫 번째 원소는 반드시 long 타입 이어야 한다.

### sem\_flag = UNDO
- p 연산이 진행 중인 프로세스에 인터럽트시 자동으로 v 연산이 되도록 함
(데드락을 피해줌)

### System V의 IPC
- 프로세스 접근의 참조 카운터가 없음
(파괴에 대해 안전성을 보장받지 못함)

### TCP/IP

### Endian을 꼭 맞춰야함
- Network는 Big Endian으로 통일하기로 약속
- 항상 보내기전에 htonl()함수와 같은 엔디안 변환 함수 사용이 필요

### 현대 네트워크 체계
- CIDR 

### TCP
- Three Way Hand Shaking

### 서버 제작의 4단계
### 클라이언트 제작의 2단계

### 서버 제작시 TIME\_WAIT에 빠지지 않게 처리를 해야만 한다.

### 동시 처리 서버 구현의 3가지 방법
- fork(): 하나의 프로세스에 문제가 생겨도 다른 곳에 영향을 안 줌
	- accept 한 후에 fork(): fd를 물려줘야 하니까
	- fork 후에 server sock을 close: 사용하지 않는 fd의 참조계수를 없애야 하니까
	- 좀비 방지: signal을 통해 비동기적으로 처리해야 함
- create\_pthread(): 데이터 공유가 쉽다, 문맥 교환 비용이 적음, 안정성 확보가 어려움
	- thread\_routine()에  csock을 넘길때 값을 넘겨야 함: while이 돌면서 csock 변수에 다른 주소가 들어갈 수 있음
	- thread\_detach(): 좀비 쓰레드를 비동기적으로 처리하긴 어려움, 쓰레드가 종료될때 자동으로 메모리를 반환하게 해야함
- poll / epoll: 멀티 플렉싱 기반 서버
	- multiplexing IO: 해당 디스크립터의 수신 버퍼에 데이터가 존재함을 감지하는 시스템 콜
	(read로 인한 block을 막을 수 있음)
	- poll
		- 연결 종료시 pollfd 배열을 정리해야만 함		
		- poll이 성능이 그렇게 좋지는 않음(계속 loop로 체크해야 하니까)
		- epoll은 event가 발생한 fd만 찾을 수 있음, 연결 관리를 커널이 함(poll보다 성능 좋고 편리)
	- epoll
		- epoll_create1(): 'epoll_create()'은 쓰면 안됨

### 고성능 IO multiplexing
- Linux:   epoll
- Windows: IOCP(성능이 좋음)
- Solaris: kqueue

### void\* 타입을 int로 변경할 때는 단순 캐스팅하면 안된다
- 아키텍쳐에 따라 바이트 사이즈가 다를 수 있기 때문

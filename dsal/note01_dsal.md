### 이진 트리
- 포화: n레벨 트리에 대해 노드가 2^n - 1개 있는 트리
- 완전: 포화 이진 트리에서 말단 노드가 오른쪽에서부터 연속적으로 없는 트리

### 트리 순회
- preorder(전위): 노드 먼저: 노 왼 우
- inorder(중위): 노드를 중간에: 왼 노 우
- postorder(후위): 노드를 제일 마지막에: 왼 우 노

### HASH
- 위변조를 판단할 때 쓸 수 있음
(전송 전후의 데이터 해시 코드가 같은지를 보면 됨)
- 데이터 --(해시 함수)--> 해시 코드(해시 테이블의 인덱스로 사용)
- 검색의 시간 복잡도가 상수라서 굉장히 빠름
- 슬롯 <- 버킷 <- 테이블
- 충돌을 회비하는 2가지 방법
	-- Open addressing: 다른 곳에 넣음
	-- Chaining: 연달아 붙이기
- Synonym: 같은 해시 값을 갖는 레코드들의 집합
- Table overflow가 일어났을 때 테이블 사이즈를 재조정하는 것은 rehashing 문제 등 까다로운 요소가 많음

### Dan Bernstein의 djb2 알고리즘(문자열 해싱)
```cpp
unsigned long hash(unsigned char *str) {
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
		hash = ((hash<<5) + hash) + c; 
		/* hash * 33 + c */
	return hash;
}
```

### 그래프(Graph)의 종류
- 방향 or 무방향
- 완전
- 부분
- 가중치

### DFS & BFS
- DFS: stack
- BFS: queue
```cpp
BFS(G, s) {
	Enqueue(Q, s);
	while size(Q) != 0;
		u <- Dequeue(Q);
		for v in ...
			enqueue(Q, v);
}

```

### 최단경로문제 의사 코드
```cpp
Generic-Single_soure(G, w, s)
	INITALISE-SINGLE-SOURCE(G, s)
	repeat
		for each edge (u,v) ∈ E
			RELAX(u, v w)
	until there is no change
```

### 문자열 매칭 KMP
- 동일한 접두, 접미 문자열의 길이를 배열에 저장해둠
- 이후 검색 시 불일치 지점에서 현재 일치 접두어 길이만큼 검색 시작 지점을 쉬프트

### Dynamic Programming
- 동적 테이블을 만들어두는 것을 의미
- 재귀를 통해 호출하면서 테이블을 채우는 것을 '상향식 DP'라 부르기도 함

### ?? 
- prestanding, free standing
- 커널은 C를 include 한다
- "%d %d" vs "%d%d"
- 식별자 설명 필요

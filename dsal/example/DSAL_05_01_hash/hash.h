#ifndef HASH_H_
#define HASH_H_
#include <stdbool.h>
#define EMPTY -1
typedef struct _node Node;
typedef struct _hash Hash;

struct _node {
	int key;
	Node *next;
};

struct _hash {
	Node *hash; /* Node 형태로 저장되는 해시 테이블 */
	int size; /* hash table 크기 (bucket 크기) */
	int dataCnt; /* hash table내의 데이터의 개수 */
};

bool createHash(Hash *hsp, int size); /* 해시 생성 및 초기화 함수 */
int hashFunction(Hash *hsp, int key); /* 해시 값 계산 함수 */
bool hashInput(Hash *hsp, int iData); /* 해시에 데이터 삽입함 */
int hashSearch(Hash *hsp, int sData); /* 해시에서 데이터를 찾음 */
bool hashDelete(Hash *hsp, int dData); /* 해시에 데이터 삭제함 */
void destroyHash(Hash *hsp); /* 해시 소멸 함수 */
void hashPrint(Hash *hsp); /* 테스트용 함수 - 해시 테이블의 내용 출력 */


#endif /* HASH_H_ */

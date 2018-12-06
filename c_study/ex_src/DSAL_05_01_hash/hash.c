#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
/*--------------------------------------------------------------------------------------
Function name	: createHash() - 해시 생성 및 초기화 함수
Parameters		: hsp - 해시관리 구조체의 주소,  size - 해시 테이블의 사이즈
Returns			: 성공적으로 생성하면 true, 실패하면 false 리턴
--------------------------------------------------------------------------------------*/
bool createHash(Hash *hsp, int size) {
	int i;

	if (hsp == NULL) {
		return false;
	}
	hsp->hash = (Node *) calloc(size, sizeof(Node));
	if (hsp->hash == NULL) {
		return false;
	}
	for (i = 0; i < size; i++) {
		hsp->hash[i].key = EMPTY;
		hsp->hash[i].next = NULL;
	}
	hsp->size = size;
	hsp->dataCnt = 0;

	return true;
}
/*--------------------------------------------------------------------------------------
Function name	: hashFunction() - 해시값 계산 함수
Parameters		: hsp - 해시관리 구조체의 주소,  key - key값
Returns			: 해시값 리턴
--------------------------------------------------------------------------------------*/
int hashFunction(Hash *hsp, int key) {
	int sum = 0;

	while ((key / 10) > 0) {
		sum += key % 10;
		key /= 10;
	}
	sum += key;
	return (sum % hsp->size);
}
/*--------------------------------------------------------------------------------------
Function name	: hashInput() - 해시에 데이터 삽입 함
Parameters		: hsp - 해시관리 구조체의 주소,  iData - 해시에 저장할 값
Returns			: 성공적으로 삽입하면 true, 실패하면 false 리턴
--------------------------------------------------------------------------------------*/
bool hashInput(Hash *hsp, int iData) {
	int hashValue;
	Node *np;
	Node *newNode;

	if (hsp == NULL) {
		return false;
	}
	hashValue = hashFunction(hsp, iData);
	if (hsp->hash[hashValue].key == EMPTY) {
		hsp->hash[hashValue].key = iData;
	}
	else {
		np = &hsp->hash[hashValue];
		newNode = (Node*)malloc(sizeof(Node) * 1);
		if (newNode == NULL) {
			return false;
		}
		newNode->next = np->next;
		newNode->key = iData;
		np->next = newNode;
	}
	hsp->dataCnt++;
	return true;
}
/*--------------------------------------------------------------------------------------
Function name	: hashSearch() - 해시에서 데이터를 찾음
Parameters		: hp - 해시관리 구조체의 주소,  sData - 해시에 찾을 데이터 값
Returns			: 찾은 데이터의 해시 값, 못찾으면 -1 리턴
--------------------------------------------------------------------------------------*/
int hashSearch(Hash *hsp, int sData) {
	int hashValue;
	Node *sp;   /* 검색용 Node 포인터변수 */
	if (hsp == NULL) {  /* hsp포인터 NULL check*/
		return -1;
	}

	hashValue=hashFunction(hsp, sData);
	sp = &hsp->hash[hashValue];

	while(sp != NULL){
		if(sp->key==EMPTY){
			break;
		}
		if(sp->key == sData)  /* 검색할 데이터를 찾았으면 해시값 리턴 */
			return hashValue;
		else                  /* 못찾았으면 다음 노드로 이동 */
			sp=sp->next;
	}
	return -1;
}
/*--------------------------------------------------------------------------------------
Function name	: hashDelete() - 해시에 데이터 삭제 함
Parameters		: hsp - 해시관리 구조체의 주소,  dData - 해시에서 삭제할 값
Returns			: 성공적으로 삭제하면 true, 실패하면 false 리턴
--------------------------------------------------------------------------------------*/
bool hashDelete(Hash *hsp, int dData) {
	int hashValue = hashFunction(hsp, dData);
	Node *cur = &hsp->hash[hashValue];
	Node *delNode;
	Node *preNode;

	if (hsp == NULL) {
		return false;
	}

	while (cur != NULL) {
		if (cur->key == EMPTY) {
			break;
		}
		if (cur->key == dData) {
			if (cur == &hsp->hash[hashValue]) {	// 삭제 대상이 첫 번째 노드라면
				if (cur->next != NULL) { // 다음노드가 있다면
					delNode = cur->next;
					*cur = *delNode;
				} else {
					cur->key = EMPTY;
					delNode = NULL;
				}
			} else { // 삭제 대상이 첫 번째 노드가 아니라면
				if (cur->next != NULL) {
					preNode->next = cur->next;
					delNode = cur;
				} else {
					preNode->next = NULL;
					delNode = cur;
				}
			}
			free(delNode);
			return true;
		}
		preNode = cur;
		cur = cur->next;
	}

	return false;
}
/*--------------------------------------------------------------------------------------
Function name	: destroyHash() - 해시 소멸 함수
Parameters		: hsp - 해시관리 구조체의 주소
Returns			: 없음
--------------------------------------------------------------------------------------*/
void destroyHash(Hash *hsp) {
	int i;
	Node *np;

	if (hsp == NULL) {  /* hsp포인터 NULL check*/
		return;
	}

	for (i = 0; i < hsp->size; i++) {
		np = hsp->hash[i].next;
		while (np != NULL) {
			hsp->hash[i].next = np->next;
			free(np);
			np = hsp->hash[i].next;
		}
	}

	free(hsp->hash);
	hsp->size = 0;
	hsp->dataCnt = 0;
}
/*--------------------------------------------------------------------------------------
Function name	: hashPrint() - 해시에 저장된 데이터 출력 함수
Parameters		: hsp - 해시관리 구조체의 주소
Returns			: 없음
--------------------------------------------------------------------------------------*/
void hashPrint(Hash *hsp) {
	int i;
	Node *np;
	if (hsp == NULL) {  /* hsp포인터 NULL check*/
		return;
	}
	printf("hash data : \n");
	for(i=0; i<hsp->size; i++){
		printf("hash[%d] : ", i);
		if(hsp->hash[i].key != -1){
			printf("%5d", hsp->hash[i].key);
			np = hsp->hash[i].next;
			while(np != NULL){
				printf("%5d", np->key);
				np= np->next;
			}
			//printf("\n");
		}
		printf("\n");
	}
	return;
}

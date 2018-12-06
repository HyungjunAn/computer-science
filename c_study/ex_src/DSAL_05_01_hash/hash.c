#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
/*--------------------------------------------------------------------------------------
Function name	: createHash() - �ؽ� ���� �� �ʱ�ȭ �Լ�
Parameters		: hsp - �ؽð��� ����ü�� �ּ�,  size - �ؽ� ���̺��� ������
Returns			: ���������� �����ϸ� true, �����ϸ� false ����
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
Function name	: hashFunction() - �ؽð� ��� �Լ�
Parameters		: hsp - �ؽð��� ����ü�� �ּ�,  key - key��
Returns			: �ؽð� ����
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
Function name	: hashInput() - �ؽÿ� ������ ���� ��
Parameters		: hsp - �ؽð��� ����ü�� �ּ�,  iData - �ؽÿ� ������ ��
Returns			: ���������� �����ϸ� true, �����ϸ� false ����
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
Function name	: hashSearch() - �ؽÿ��� �����͸� ã��
Parameters		: hp - �ؽð��� ����ü�� �ּ�,  sData - �ؽÿ� ã�� ������ ��
Returns			: ã�� �������� �ؽ� ��, ��ã���� -1 ����
--------------------------------------------------------------------------------------*/
int hashSearch(Hash *hsp, int sData) {
	int hashValue;
	Node *sp;   /* �˻��� Node �����ͺ��� */
	if (hsp == NULL) {  /* hsp������ NULL check*/
		return -1;
	}

	hashValue=hashFunction(hsp, sData);
	sp = &hsp->hash[hashValue];

	while(sp != NULL){
		if(sp->key==EMPTY){
			break;
		}
		if(sp->key == sData)  /* �˻��� �����͸� ã������ �ؽð� ���� */
			return hashValue;
		else                  /* ��ã������ ���� ���� �̵� */
			sp=sp->next;
	}
	return -1;
}
/*--------------------------------------------------------------------------------------
Function name	: hashDelete() - �ؽÿ� ������ ���� ��
Parameters		: hsp - �ؽð��� ����ü�� �ּ�,  dData - �ؽÿ��� ������ ��
Returns			: ���������� �����ϸ� true, �����ϸ� false ����
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
			if (cur == &hsp->hash[hashValue]) {	// ���� ����� ù ��° �����
				if (cur->next != NULL) { // ������尡 �ִٸ�
					delNode = cur->next;
					*cur = *delNode;
				} else {
					cur->key = EMPTY;
					delNode = NULL;
				}
			} else { // ���� ����� ù ��° ��尡 �ƴ϶��
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
Function name	: destroyHash() - �ؽ� �Ҹ� �Լ�
Parameters		: hsp - �ؽð��� ����ü�� �ּ�
Returns			: ����
--------------------------------------------------------------------------------------*/
void destroyHash(Hash *hsp) {
	int i;
	Node *np;

	if (hsp == NULL) {  /* hsp������ NULL check*/
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
Function name	: hashPrint() - �ؽÿ� ����� ������ ��� �Լ�
Parameters		: hsp - �ؽð��� ����ü�� �ּ�
Returns			: ����
--------------------------------------------------------------------------------------*/
void hashPrint(Hash *hsp) {
	int i;
	Node *np;
	if (hsp == NULL) {  /* hsp������ NULL check*/
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

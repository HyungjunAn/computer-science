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
	Node *hash; /* Node ���·� ����Ǵ� �ؽ� ���̺� */
	int size; /* hash table ũ�� (bucket ũ��) */
	int dataCnt; /* hash table���� �������� ���� */
};

bool createHash(Hash *hsp, int size); /* �ؽ� ���� �� �ʱ�ȭ �Լ� */
int hashFunction(Hash *hsp, int key); /* �ؽ� �� ��� �Լ� */
bool hashInput(Hash *hsp, int iData); /* �ؽÿ� ������ ������ */
int hashSearch(Hash *hsp, int sData); /* �ؽÿ��� �����͸� ã�� */
bool hashDelete(Hash *hsp, int dData); /* �ؽÿ� ������ ������ */
void destroyHash(Hash *hsp); /* �ؽ� �Ҹ� �Լ� */
void hashPrint(Hash *hsp); /* �׽�Ʈ�� �Լ� - �ؽ� ���̺��� ���� ��� */


#endif /* HASH_H_ */

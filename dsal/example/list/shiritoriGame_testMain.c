#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "doublyLinkedlist.h"
#include "word.h"

#define POINTWORD_FILENAME  "c:/data/pointword.txt"
#define POINTWORD_CNT 5  /* ����Ʈ�ܾ� ���� */
#define INPUT_MAX_CNT 10 /* ���ӽ� �Է� ����Ƚ�� */

typedef struct _pointWord {
	char pointW[POINTWORD_CNT][50];
	int pwCnt; 
}PointWord;

int pointWordRead(PointWord *pw); /* ����Ʈ�ܾ� �Է� �޾� �����ϴ� �Լ� */
void wordGame(PointWord *pw);  /* �����ձ� ���� ó�� �Լ� */
void pointWordDisplay(PointWord *pw); /* ����Ʈ�ܾ� ��� �Լ� */
int wordAgree(List *lp, char *userWord); /* �����ձ� ���� Ȯ�� �Լ� */
int pointWordCheck(PointWord *pw, char *userWord);  /* ����Ʈ�ܾ�� ��ġ���� Ȯ�� �Լ� */

void newInput(int n, char *userWord);
/*------------------------------------------------------------------------------
 main()�Լ�
-------------------------------------------------------------------------------*/
int main()
{
	PointWord pointW;  /* ����Ʈ�ܾ� ���� ����ü ���� ���� */
	int res;  /* ����Ʈ�ܾ� ���� ������ �б�ó���� ���� ó�� ���θ� ���� ���� ���� */

    /* ����Ʈ�ܾ� �о���� */
	res = pointWordRead(&pointW);
	if (res){ /* ����Ʈ�ܾ� ���� �����б� ���� */
		printf("%s ���� ���� ����!!\n", POINTWORD_FILENAME);
		return 0;
	}

	/* �����ձ� ���� �Լ� ȣ�� */
	wordGame(&pointW);
	return 0;
}

/*------------------------------------------------------------------------------
����Ʈ�ܾ �ش� ���Ϸ� ���� �Է� �޾� �����ϴ� �Լ�
���������� ����Ǹ� 0���� / ������ ����Ǹ� 1 ����
-------------------------------------------------------------------------------*/

int pointWordRead(PointWord *pw)
{
	FILE *fp;
	int i;

	fp = fopen(POINTWORD_FILENAME, "r");
	for (i = 0; i < POINTWORD_CNT; ++i) {
		fscanf(fp, "%s", pw->pointW[i]);
	}
	pw->pwCnt = POINTWORD_CNT;
	fclose(fp);  /* ���� �ݱ� */
	return 0;    /* ���� ���� ó�� �� 0 ���� */
}

/*------------------------------------------------------------------------------
�����ձ� ���� ó�� �Լ�
-------------------------------------------------------------------------------*/
void wordGame(PointWord *pw)
{
	List wlist;
	int  score = 0;             /* ���� ���� ���� ���� */
	int  i;
	char tempWord[50];

	printf("** �����ձ� ������ �����մϴ� **\n\n");
	createList(&wlist);
	addLast(&wlist, "pointer");

	for (i = 0; i < INPUT_MAX_CNT; ++i) {
		pointWordDisplay(pw);
		printList(&wlist);
		newInput(i+1, tempWord);
		if (wordAgree(&wlist, tempWord) == 1) {
			addLast(&wlist, tempWord);
			if (pointWordCheck(pw, tempWord) == 1) {
				score += 20;
			}
		}
		else {
			printf("�߸� �Է��ϼ̽��ϴ�.\n");
		}
		printf("\n");
	}
	pointWordDisplay(pw);
	printList(&wlist);
	printf("** ����� ������ %d�� �Դϴ�.\n", score);

	destroyList(&wlist);
	return;
}
/*------------------------------------------------------------------------------
����� �Է� �ܾ ����Ʈ�ܾ�� ���Ͽ� ����Ʈ �ܾ ��������  1����
�����߸� 0����
���� ������ �ܾ�� �迭���� ���� ��
-------------------------------------------------------------------------------*/
int pointWordCheck(PointWord *pw, char *userWord)
{
	int i;
	for (i = 0; i < POINTWORD_CNT; ++i) {
		if (strcmp(pw->pointW[i], userWord) == 0) {
			pw->pointW[i][0] = '\0';
			pw->pwCnt--;
			return 1;
		}
	}
	return 0;
}
/*------------------------------------------------------------------------------
�Է´ܾ� �����ձ� ���� Ȯ��
�̾����� ���� : 1���� / �̾����� ���� : -1����
-------------------------------------------------------------------------------*/
int wordAgree(List *lp, char *userWord)
{
	Node *p = lp->tail->prev;
	return (p->data.word[strlen(p->data.word) - 1] == userWord[0])? 1: -1;
}
/*------------------------------------------------------------------------------
����Ʈ�ܾ� ��� �Լ�
-------------------------------------------------------------------------------*/
void pointWordDisplay(PointWord *pw)
{
	int i;
	printf("* ����Ʈ �ܾ� :");
	for (i = 0; i < POINTWORD_CNT; ++i) {
		if (strcmp(pw->pointW[i], "") != 0) {
			printf(" %s /", pw->pointW[i]);
		}
	}
	printf("\n");
	return;
}

void newInput(int n, char *userWord) {
	printf("�����ձ� �ܾ� �Է�(%dȸ��) : ", n);
	scanf("%s", userWord);
}

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "doublyLinkedlist.h"
#include "word.h"

#define POINTWORD_FILENAME  "c:/data/pointword.txt"
#define POINTWORD_CNT 5  /* 포인트단어 개수 */
#define INPUT_MAX_CNT 10 /* 게임시 입력 제한횟수 */

typedef struct _pointWord {
	char pointW[POINTWORD_CNT][50];
	int pwCnt; 
}PointWord;

int pointWordRead(PointWord *pw); /* 포인트단어 입력 받아 저장하는 함수 */
void wordGame(PointWord *pw);  /* 끝말잇기 게임 처리 함수 */
void pointWordDisplay(PointWord *pw); /* 포인트단어 출력 함수 */
int wordAgree(List *lp, char *userWord); /* 끝말잇기 여부 확인 함수 */
int pointWordCheck(PointWord *pw, char *userWord);  /* 포인트단어와 일치여부 확인 함수 */

void newInput(int n, char *userWord);
/*------------------------------------------------------------------------------
 main()함수
-------------------------------------------------------------------------------*/
int main()
{
	PointWord pointW;  /* 포인트단어 저장 구조체 변수 선언 */
	int res;  /* 포인트단어 저장 파일의 읽기처리에 정상 처리 여부를 리턴 받을 변수 */

    /* 포인트단어 읽어오기 */
	res = pointWordRead(&pointW);
	if (res){ /* 포인트단어 저장 파일읽기 실패 */
		printf("%s 파일 오픈 에러!!\n", POINTWORD_FILENAME);
		return 0;
	}

	/* 끝말잇기 게임 함수 호출 */
	wordGame(&pointW);
	return 0;
}

/*------------------------------------------------------------------------------
포인트단어를 해당 파일로 부터 입력 받아 저장하는 함수
정상적으로 수행되면 0리턴 / 비정상 수행되면 1 리턴
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
	fclose(fp);  /* 파일 닫기 */
	return 0;    /* 파일 정상 처리 시 0 리턴 */
}

/*------------------------------------------------------------------------------
끝말잇기 게임 처리 함수
-------------------------------------------------------------------------------*/
void wordGame(PointWord *pw)
{
	List wlist;
	int  score = 0;             /* 게임 점수 저장 변수 */
	int  i;
	char tempWord[50];

	printf("** 끝말잇기 게임을 시작합니다 **\n\n");
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
			printf("잘못 입력하셨습니다.\n");
		}
		printf("\n");
	}
	pointWordDisplay(pw);
	printList(&wlist);
	printf("** 당신의 점수는 %d점 입니다.\n", score);

	destroyList(&wlist);
	return;
}
/*------------------------------------------------------------------------------
사용자 입력 단어를 포인트단어와 비교하여 포인트 단어를 맞췄으면  1리턴
못맞추면 0리턴
맞춘 포인터 단어는 배열에서 제거 함
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
입력단어 끝말잇기 여부 확인
이어지기 성공 : 1리턴 / 이어지기 실패 : -1리턴
-------------------------------------------------------------------------------*/
int wordAgree(List *lp, char *userWord)
{
	Node *p = lp->tail->prev;
	return (p->data.word[strlen(p->data.word) - 1] == userWord[0])? 1: -1;
}
/*------------------------------------------------------------------------------
포인트단어 출력 함수
-------------------------------------------------------------------------------*/
void pointWordDisplay(PointWord *pw)
{
	int i;
	printf("* 포인트 단어 :");
	for (i = 0; i < POINTWORD_CNT; ++i) {
		if (strcmp(pw->pointW[i], "") != 0) {
			printf(" %s /", pw->pointW[i]);
		}
	}
	printf("\n");
	return;
}

void newInput(int n, char *userWord) {
	printf("끝말잇기 단어 입력(%d회차) : ", n);
	scanf("%s", userWord);
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define W_MAX 100
#define H_MAX 100


typedef struct {
	int r;
	int c;
}RC;
typedef struct Node {
	RC rc;
	struct Node* next;
	struct Node* prev;
} Node;
typedef struct {
	Node* head;
	Node* tail;
	int cnt;
} List;

typedef enum { BLANK, SNAKE, APPLE, WALL } CELL;
int w;
int h;
CELL map[H_MAX][W_MAX];

Node* mkNode(RC rc) {
	Node *pn = (Node*)malloc(sizeof(Node)*1);
	pn->next = NULL;
	pn->prev = NULL;
	pn->rc = rc;
	return pn;
}
void creatList(List* lp) {
	RC rc = {0, 0};
	lp->head = mkNode(rc);
	lp->tail = mkNode(rc);
	lp->head->prev = lp->head;
	lp->head->next = lp->tail;
	lp->tail->prev = lp->head;
	lp->tail->next = lp->tail;
	lp->cnt = 0;
}
void addFirst(List* lp, RC rc) {
	Node *pn = mkNode(rc);
	lp->head->next->prev = pn;
	pn->next = lp->head->next;
	pn->prev = lp->head;
	lp->head->next = pn;
	lp->cnt++;
}
void deleteLast(List* lp, RC* prc) {
	Node *pn = lp->tail->prev;
	pn->prev->next = lp->tail;
	lp->tail->prev = pn->prev;
	*prc = pn->rc;
	lp->cnt--;
}

RC randRC(void) {
	RC rs;
	rs.r = rand() % h;
	rs.c = rand() % w;
	return rs;
}

void setMap(void) {
	int i;
	int j;
	do {
		scanf("%d %d", &w, &h);
	}
	while (w > W_MAX || h > H_MAX);
	for (i = 0; i < h; ++i) {
		for (j = 0; j < w; ++j) {
			map[i][j] = BLANK;
		}
	}
}
void move(void);

void printMap(void) {
	int i;
	int j;
	char wall_c = '#';
	for (j = 0; j < w+2; ++j) {
		printf("%c", wall_c);
	}
	printf("\n");
	for (i = 0; i < h; ++i) {
		printf("%c", wall_c);
		for (j = 0; j < w; ++j) {
			switch (map[i][j]) {
			case BLANK: printf(" "); break;
			case SNAKE: printf("@"); break;
			case APPLE: printf("*"); break;
			}
		}
		printf("%c\n", wall_c);
	}
	for (j = 0; j < w+2; ++j) {
		printf("%c", wall_c);
	}
	printf("\n");
}

void mkApple(void) {
	RC rc;
	do {
		rc = randRC();
	}
	while (map[rc.r][rc.c] == SNAKE);
	map[rc.r][rc.c] = APPLE;
}

TCHAR getKey() {
	TCHAR ch;
	HANDLE  stdIn = GetStdHandle(STD_INPUT_HANDLE);
	DWORD   saveMode;
	GetConsoleMode(stdIn, &saveMode);
	SetConsoleMode(stdIn, ENABLE_PROCESSED_INPUT);

	if (WaitForSingleObject(stdIn, INFINITE) == WAIT_OBJECT_0) {
		DWORD num;
		ReadConsole(stdIn, &ch, 1, &num, NULL);
	}
	SetConsoleMode(stdIn, saveMode);
	return ch;
}

int main(void)
{
	srand(time(NULL));
	setMap();
	List snake;
	RC rc = randRC();
	RC delRC;
	char ch;
	creatList(&snake);
	addFirst(&snake, rc);
	map[rc.r][rc.c] = SNAKE;

	mkApple();
	while (snake.cnt != w*h) {
		system("cls");
		printMap();

		ch = getKey();
		printf("%c", ch);
		switch (ch) {
		case 'w': rc.r--; break;
		case 's': rc.r++; break;
		case 'a': rc.c--; break;
		case 'd': rc.c++; break;
		}

		addFirst(&snake, rc);
		if (map[rc.r][rc.c] == APPLE) {
			map[rc.r][rc.c] = SNAKE;
			mkApple();
		}
		else {
			map[rc.r][rc.c] = SNAKE;
			deleteLast(&snake, &delRC);
			map[delRC.r][delRC.c] = BLANK;
		}
	}
	return 0;
}

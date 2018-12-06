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
CELL map[H_MAX + 2][W_MAX + 2];

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
	rs.r = rand() % h + 1;
	rs.c = rand() % w + 1;
	return rs;
}

void setMap(void) {
	int i;
	int j;
	do {
		scanf("%d %d", &w, &h);
	}
	while (w > W_MAX || h > H_MAX);

	for (j = 0; j <= w+1; ++j) {
		map[0][j] = WALL;
	}
	for (i = 1; i <= h; ++i) {
		map[i][0] = WALL;
		for (j = 1; j <= w; ++j) {
			map[i][j] = BLANK;
		}
		map[i][j] = WALL;
	}
	for (j = 0; j <= w+1; ++j) {
		map[h+1][j] = WALL;
	}
}

void printMap(void) {
	int i;
	int j;
	for (i = 0; i <= h+1; ++i) {
		for (j = 0; j <= w+1; ++j) {
			switch (map[i][j]) {
			case BLANK: printf(" "); break;
			case SNAKE: printf("@"); break;
			case APPLE: printf("*"); break;
			case WALL:  printf("#"); break;
			}
		}
		printf("\n");
	}
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
	int isGameOver = 0;
	creatList(&snake);
	addFirst(&snake, rc);
	map[rc.r][rc.c] = SNAKE;

	mkApple();
	while (snake.cnt != w*h && !isGameOver) {
		system("cls");
		printMap();

		ch = getKey();

		if (ch == 'q') {
			break;
		}

		switch (ch) {
		case 'w': rc.r--; break;
		case 's': rc.r++; break;
		case 'a': rc.c--; break;
		case 'd': rc.c++; break;
		}

		addFirst(&snake, rc);

		switch (map[rc.r][rc.c]) {
		case APPLE:
			map[rc.r][rc.c] = SNAKE;
			mkApple();
			break;
		case SNAKE:
		case WALL:
			printf("\n\nGAME OVER\n");
			isGameOver = 1;
			break;
		default:
			map[rc.r][rc.c] = SNAKE;
			deleteLast(&snake, &delRC);
			map[delRC.r][delRC.c] = BLANK;
			break;
		}
	}
	getchar();
	getchar();
	return 0;
}

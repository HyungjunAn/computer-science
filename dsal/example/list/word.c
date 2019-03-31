#include<string.h>
#include "word.h"

void makeWord(Word *wp, const char *str) {
	wp->len = strlen(str);
	strcpy(wp->word, str);
}











#ifndef WORD_H_
#define WORD_H_

typedef struct _word
{
	char word[50];
	int  len;
}Word;
void makeWord(Word *wp, const char *str);

#endif /* WORD_H_ */

#include <stdio.h>

int getBit(int num, int i);
int setBit(int num, int i);
int clearBit(int num, int i);
int clearBitsMSBthroughl(int num, int i);
int clearBitslthrough0(int num, int i);
void printBin(int num);
int updateBit(int num, int i, int value);

int main(void) {
	int n = 182;
	printf("%d\n", n);
	printBin(n);
	n = clearBitsMSBthroughl(n, 1);
	printf("%d\n", n);
	printBin(n);
	return 0;
}

int getBit(int num, int i)
{
	int n = 1 << i;
	return ((num & n) > 0)? 1: 0;
}

int setBit(int num, int i)
{
	int n = 1 << i;
	return num | n;
}

int clearBit(int num, int i)
{
	int n = 1 << i;
	n = ~n;
	return num & n;
}

int clearBitsMSBthroughl(int num, int i)
{
	int shiftN = (31 - i);
	num <<= shiftN;
	num = (unsigned int)num >> shiftN;
	return num;
}

int clearBitslthrough0(int num, int i)
{
	int shiftN = (i+1);
	num = (unsigned int)num >> shiftN;
	num <<= shiftN;
	return num;
}

int updateBit(int num, int i, int value)
{
	if (value == 0) {
		return clearBit(num, i);
	}
	else {
		return setBit(num, i);
	}
}

void printBin(int num) {
	char bin[32];
	int i;
	for (i = 0; i < 32; ++i) {
		bin[i] = (num & 1)? '1': '0';
		num >>= 1;
	}
	int cnt = 0;
	for (i = 32 - 1; i >= 0; --i) {
		printf("%c", bin[i]);
		cnt++;
		if ((cnt % 4) == 0) {
			printf(" ");
		}
	}
	printf("\n");
}

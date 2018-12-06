#include <stdio.h>
#define CHECK (1)
#define MAX_CNT 15

int colChk[MAX_CNT+1];        // column üũ �迭 (0���� ��� ����)
int incLineChk[MAX_CNT*2+1];  // ������ �����ϴ� �밢�� üũ �迭 (0���� ��� ����)
int decLineChk[MAX_CNT*2+1];  // ������ �����ϴ� �밢�� üũ �迭 (0���� ��� ����)
int placementCnt;             // ���� ���ݸ��ϰ� ��ġ ������ ����� �� ī��Ʈ ����
int n;                        // queen�� ��(���� ��,���� ��) ���庯��
/*-------------------------------------------------------------------------------------
Function name 	: main()
------------------------------------------------------------------------------------*/
void nQueen(int row);

int main()
{
	while(1)  // ���� ������ 1~MAX_CNT �� ������ �ƴϸ� ���Է�
	{
		printf("���� ������ �Է� �Ͻÿ� : ");
		scanf("%d", &n);
		if(n>0 && n<=MAX_CNT)
			break;
	}
	nQueen(1);
	printf("��ġ ������ ����� �� : %d\n\n", placementCnt);
	getchar(); getchar();
	return 0;
}
/*------------------------------------------------------------------
Function name 	: nQueen() - n���� queen�� ��ġ�ϱ� ���� ���ȣ�� �Լ�
Parameters		: row - ü������ ���ȣ(0���� ��� ����)
Returns			: ����
------------------------------------------------------------------*/
void nQueen(int row)
{
	if (row == n+1) {
		placementCnt++;
		return;
	}

	int i;
	for (i = 1; i <= n; ++i) {
		if (colChk[i] == 0
			&& incLineChk[i+row-1] == 0
			&& decLineChk[i+n-row] == 0)
		{
			colChk[i] = 1;
			incLineChk[i+row-1] = 1;
			decLineChk[i+n-row] = 1;
			nQueen(row+1);
			colChk[i] = 0;
			incLineChk[i+row-1] = 0;
			decLineChk[i+n-row] = 0;
		}
	}
	return;
}

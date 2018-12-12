#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<algorithm>
#include<time.h>
using namespace std;
#define SUDOKUPATH  "sudoku.txt"
#define QUESPATH "ques.txt"
#define SOLUTIONPATH "solution.txt"
int num = 0;
int settle_flag = 1;
char ques_board[9][9];
void sudoku_generate(int n)
{
	char str[30];
	char line1[9] = { '5','1','2','3','4','6','7','8','9' };
	int shift[9] = { 0,3,6,1,4,7,2,5,8 };
	int pos[10] = { 0,1,2,3,4,5,6,7,8,9 };//�е����˳��

	char final[9][9];
	int i, j, k;
	int flag = 0;
	freopen(SUDOKUPATH, "w", stdout);
	do//���ɵ�һ��
	{
		memcpy(final[0], line1, sizeof(line1));
		for (i = 1; i < 9; i++)//�Ե�һ��Ϊ����������һ���վ�
		{
			for (j = 0; j < 9; j++)
			{
				final[i][j] = line1[(j + shift[i]) % 9];
			}
		}

		//��һ���վֵĻ����ϸı�4-6,7-9�е����˳�򼴿�
		do
		{
			do
			{

				if (flag)  putchar('\n');
				flag++;
				// printf("%d\n",flag);
				for (i = 0; i < 9; i++)
				{
					//sprintf(str,"%c %c %c %c %c %c %c %c %c\n",final[i][0],
					//	final[i][1], final[i][2], final[i][3], final[i][4], final[i][5], final[i][6], final[i][7], final[i][8]);
					//puts(str);
					//puts(final[i]);
					for (j = 0; j < 9; j++)
					{
						if (j != 0)putchar(' ');
						putchar(final[pos[i]][j]);
						//putchar(*(*(final + i) + j));
					}putchar('\n');
				}
				n--;
				if (!n) { return; }


			} while (next_permutation(pos + 6, pos + 9));

		} while (next_permutation(pos + 3, pos + 6));

	} while (next_permutation(line1 + 1, line1 + 9));
}


void ques_genetate()
{


	freopen("sudokubase.txt", "r", stdin);
	int pos;
	char str[20];
	pos = 1 + rand() % 1000;
	while (--pos)
	{
		for (int i = 0; i < 10; i++)
			gets_s(str);
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (j > 0)getchar();
			ques_board[i][j] = getchar();
		}getchar();
	}

	int base[9] = { 0,3,6,27,30,33,54,57,60 };
	int plus[9] = { 0,1,2,9,10,11,18,19,20 };

	for (int k = 0; k < 9; k++)//ÿ��3*3����Ϳ�2��
	{

		int i, j, hole[2];
		hole[1] = rand() % 9;
		hole[2] = rand() % 9;
		while (hole[1] == hole[2])
		{
			hole[2] = rand() % 9;
		}
		for (int t = 0; t < 2; t++)
		{
			int dot;
			dot = base[k] + plus[hole[t]];
			i = dot / 9;
			j = dot % 9;
			ques_board[i][j] = '0';

		}

	}

	//�Ѿ��Ϳ���18��
	int others;
	others = 12 + rand() % 31;//����12-41���Ϳ�����
	while (others--)
	{
		int flag = 1;
		while (flag)
		{
			int k = rand() % 81;
			int i = k / 9;
			int j = k % 9;
			if (ques_board[i][j] != '0')continue;

			flag = 0;
			ques_board[i][j] = '0';
		}
	}

	freopen(QUESPATH, "w", stdout);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (j > 0)putchar(' ');
			putchar(ques_board[i][j]);
		}putchar('\n');
	}

}

int check(int m, int n)
{
	int i, j, k;
	i = m;
	j = n;
	for (k = 0; k < 9; k++)
	{
		if (k != j)//�ж����Ƿ�����
		{
			if (ques_board[i][j] == ques_board[i][k])return 0;
		}
		if (k != i)//�ж����Ƿ�����
		{
			if (ques_board[i][j] == ques_board[k][j])return 0;
		}
	}
	if (m / 3 == 0)i = 0;
	else if (m / 3 == 1)i = 3;
	else i = 6;

	if (n / 3 == 0)j = 0;
	else if (n / 3 == 1)j = 3;
	else j = 6;

	//int sum = 0;
	for (int c = i; c<i + 3; c++)
		for (int d = j; j < j + 3; j++)
		{
			if (c != m && d != n && ques_board[m][n] == ques_board[c][d])return 0;
		}
	return 1;
}



void settle(int pos)
{
	if (pos == 81)
	{
		settle_flag = 1;
		return;
	}
	int i, j, k;
	i = pos / 9;
	j = pos % 9;

	if (ques_board[i][j] != '0')
	{
		for (k = 1; k <= 9; k++)
		{
			ques_board[i][j] = k + '0';
			if (check(i, j))
			{
				settle(pos + 1);
				//ques_board[i][j] = 0;
			}
			if (settle_flag)return;
			ques_board[i][j] = '0';
		}
	}
	else
	{
		settle(pos + 1);
	}
	if (settle_flag)return;
}

void settle_ques()
{
	char c;
	freopen(QUESPATH, "r", stdin);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			ques_board[i][j] = getchar();
		}
		getchar();
	}
	settle(0);
	freopen(SOLUTIONPATH, "w", stdout);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (j > 0)putchar(' ');
			putchar(ques_board[i][j]);
		}
		putchar('\n');
	}
}

int main(int argc, char** argv)
{

	int begintime, endtime;
	scanf("%d", &num);
	begintime = clock();
	//freopen("test.txt","w",stdout);
	sudoku_generate(num);
	endtime = clock();	//��ʱ����
	freopen("CON", "w", stdout);
	printf("\nRunning Time��%dms\n", endtime - begintime);
	system("pause");
	return 0;
}
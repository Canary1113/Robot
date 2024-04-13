#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.1415926

float DHList[6][4];

typedef struct DHList
{
	float alpha;
	float a;
	float d;
	float theta;
}DH;

typedef struct Matrix
{
	float m[4][4];
}T;


int InputDHList(DH dh[]);
T Convert(DH dh);
int OutputMatrix(T t);
int TotalMatrix(T t[], int cnt, float resultMatrix[4][4]);

int main()
{
	//input the DHList
	DH dh[100];
	int cnt = InputDHList(dh);
	T* t = (T*)malloc(cnt * sizeof(T));

	//convert the DHList to T
	for (int i = 0; i < cnt; i++)
	{
		t[i] = Convert(dh[i]);
		printf("\nT%d%d:\n", i, i + 1);
		OutputMatrix(t[i]);
	}

	//calculate the total matrix
	float resultMatrix[4][4];
	TotalMatrix(t, cnt, resultMatrix);
	printf("\nT:0%d\n", cnt);
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%.2f ", resultMatrix[i][j]);
		}
		printf("\n");
	}

	free(t); 
	return 0;
}

int InputDHList(DH dh[])
{
	printf("input the DHList, end with -1\n");
	printf("      a, alpha, d, theta\n");
	int cnt = 0;

	char inputBuffer[1024];
	while (1)
	{
		printf("NO.%d  ", cnt + 1);
		if (!fgets(inputBuffer, sizeof(inputBuffer), stdin))
		{
			break;
		}

		if (inputBuffer[0] == '-' && inputBuffer[1] == '1')
		{
			break;
		}

		if (sscanf(inputBuffer, "%f%f%f%f", &dh[cnt].alpha, &dh[cnt].a, &dh[cnt].d, &dh[cnt].theta) == 4)
		{
			cnt++;
		}
		else
		{
			printf("输入格式错误，请重新输入：a, alpha, d, theta\n");
		}
	}

	return cnt;
}

T Convert(DH dh)
{
	T t;
	float theta = dh.theta * PI / 180;
	float alpha = dh.alpha * PI / 180;

	t.m[0][0] = cos(theta);
	t.m[0][1] = -sin(theta);
	t.m[0][2] = 0;
	t.m[0][3] = dh.a;
	t.m[1][0] = sin(theta) * cos(alpha);
	t.m[1][1] = cos(theta) * cos(alpha);
	t.m[1][2] = -sin(alpha);
	t.m[1][3] = -sin(alpha) * dh.d;
	t.m[2][0] = sin(theta) * sin(alpha);
	t.m[2][1] = cos(theta) * sin(alpha);
	t.m[2][2] = cos(alpha);
	t.m[2][3] = cos(alpha) * dh.d;
	t.m[3][0] = 0;
	t.m[3][1] = 0;
	t.m[3][2] = 0;
	t.m[3][3] = 1;

	return t;
}

int OutputMatrix(T t)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%.4f ", t.m[i][j]);
		printf("\n");
	}
	return 0;
}

int TotalMatrix(T t[], int cnt, float resultMatrix[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			resultMatrix[i][j] = (i == j) ? 1.0f : 0.0f;
		}
	}

	for (int ct = 0; ct < cnt; ct++)
	{
		float temp;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				temp = 0;
				for (int k = 0; k < 4; k++)
				{
					temp += resultMatrix[i][k] * t[ct].m[k][j];
				}
				resultMatrix[i][j] = temp;
			}
		}
	}

	return 0;
}
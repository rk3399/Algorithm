#include<stdlib.h>
#include<stdio.h>
#define ARRLEN	100000000
#define ARRMAXINDEX (ARRLEN - 1)

void swap(short* arr, int index1, int index2)
{
	short temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
}
void Bubble_Sort(short* arr, int len)
{
	int swapflag = 0;
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = len - 1; j > i; j--)
		{
			if (arr[j] < arr[j - 1]) {
				swap(arr, j, j - 1);
				swapflag = 1;
			}
		}
		if (!swapflag)
			break;
		swapflag = 0;
	}
}
void Insert_sort(short* arr, int len)
{
	int temp = 0;
	for (int i = 1; i < len; i++)
	{
		temp = arr[i];
		for (int j = i - 1; j >= 0; j--)
		{
			if (temp < arr[j])
				arr[j + 1] = arr[j];
			else {
				arr[j + 1] = temp;
				break;
			}
		}
	}
}
void Shell_sort(short* arr, int len)
{
	short temp; int j;
	for (int increment = len / 2; increment > 0; increment = increment / 2)
	{
		for (int i = increment; i < len; i++)
		{
			temp = arr[i];
			for (j = i; j >= increment; j -= increment)
			{
				if (temp < arr[j - increment])
					arr[j] = arr[j - increment];
				else {
					break;
				}
			}
			arr[j] = temp;
		}
	}
}
void shell_sort(short *arr, const int start, const int end) {
	int increment = end - start + 1;	//��ʼ����������
	int temp{ 0 };
	do {	//ÿ�μ�С������ֱ��increment = 1
		increment = increment / 3 + 1;
		for (int i = start + increment; i <= end; ++i) {	//��ÿ�����ֽ���ֱ�Ӳ�������
			if (arr[i - increment] > arr[i]) {
				temp = arr[i];
				int j = i - increment;
				do {	//�ƶ�Ԫ�ز�Ѱ��λ��
					arr[j + increment] = arr[j];
					j -= increment;
				} while (j >= start && arr[j] > temp);
				arr[j + increment] = temp;	//����Ԫ��
			}
		}
	} while (increment > 1);
}

void Quick_sort(short *a, int left, int right)
{
	if (left >= right)/*�������������ڻ��ߵ����ұߵ������ʹ����Ѿ��������һ������*/
	{
		return;
	}
	int i = left;
	int j = right;
	int key = a[left];

	while (i < j)                               /*�����ڵ�����Ѱ��һ��*/
	{
		while (i < j && key <= a[j])
			/*��Ѱ�ҽ������������ǣ�1���ҵ�һ��С�ڻ��ߴ���key���������ڻ�С��ȡ����������
			���ǽ���2��û�з�������1�ģ�����i��j�Ĵ�Сû�з�ת*/
		{
			j--;/*��ǰѰ��*/
		}

		a[i] = a[j];
		/*�ҵ�һ������������Ͱ�������ǰ��ı����ߵ�i��ֵ�������һ��ѭ����key��
		a[left]����ô���Ǹ�key��*/

		while (i < j && key >= a[i])
			/*����i�ڵ�������ǰѰ�ң�ͬ�ϣ�����ע����key�Ĵ�С��ϵֹͣѭ���������෴��
			��Ϊ����˼���ǰ����������ӣ������������ߵ�����С��key�Ĺ�ϵ�෴*/
		{
			i++;
		}

		a[j] = a[i];
	}

	a[i] = key;/*���ڵ���������һ���Ժ�Ͱ��м���key�ع�*/
	Quick_sort(a, left, i - 1);/*�����ͬ���ķ�ʽ�Էֳ�������ߵ�С�����ͬ�ϵ�����*/
	Quick_sort(a, i + 1, right);/*��ͬ���ķ�ʽ�Էֳ������ұߵ�С�����ͬ�ϵ�����*/
					   /*��Ȼ�����ܻ���ֺܶ�����ң�ֱ��ÿһ���i = j Ϊֹ*/
}

void TraversalArr(short* arr, int len)
{
	static int TraversalCount = 0;
	printf("�� %d�α���\r\n", ++TraversalCount);
	for (int i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\r\n\r\n");
}
short arr[ARRLEN];
int main(void)
{
	for (int i = 0; i < ARRLEN; i++)
	{
		arr[i] = rand() % 10000;
	}


	//Bubble_Sort(arr, ARRLEN);

	//for (int i = 0; i < ARRLEN; i++)
	//{
	//	arr[i] = rand() % 10000;
	//}
	//Insert_sort(arr, ARRLEN);
	Shell_sort(arr, ARRLEN);
	//shell_sort(arr, 0, ARRMAXINDEX);

	//Quick_sort(arr, 0, ARRMAXINDEX);
	Bubble_Sort(arr, ARRLEN);
	TraversalArr(arr, ARRLEN);
	return 0;
}

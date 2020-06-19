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
	int increment = end - start + 1;	//初始化划分增量
	int temp{ 0 };
	do {	//每次减小增量，直到increment = 1
		increment = increment / 3 + 1;
		for (int i = start + increment; i <= end; ++i) {	//对每个划分进行直接插入排序
			if (arr[i - increment] > arr[i]) {
				temp = arr[i];
				int j = i - increment;
				do {	//移动元素并寻找位置
					arr[j + increment] = arr[j];
					j -= increment;
				} while (j >= start && arr[j] > temp);
				arr[j + increment] = temp;	//插入元素
			}
		}
	} while (increment > 1);
}

void Quick_sort(short *a, int left, int right)
{
	if (left >= right)/*如果左边索引大于或者等于右边的索引就代表已经整理完成一个组了*/
	{
		return;
	}
	int i = left;
	int j = right;
	int key = a[left];

	while (i < j)                               /*控制在当组内寻找一遍*/
	{
		while (i < j && key <= a[j])
			/*而寻找结束的条件就是，1，找到一个小于或者大于key的数（大于或小于取决于你想升
			序还是降序）2，没有符合条件1的，并且i与j的大小没有反转*/
		{
			j--;/*向前寻找*/
		}

		a[i] = a[j];
		/*找到一个这样的数后就把它赋给前面的被拿走的i的值（如果第一次循环且key是
		a[left]，那么就是给key）*/

		while (i < j && key >= a[i])
			/*这是i在当组内向前寻找，同上，不过注意与key的大小关系停止循环和上面相反，
			因为排序思想是把数往两边扔，所以左右两边的数大小与key的关系相反*/
		{
			i++;
		}

		a[j] = a[i];
	}

	a[i] = key;/*当在当组内找完一遍以后就把中间数key回归*/
	Quick_sort(a, left, i - 1);/*最后用同样的方式对分出来的左边的小组进行同上的做法*/
	Quick_sort(a, i + 1, right);/*用同样的方式对分出来的右边的小组进行同上的做法*/
					   /*当然最后可能会出现很多分左右，直到每一组的i = j 为止*/
}

void TraversalArr(short* arr, int len)
{
	static int TraversalCount = 0;
	printf("第 %d次遍历\r\n", ++TraversalCount);
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

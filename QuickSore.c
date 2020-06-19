#include<stdio.h>
#include<stdlib.h>
void swap(int *l, int a, int b)
{
	int temp = l[a];
	l[a] = l[b];
	l[b] = temp;
}
int partition(int *l, int low, int higt)
{
	int part = l[low];
	while(low < higt)
	{
		while (part <= l[higt] && low < higt)
		{
			/* code */
			higt--;
		}

		if (low < higt)
			swap(l,low,higt);
		
		while (part >= l[low] && low < higt)
		{
			/* code */
			low++;
		}
		if(low < higt)
			swap(l,low,higt);
	}
	return low;
}
void Qsqrt(int* l, int low, int higt)
{
	if (low < higt) {
		int part = partition(l, low, higt);
		Qsqrt(l, part + 1, higt);
		Qsqrt(l, low, part - 1);
	}
}
#define arrlen 10000000
int list[arrlen];// = {9,3,4,2,5,20,3,7,4,2};
int main(void)
{
	int i = arrlen;
	while(i--)
		list[i] = rand();
	Qsqrt(list, 0, arrlen - 1);

	for(int i = 0; i < 10; i++)
	{
		printf("%d ",list[i]);
	}
	return 0;
}

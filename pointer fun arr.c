#include <stdio.h>

int *fun1(int a, int b)
{
	return (int *)0xf1;
}
int *fun2(int a, int b)
{
	return (int *)0xf2;
}

int *fun3(int a, int b)
{
	return (int *)0xf3;
}
int* (*pfuns[])(int, int) = {
	fun1, 
	fun2,
	fun3
};

typedef int *(*pfunt)(int, int);
pfunt pfuns_b[] = {
	fun1,
	fun2, 
	fun3
};
//pfuns �� pfuns_b ͬΪָ�뺯��ָ������


char chs[] = "abc";
int nums[3];
int *anums[3];
int (*pnums)[3] = &nums;
// ���ȼ��� () > [] > *
//numsΪ����
//anumsΪָ������
//pnumsΪ����ָ��
int main(void)
{
	pfunt pfun;
	char con = ({int a = 0; int b = 1; a += b; b + a;});//gnu�����﷨({}), ֵΪ���һ������ֵ
	printf(" %d", con);
	printf(" %p %p %p", chs, &chs, &chs[0]);
	printf(" %p %p %p", chs/*�ַ����������׵�ַ*/ + 1, &chs/*��������ָ��*/ + 1);
	printf(" %p", pfuns[0](1, 2));
	pfun = fun1;
	printf(" %p", pfun(1, 2));
	pfun = pfuns[0];
	printf(" %p", pfun(1, 2));

	printf(" %d %d", sizeof(anums), sizeof(pnums));
	printf(" %p %p", anums, pnums);
	return 0;
}
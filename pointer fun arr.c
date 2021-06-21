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
//pfuns 和 pfuns_b 同为指针函数指针数组


char chs[] = "abc";
int nums[3];
int *anums[3];
int (*pnums)[3] = &nums;
// 优先级： () > [] > *
//nums为数组
//anums为指针数组
//pnums为数组指针
int main(void)
{
	pfunt pfun;
	char con = ({int a = 0; int b = 1; a += b; b + a;});//gnu特有语法({}), 值为最后一条语句的值
	printf(" %d", con);
	printf(" %p %p %p", chs, &chs, &chs[0]);
	printf(" %p %p %p", chs/*字符类型数组首地址*/ + 1, &chs/*数组类型指针*/ + 1);
	printf(" %p", pfuns[0](1, 2));
	pfun = fun1;
	printf(" %p", pfun(1, 2));
	pfun = pfuns[0];
	printf(" %p", pfun(1, 2));

	printf(" %d %d", sizeof(anums), sizeof(pnums));
	printf(" %p %p", anums, pnums);
	return 0;
}
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
int *(*panums)[3] = &anums;
// 优先级： () > [] > *
//nums为数组
//anums为指针数组
//pnums为数组指针
//panums为指针数组指针
int main(void)
{
	pfunt pfun;
	char con = ({int a = 0; int b = 1; a += b; b + a;});//gnu特有语法({}), 值为最后一条语句的值
	printf(" %d", con);
	printf(" %d", con ?: 3);//gnu特有语法 等同于con ? con : 3
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

/**********************************************************************************************
#define cat(x,y) x##y
#define defcat(x,y) cat(x,y)

#define ToString(x) #x
#define defToString(x) ToString(x)


//#define u1 usart1
//#define hd handler
//char *str = defToString(defcat(u1, hd)); //"usart1handler"
//char *str1 = defToString(cat(u1, hd));   //"u1hd"
//char *str2 = ToString(defcat(u1, hd));   //"defcat(u1, hd)"
//char *str3 = ToString(cat(u1, hd));      //"cat(u1, hd)"

***********************************************************************************************/


/**********************************************************************************************
typedef void (*init_fun)(void);
#define __Init(x)  static void x(void); init_fun __attribute__((unused, section("myinit"))) __init_fun_##x = x; 
__Init(f1_init);
void f1_init(void)
{
	
}

__Init(f2_init);
void f2_init(void)
{
	
}

extern init_fun myinit$$Base;
extern init_fun myinit$$Limit;

void SystemInitPtr(void)
{
	for(init_fun *Init_Ptr = &myinit$$Base; Init_Ptr < &myinit$$Limit; Init_Ptr++)
	{
		(*Init_Ptr)();
	}
}
***********************************************************************************************/



/**********************************************************************************************
//const 用法
//基本用法
//const int value = 0;
//value = 1;  不合法


//关于const的指针和数组指针
//const int *point_a = 0;
//int *const point_b = 0;
//int arr_c[1]; 

//point_a = point_b;//合法
//*point_a = 1;//不合法
//point_b = point_a;//不合法
//*point_b = 1;//合法
//arr_c = 0;不合法
//总结：const修饰的什么，什么就是只读的
//const int *point_a = 0;修饰的int *,是一个内存上地址，本质是内存，所以这个地址的内存是只读的
//int *const point_b = 0;//修饰的point_b,是一个指向内存的指针变量,本质是一个无符号整型变量，所以这个无符号整型变量是只读的
//arr_c作为数组指针不可以被赋值，类似于point_b

//地址=指针，和指针变量有本质区别
//地址（指针）是没有类型的，指针变量在定义时就确定了类型
//指针变量的类型不可以改变，指针变量指向的地址可以强转为任意类型
/*****************************************/

/* 关于结构体和联合体 */
//结构体和联合体本质上都是一段连续的地址(所有类型都可以这样理解)
//结构体的不同成员有着不同的长度，相对于结构体基地址有着不同的偏移量
//联合体的不同成员有着不同的长度，相对于联合体基地址都没有偏移，或者说都是偏移量都是0。
//结构体的长度由所有成员的长度相加决定，联合体的长度由所有成员中的最大长度决定
//位段：位段显式的指明了一个成员的长度（bit数），在结构体中使用位段尽量先联合为一个标准长度
//对齐：对于长度不能整除对齐量（求余不为零）的成员，在成员的尾部填充（map文件中为pad）（对齐量-余数）个无实际意义的字节。以增加下一个成员的偏移量，保证所有成员的起始地址都是对齐的
//不对齐：所有成员的起始地址都紧跟上一个成员结束地址（第一个成员起始地址为基地址）



***********************************************************************************************/


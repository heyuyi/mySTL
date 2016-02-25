// basicStructureTest.cpp : 定义控制台应用程序的入口点。
// 基本数据结构测试

#include "stdafx.h"
#include "..\include\stack.h"
#include "..\include\queue.h"
#include <cstdio>
int main()
{
	int a[5] = { 1,2,3,4,5 };
	int *ptr = (int*)(&a);
	printf("%d,%d", *(a + 1), *(ptr - 1));
	return 0;
}


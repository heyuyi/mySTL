// basicStructureTest.cpp : �������̨Ӧ�ó������ڵ㡣
// �������ݽṹ����

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


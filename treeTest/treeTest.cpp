// treeTest.cpp : �������̨Ӧ�ó������ڵ㡣
// ���������ݽṹ����

#include "stdafx.h"
#include "..\include\tree.h"
#include <xtree>

//using namespace std;
using namespace mySTL;

void f1(const int& x)
{

}

int main()
{
	bs_tree<int> a(10);
	a.inorder_walk(a.root(), f1);
	return 0;
}


// treeTest.cpp : 定义控制台应用程序的入口点。
// 各种树数据结构测试

#include "stdafx.h"
#include "..\include\tree.h"

using namespace std;
using namespace mySTL;

int main()
{
	binary_search_tree<int> a;
	tree_base<int>::node_ptr x = new tree_base<int>::node_type;
	a.search(x);
	return 0;
}


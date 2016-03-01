// treeTest.cpp : 定义控制台应用程序的入口点。
// 各种树数据结构测试

#include "stdafx.h"
#include "..\include\tree.h"
#include <iostream>
#include <ctime>
#include <random>
//#include <xtree>
#include <vector>

//using namespace std;
using std::cout;
using std::endl;
using namespace mySTL;

void f1(const int& x)
{
	cout << x << endl;
}

int main()
{
	std::default_random_engine e(time(0));
	std::uniform_int_distribution<> u(0, 1000);
	std::vector<int> x;
	for (int i = 100; i > 0; --i)
		x.push_back(u(e));
	bs_tree<int> a(x.begin(), x.end());
	a.inorder_walk(f1);
	auto it = a.end();
	--it;
	a.erase(a.begin(), it);
//	std::shared_ptr<bs_tree_node<int>> a(std::make_shared<bs_tree_node<int>>(6));
//	auto b = a->value();
	return 0;
}


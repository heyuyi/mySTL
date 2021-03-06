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
	std::default_random_engine e(8);
	std::uniform_int_distribution<> u(1, 1000);
	std::vector<int> x;
	for (int i = 100; i > 0; --i)
		x.push_back(u(e));
	bs_tree<int> a(x.begin(), x.end());
	inorder_walk(a.root(), f1);
//	auto it = a.end();
//	--it;
//	--it;
//	a.erase(a.begin(), it);
	auto it = a.begin();
	++it;
	++it;
	a.erase(it, a.end());

	rb_tree<int> rb(x.begin(), x.end());
	int h = rb.black_height(rb.root());
	auto i = search(rb.root(), x[0]);
	auto j = rb.erase(i);
	h = rb.black_height(rb.root());
	return 0;
}


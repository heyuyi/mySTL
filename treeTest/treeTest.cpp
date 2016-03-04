// treeTest.cpp : �������̨Ӧ�ó������ڵ㡣
// ���������ݽṹ����

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
	std::default_random_engine e(0);
	std::uniform_int_distribution<> u(1, 10000);
	std::vector<int> x;
	for (int i = 1000; i > 0; --i)
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
	return 0;
}


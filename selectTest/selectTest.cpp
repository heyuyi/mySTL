// selectTest.cpp : 定义控制台应用程序的入口点。
// 从一组数据中选出第i小的元素

#include "stdafx.h"
#include "..\include\algorithm.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <iostream>

using namespace std;
using namespace mySTL;

int main()
{
	vector<int> a;
/*	for (int i = 1000; i > 0; --i)
		a.push_back(i);*/

	default_random_engine e(time(0));
	uniform_int_distribution<> u;	

	for (int i = 10000; i > 0; --i)
		a.push_back(u(e));

	auto x = select(a.begin(), a.end(), 10);
	sort(a.begin(), a.end());
	return 0;
}


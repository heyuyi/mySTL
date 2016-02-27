// selectTest.cpp : �������̨Ӧ�ó������ڵ㡣
// ��һ��������ѡ����iС��Ԫ��

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

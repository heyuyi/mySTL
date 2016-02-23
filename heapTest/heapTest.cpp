// heapTest.cpp : �������̨Ӧ�ó������ڵ㡣
// �����ݽṹ����

#include "stdafx.h"
#include "..\include\heap.h"
#include <vector>
#include <functional>
#include <queue>
#include <ctime>
#include <random>

using namespace std;
using namespace mySTL;

int main()
{
//	vector<int> a{ 1,2 };
//	heap<int> b(a);

//	vector<int> a{ 6,5,4,3,2,1 };
//	heap<int, greater<int>> b(a, greater<int>());

//	vector<int> a{ 1,2,3,4,5,6 };
//	heap<int> b(a.begin(), a.end());

//	heap<int> b({ 1,2 });
//	b.pop();
//	b.pop();
//	b.pop();

//	heap<int> b;
//	for (int i = 0; i < 10; ++i)
//		b.push(i);
	
	default_random_engine e(time(0));
	uniform_int_distribution<> u;
	vector<int> a;
	for (int i = 1000; i > 0; --i)
		a.push_back(u(e));

	heap<int> b;
	priority_queue<int> c;
	for (int i = 0; i < a.size(); ++i)		// 27ms
		b.push(a[i]);
	for (int i = 0; i < a.size(); ++i)		// 54ms
		c.push(a[i]);

	return 0;
}


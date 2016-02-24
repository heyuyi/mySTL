// heapTest.cpp : 定义控制台应用程序的入口点。
// 堆数据结构测试

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
	for (int i = 10000; i > 0; --i)
		a.push_back(u(e));

/*	// i									10000
	heap<int> b(a.begin(), a.end());			// 95ms
	priority_queue<int> c(a.begin(), a.end());	// 8ms
*/
	heap<int> b;
	priority_queue<int> c;
	// i							1000	|	10000
	for (int i = 0; i < a.size(); ++i)		// 27ms	|	133ms
		b.push(a[i]);
	for (int i = 0; i < a.size(); ++i)		// 54ms	|	3330ms
		c.push(a[i]);

	return 0;
}


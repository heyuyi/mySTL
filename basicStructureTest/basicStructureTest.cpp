// basicStructureTest.cpp : 定义控制台应用程序的入口点。
// 基本数据结构测试

#include "stdafx.h"
#include "..\include\stack.h"
#include "..\include\queue.h"
#include <vector>
#include <deque>
#include <iostream>

using namespace std;
using namespace mySTL;

int main()
{
	stack<int> a;
	for (int i = 0; i < 5; ++i)
		a.push(i);
	while (!a.empty()) {
		cout << a.top() << endl;
		a.pop();
	}
	cout << endl;
	queue<int> b;
	for (int i = 0; i < 5; ++i) {
		b.push(i);
		cout << b.head() << '\t' << b.tail() << endl;
	}
	cout << endl;
	while (!b.empty()) {
		cout << b.head() << '\t' << b.tail() << endl;
		b.pop();
	}
	return 0;
}


// basicStructureTest.cpp : 定义控制台应用程序的入口点。
// 基本数据结构测试

#include "stdafx.h"
#include "..\include\stack.h"
#include "..\include\queue.h"
#include <iostream>

//using namespace std;
using std::cout;
using std::endl;
using namespace mySTL;

int main()
{
/*	stack<int> a;
	for (int i = 0; i < 5; ++i)
		a.push(i);
	while (!a.empty()) {
		cout << a.top() << endl;
		a.pop();
	}
	cout << endl;
	queue<int> b;
	for (int i = 0; i < 5; ++i) {
		b.enqueue(i);
		cout << b.head() << '\t' << b.tail() << endl;
	}
	cout << endl;
	while (!b.empty()) {
		cout << b.head() << '\t' << b.tail() << endl;
		b.dequeue();
	}*/

	stack_2queue<int> a;
	int i, j = 0;
	for (i = 0; i < 5; ++i) {
		a.push(j++);
		cout << a.top() << '\t' << a.bottom() << endl;
		a.push(j++);
		cout << a.top() << '\t' << a.bottom() << endl;
		a.pop();
		cout << a.top() << '\t' << a.bottom() << endl;
	}
	cout << endl;
	queue_2stack<int> b;
	j = 0;
	for (i = 0; i < 5; ++i) {
		b.enqueue(j++);
		cout << b.head() << '\t' << b.tail() << endl;
		b.enqueue(j++);
		cout << b.head() << '\t' << b.tail() << endl;
		b.dequeue();
		cout << b.head() << '\t' << b.tail() << endl;
	}
	return 0;
}


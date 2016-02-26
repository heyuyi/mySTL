// basicStructureTest.cpp : �������̨Ӧ�ó������ڵ㡣
// �������ݽṹ����

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
		b.push(i);
		cout << b.head() << '\t' << b.tail() << endl;
	}
	cout << endl;
	while (!b.empty()) {
		cout << b.head() << '\t' << b.tail() << endl;
		b.pop();
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
		b.push(j++);
		cout << b.head() << '\t' << b.tail() << endl;
		b.push(j++);
		cout << b.head() << '\t' << b.tail() << endl;
		b.pop();
		cout << b.head() << '\t' << b.tail() << endl;
	}
	return 0;
}


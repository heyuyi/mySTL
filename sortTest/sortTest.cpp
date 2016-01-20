// sortTest.cpp : 定义控制台应用程序的入口点。
//

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
	default_random_engine e(time(0));
	uniform_int_distribution<> u;
	vector<int> a1, a2, a3, a4, a5, a6;
	clock_t start, end;

	for (int i = 10000; i > 0; --i)
		a1.push_back(u(e));
//	for (int i = 10000; i > 0; --i)
//		a1.push_back(i);
	a2 = a1; a3 = a1; a4 = a1; a5 = a1; a6 = a1;

/*
//	i =								10000		|	
	sort(a1.begin(), a1.end());			// 20ms		|
//	insertSort(a2.begin(), a2.end());	// 57s		|
//	heapSort(a3.begin(), a3.end());		// 710ms	|
	quickSort(a4.begin(), a4.end(), 0);	//159ms		|
	quickSort(a5.begin(), a5.end(), 1);	//128ms		|
	quickSort(a6.begin(), a6.end(), 2);
	*/

	cout << "data size: i = " << a1.size() << endl;
	start = clock();
	sort(a1.begin(), a1.end());
	end = clock();
	cout << "STL sort: " << end - start << endl;
	start = clock();
	quickSort(a4.begin(), a4.end(), 2);
	end = clock();
	cout << "quick sort.2: " << end - start << endl;
	return 0;
}


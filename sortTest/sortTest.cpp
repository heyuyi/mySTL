// sortTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "..\include\algorithm.h"
#include <vector>

using namespace std;
using namespace mySTL;


int main()
{
	vector<int> a;
	for (int i = 100; i > 0; --i)
		a.push_back(i);
	heapSort(a.begin(), a.end());
	return 0;
}


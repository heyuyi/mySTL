// findMaxSubarrayTest.cpp : 定义控制台应用程序的入口点。
// 最大子数组问题测试

#include "stdafx.h"
#include "..\include\algorithm.h"
#include <vector>
#include <ctime>
#include <random>

using namespace std;
using namespace mySTL;

int main()
{
	default_random_engine e(time(0));
	uniform_int_distribution<> u(-1000, 1000);
//	vector<int> a{ 13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 };
//	vector<int> a{ 1,-2,3,-4 };
	vector<int> a;
	for (int i = 10000; i > 0; --i)
		a.push_back(u(e));

	auto x1 = find_max_subarray(a.begin(), a.end());		//147ms
	auto x2 = find_max_subarray_m(a.begin(), a.end());	//14ms
	return 0;
}


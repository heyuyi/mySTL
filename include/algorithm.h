#pragma once
#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <type_traits>

namespace mySTL {
// some kinds of sort algorithm
// insertion-sort
template<typename _TIt, 
	typename _FPtr> inline
	void insert_sort(_TIt beg, _TIt end, _FPtr func)
	{
		_TIt it1, it2;
		for (it1 = beg + 1; it1 != end; ++it1) {
			auto val = *it1;
			for (it2 = it1; it2 != beg && func(val, *(it2 - 1)); --it2)
				*it2 = *(it2 - 1);
			*it2 = val;
		}
	}

template<typename _TIt> inline
	void insert_sort(_TIt beg, _TIt end)
	{
		insert_sort(beg, end, std::less<decltype(*beg)>());
	}

// bubble-sort
template<typename _TIt,
	typename _FPtr> inline
	void bubble_sort(_TIt beg, _TIt end, _FPtr func)
	{
		using std::swap;
		for (_TIt it1 = beg; it1 != end; ++it1) {
			for (_TIt it2 = end - 1; it2 != it1; --it2) {
				if (func(*it2, *(it2 - 1)))
					swap(*it2, *(it2 - 1));
			}
		}
	}

template<typename _TIt> inline
	void bubble_sort(_TIt beg, _TIt end)
	{
		bubble_sort(beg, end, std::less<decltype(*beg)>());
	}

// merge-sort
template<typename _TIt,
	typename _FPtr> inline
	void _Merge(_TIt beg, _TIt mid, _TIt end, _FPtr func)
	{
		auto n1 = mid - beg;
		auto n2 = end - mid;
		decltype(n1) i, j;
		auto *_Lp = new std::remove_reference<decltype(*beg)>::type[n1];
		auto *_Rp = new std::remove_reference<decltype(*beg)>::type[n2];
		for (i = 0; i < n1; ++i)
			_Lp[i] = *(beg + i);
		for (j = 0; j < n2; ++j)
			_Rp[j] = *(mid + j);
		_TIt it = beg;
		for (i = 0, j = 0; i < n1 && j < n2; ++it) {
			if (func(_Lp[i], _Rp[j]))
				*it = _Lp[i++];
			else
				*it = _Rp[j++];
		}
		if (i == n1) {
			for (; j < n2; ++it)
				*it = _Rp[j++];
		} else {
			for (; i < n1; ++it)
				*it = _Lp[i++];
		}
		delete[]_Lp;
		delete[]_Rp;
	}

template<typename _TIt,
	typename _FPtr> inline
	void merge_sort(_TIt beg, _TIt end, _FPtr func)
	{
		auto n = end - beg;
		if (n > 1) {
			_TIt mid = beg + (end - beg) / 2;
			merge_sort(beg, mid, func);
			merge_sort(mid, end, func);
			_Merge(beg, mid, end, func);
		}
	}

template<typename _TIt> inline
	void merge_sort(_TIt beg, _TIt end)
	{
		merge_sort(beg, end, std::less<decltype(*beg)>());
	}

// heap-sort
template<typename _TIt,
	typename _Diff,
	typename _FPtr> inline
	void _Adjust_heap(_TIt beg, _Diff n, _Diff i, _FPtr func)
	{
		auto val = *(beg + i);
		_Diff child = 2 * i + 2;
		for (; child < n; child = 2 * child + 2) {
			if (func(*(beg + child), *(beg + child - 1)))
				--child;
			if (func(val, *(beg + child))) {
				*(beg + i) = *(beg + child);
				i = child;
			} else
				break;
		}
		if (child == n && func(val, *(beg + child - 1))) {
			*(beg + i) = *(beg + child - 1);
			*(beg + child - 1) = val;
		} else
			*(beg + i) = val;
	}

template<typename _TIt,
	typename _Diff,
	typename _FPtr> inline
	void _Build_heap(_TIt beg, _Diff n, _FPtr func)
	{
		for (_Diff i = n / 2 - 1; i >= 0; --i)
			_Adjust_heap(beg, n, i, func);
	}

template<typename _TIt,
	typename _Diff,
	typename _FPtr> inline
	void _Sort_heap(_TIt beg, _Diff n, _FPtr func)
	{
		using std::swap;
		for (_Diff i = n - 1; i > 0; --i) {
			swap(*beg, *(beg + i));
			_Adjust_heap(beg, i, static_cast <_Diff>(0), func);
		}
	}

template<typename _TIt,
	typename _FPtr> inline
	void heap_sort(_TIt beg, _TIt end, _FPtr func)
	{
		_Build_heap(beg, end - beg, func);
		_Sort_heap(beg, end - beg, func);
	}

template<typename _TIt> inline
	void heap_sort(_TIt beg, _TIt end)
	{
		heap_sort(beg, end, std::less<decltype(*beg)>());
	}

template<typename _TIt,
	typename _Diff,
	typename _FPtr> inline
	void _Push_heap(_TIt beg, _Diff n, _FPtr func)
	{
		_Diff i = n - 1, j;
		auto val = *(beg + i);
		for (; i != 0;) {
			j = (i - 1) / 2;
			if (func(*(beg + j), val)) {
				*(beg + i) = *(beg + j);
				i = j;
			} else
				break;
		}
		*(beg + i) = val;
	}

// quick-sort
template<typename _TIt,
	typename _FPtr> inline
	typename _TIt _Partition_0(_TIt beg, _TIt end, _FPtr func)
	{
		using std::swap;
		auto val = *beg;
		_TIt i = beg + 1, j = beg;
		for (; i != end; ++i) {
			if (func(*i, val)) {
				++j;
				swap(*j, *i);
			}
		}
		if (j != beg)
			swap(*beg, *j);
		return j;
	}

template<typename _TIt,
	typename _FPtr> inline
	typename _TIt _Partition_1(_TIt beg, _TIt end, _FPtr func)
	{
		using std::swap;
		auto val = *beg;
		_TIt i = beg, j = end;
		for (;;) {
			do {
				++i;
			} while (i != end && func(*i, val));
			do {
				--j;
			} while (j >= beg && func(val, *j));
			if (i < j)
				swap(*i, *j);
			else
				break;
		}
		swap(*beg, *j);
		return j;
	}

template<typename _TIt,
	typename _FPtr> inline
	typename _TIt _Partition_2(_TIt beg, _TIt end, _FPtr func)
	{
		using std::swap;
		auto len = end - beg;
		if (len > 7) {
			_TIt l = beg;
			_TIt m = beg + len / 2;
			_TIt n = end - 1;
			if (len > 40) {
				auto d = len / 8;
				l = mid3(l, l + d, l + 2 * d, func);
				m = mid3(m - d, m, m + d, func);
				n = mid3(n - 2 * d, n - d, n, func);
			}
			_TIt it = mid3(l, m, n, func);
			swap(*beg, *it);
		}

		auto val = *beg;
		_TIt i = beg, j = end;
		for (;;) {
			do {
				++i;
			} while (i != end && func(*i, val));
			do {
				--j;
			} while (j >= beg && func(val, *j));
			if (i < j)
				swap(*i, *j);
			else
				break;
		}
		swap(*beg, *j);
		return j;
	}

template<typename _TIt,
	typename _FPtr> inline
	typename _TIt mid3(_TIt a1, _TIt a2, _TIt a3, _FPtr func)
	{
		if (func(*a1, *a2)) {
			if (func(*a2, *a3))
				return a2;
			else if (func(*a1, *a3))
				return a3;
			else
				return a1;
		}
		else {
			if (func(*a1, *a3))
				return a1;
			else if (func(*a2, *a3))
				return a3;
			else
				return a2;
		}
	}

template<typename _TIt,
	typename _FPtr> inline
	void _Mid3_m(_TIt _First, _TIt _Mid, _TIt _Last, _FPtr func)
	{
		using std::swap;
		if (func(*_Mid, *_First))
			swap(*_First, *_Mid);
		if (func(*_Last, *_Mid)) {
			swap(*_Mid, *_Last);
			if (func(*_Mid, *_First))
				swap(*_First, *_Mid);
		}			
	}

template<typename _TIt,
	typename _FPtr> inline
	auto _Partition_3(_TIt beg, _TIt end, _FPtr func)
	{
		using std::swap;
		auto len = end - beg;
		_TIt _Mid = beg + len / 2;
		_TIt _End = end - 1;
		if (len > 7) {
			if (len > 40) {
				auto d = len / 8;
				_Mid3_m(beg, beg + d, beg + 2 * d, func);
				_Mid3_m(_Mid - d, _Mid, _Mid + d, func);
				_Mid3_m(_End - 2 * d, _End - d, _End, func);
				_Mid3_m(beg + d, _Mid, _End - d, func);
			} else {
				_Mid3_m(beg, _Mid, _End, func);
			}
		}

		_TIt _Mbeg = _Mid;
		_TIt _Mend = _Mid + 1;
		for (; beg < _Mbeg && !func(*(_Mbeg - 1), *_Mbeg) && !func(*_Mbeg, *(_Mbeg - 1)); --_Mbeg);
		for (; _Mend < end && !func(*_Mbeg, *_Mend) && !func(*_Mend, *_Mbeg); ++_Mend);
		_TIt _Sfront = _Mbeg;
		_TIt _Sback = _Mend;

		for (;;) {
			for (; _Sback < end; ++_Sback) {
				if (func(*_Mbeg, *_Sback))
					;
				else if (func(*_Sback, *_Mbeg))
					break;
				else {
					if (_Sback != _Mend)
						swap(*_Mend, *_Sback);
					++_Mend;
				}
			}
			for (; beg < _Sfront; --_Sfront) {
				if (func(*(_Sfront - 1), *_Mbeg))
					;
				else if (func(*_Mbeg, *(_Sfront - 1)))
					break;
				else {
					if (_Sfront != _Mbeg--)
						swap(*_Mbeg, *(_Sfront - 1));
				}
			}
			if (_Sfront == beg) {
				if (_Sback == end)
					return std::pair<_TIt, _TIt>(_Mbeg, _Mend);
				else {
					if (_Mend != _Sback)
						swap(*_Mend, *_Sback);
					swap(*(_Mbeg++), *(_Mend++));
					++_Sback;						
				}
			}
			else if (_Sback == end) {
				if (_Mbeg != _Sfront)
					swap(*(_Mbeg - 1), *(_Sfront - 1));
				swap(*(--_Mbeg), *(--_Mend));
				--_Sfront;
			}
			else
				swap(*(--_Sfront), *(_Sback++));
		}
	}

#define QUICK_SORT_CHOICE	3
#define TAIL_RECURSIVE_QUICK_SORT
#define QUICK_SORT_TEST
template<typename _TIt,
	typename _FPtr> inline
	void quick_sort(_TIt beg, _TIt end, _FPtr func)
	{
		// test result		|	const array	|	sorted array	|	random array
		// STL sort		|	2  ms		|	12 ms		|	20 ms
		// _Partition_2		|	106 ms		|	115 ms		|	106 ms
		// _Partition_3		|	18 ms		|	202 ms		|	303 ms
#ifdef QUICK_SORT_TEST
#ifndef TAIL_RECURSIVE_QUICK_SORT
		auto s = end - beg;
		if (s > 1) {
#if (QUICK_SORT_CHOICE < 3)
#if (QUICK_SORT_CHOICE == 0)
			_TIt q = _Partition_0(beg, end, func);
#elif (QUICK_SORT_CHOICE == 1)
			_TIt q = _Partition_1(beg, end, func);
#elif (QUICK_SORT_CHOICE == 2)
			_TIt q = _Partition_2(beg, end, func);
#else
#endif
			quick_sort(beg, q, func);
			quick_sort(q + 1, end, func);
#else
//			_TIt q = _Partition_3(beg, end, func);
//			quick_sort(beg, q, func);
//			quick_sort(q, end, func);
#endif
		}
#else
		// Tail recursive quicksort
		while ((end - beg) > 1) {
#if (QUICK_SORT_CHOICE == 2)
			_TIt q = _Partition_2(beg, end, func);
			quick_sort(beg, q, func);
			beg = q+1;
#elif (QUICK_SORT_CHOICE == 3)
			std::pair<_TIt, _TIt> _Mid = _Partition_3(beg, end, func);
			if ((_Mid.first - beg) < (end - _Mid.second)) {
				quick_sort(beg, _Mid.first, func);
				beg = _Mid.second;
			} else {
				quick_sort(_Mid.second, end, func);
				end = _Mid.first;
			}
#endif
		}
#endif
#else
		while ((end - beg) > 7) {
			pair<_TIt, _TIt> _Mid = _Partition_3(beg, end, func);
			if ((_Mid.first - beg) < (end - _Mid.second)) {
				quick_sort(beg, _Mid.first, func);
				beg = _Mid.second;
			} else {
				quick_sort(_Mid.second, end, func);
				end = _Mid.first;
			}
		}
		if ((end - beg) <= 7) {
			insert_sort(beg, end, func);
		}
#endif
	}

template<typename _TIt> inline
	void quick_sort(_TIt beg, _TIt end)
	{
		quick_sort(beg, end, std::less<decltype(*beg)>());
	}

// P38, <<Introduction to Algorithms>>
// T(n) = O(nlgn)
template<typename _TIt>
	auto find_max_subarray(_TIt beg, _TIt end)
		-> typename std::remove_reference<decltype(*beg)>::type
//		-> decltype(*beg + 0)
//		-> typename _TIt::value_type
	{
		auto d = end - beg;
		if (d == 0)
			return 0;
		else if (d == 1)
			return *beg;
		else {
			_TIt mid = beg + d / 2;
			auto left = find_max_subarray(beg, mid);
			auto right = find_max_subarray(mid, end);
			auto cross = find_max_cross_subarray(beg, mid, end);
			auto temp = left > right ? left : right;
			return temp > cross ? temp : cross;
		}
	}

template<typename _TIt>
	auto find_max_cross_subarray(_TIt beg, _TIt mid, _TIt end)
		-> typename std::remove_reference<decltype(*beg)>::type
//		-> decltype(*beg + 0)
//		-> typename _TIt::value_type
	{
		auto left_sum = *(mid - 1);
		auto right_sum = *mid;
		auto sum = left_sum;
		for (_TIt it = mid - 1; it != beg;) {
			--it;
			sum += *it;
			if (sum > left_sum)
				left_sum = sum;
		}
		sum = right_sum;
		for (_TIt it = mid + 1; it != end; ++it) {
			sum += *it;
			if (sum > right_sum)
				right_sum = sum;
		}
		return left_sum + right_sum;
	}

// My solution, T(n) = O(n)
template<typename _TIt>
	auto find_max_subarray_m(_TIt beg, _TIt end)
		-> typename std::remove_reference<decltype(*beg)>::type
//		-> decltype(*beg + 0)
//		-> typename _TIt::value_type
	{
		auto d = end - beg;
		if (d == 0)
			return 0;
		else {
			auto sum = *beg;
			auto max = *beg;
			for (_TIt it = beg + 1; it != end; ++it) {
				if (sum > 0) {
					sum += *it;					
				} else {
					sum = *it;
				}
				if (sum > max)
					max = sum;
			}
			return max;
		}
	}

// select algorithms, P119, <<Introduction to Algorithms>>
template<typename _TIt,
	typename _FPtr> inline
	auto select(_TIt beg, _TIt end, int i, _FPtr func)
		-> typename std::remove_reference<decltype(*beg)>::type
//		->decltype(*beg)
	{
		if ((end - beg) == 1)
			return *beg;
		_TIt q = _Partition_2(beg, end, func);
		decltype(i) k = q - beg + 1;
		if (i == k)
			return *q;
		else if (i < k)
			return select(beg, q, i, func);
		else
			return select(q + 1, end, i - k, func);
	}

template<typename _TIt> inline
	auto select(_TIt beg, _TIt end, int i)
		-> typename std::remove_reference<decltype(*beg)>::type
//		->decltype(*beg)
	{
		return select(beg, end, i, std::less<decltype(*beg)>());
	}

}
#endif // !_ALGORITHM_H_
#pragma once
#ifndef _TREE_H_
#define _TREE_H_

namespace mySTL {
template<typename _T>
	class tree_base
	{
	public:
		typedef typename _T value_type;
		typedef value_type& value_ref;
		typedef tree_base<_T> node_type;
		typedef node_type* node_ptr;
		typedef node_ptr& node_ptref;

		tree_base()
			: _Value(nullptr), _Parent(nullptr), _Left(nullptr), _Right(nullptr)
		{
		}

//		value_ref value(void)
//		{
//			return *(this->value);
//		}

		node_ptref parent(void)
		{
			return this->_Parent;
		}

		node_ptref left(void)
		{
			return this->_Left;
		}
		
		node_ptref right(void)
		{
			return this->_Right;
		}
	private:
		value_type* _Value;
		node_ptr _Parent;
		node_ptr _Left;
		node_ptr _Right;
	};

// binary search tree structure, P161, <<Introduction to Algorithms>>
template<typename _T,
	typename _Tree_base = tree_base<_T>>
	class binary_search_tree
	{
	public:
		typedef typename _Tree_base::value_type value_type;
		typedef typename _Tree_base::node_type node_type;
		typedef typename _Tree_base::node_ptr node_ptr;
		typedef typename _Tree_base::node_ptref node_ptref;

		binary_search_tree()
			: root(nullptr)
		{
		}

		node_ptr search(node_ptr x)
		{
			root = new node_type;
			root->parent() = nullptr;
			return nullptr;
		}
	private:
		node_ptr root;
	};
}
#endif // !_TREE_H_

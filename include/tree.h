#pragma once
#ifndef _TREE_H_
#define _TREE_H_

#include <memory>

namespace mySTL {
template<typename _T>
	class tree_node
	{
	public:
		typedef typename _T value_type;
		typedef tree_node<_T> node_type;
		typedef node_type* node_ptr;
		typedef node_ptr& node_ptref;

		tree_node()
			: _Value()
		{
		}

		tree_node(const value_type& _Val)
			: _Value(_Val)
		{
		}

//		value_ref value(void)
//		{
//			return *(this->value);
//		}

/*		node_ptref parent(void)
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
		}*/
	private:
		std::shared_ptr<node_type> _Left;
		std::shared_ptr<node_type> _Right;
		std::weak_ptr<node_type> _Parent;
		value_type _Value;
	};

// binary search tree structure, P161, <<Introduction to Algorithms>>
template<typename _T>
	class binary_search_tree
	{
	public:
//		typedef typename _Tree_node::value_type value_type;
//		typedef typename _Tree_node::node_type node_type;
//		typedef typename _Tree_node::node_ptr node_ptr;
//		typedef typename _Tree_node::node_ptref node_ptref;

		binary_search_tree(const _T& _Val)
			: root(std::make_shared<tree_node<_T>>(_Val))
		{
//			root = std::make_shared<tree_node<_T>>(5);
		}


	private:
		std::shared_ptr<tree_node<_T>> root;
	};
}
#endif // !_TREE_H_

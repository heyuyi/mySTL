 #pragma once
#ifndef _TREE_H_
#define _TREE_H_

#include <memory>

namespace mySTL {
// binary search tree node
template<typename _T>
	class bs_tree_node
	{
	public:
		typedef typename _T value_type;
		typedef bs_tree_node<_T> node_type;

		bs_tree_node()
			: _Value()
		{
		}

		bs_tree_node(const value_type& _Val)
			: _Value(_Val)
		{
		}

		bs_tree_node(value_type&& _Val)
			: _Value(std::move(_Val))
		{
		}

		bs_tree_node(const value_type& _Val, const std::weak_ptr<node_type> _P)
			: _Value(_Val), _Parent(_P)
		{
		}

		bs_tree_node(value_type&& _Val, const std::weak_ptr<node_type> _P)
			: _Value(std::move(_Val)), _Parent(_P)
		{
		}

		value_type& value(void)
		{
			return this->_Value;
		}

		std::weak_ptr<node_type>& parent(void)
		{
			return this->_Parent;
		}

		std::shared_ptr<node_type>& left(void)
		{
			return this->_Left;
		}
		
		std::shared_ptr<node_type>& right(void)
		{
			return this->_Right;
		}

		static std::shared_ptr<node_type> maximum(std::shared_ptr<node_type> x)
		{
			while (x->right())
				x = x->right();
			return x;
		}

		static std::shared_ptr<node_type> minimum(std::shared_ptr<node_type> x)
		{
			while (x->left())
				x = x->left();
			return x;
		}

	private:
		value_type _Value;
		std::weak_ptr<node_type> _Parent;
		std::shared_ptr<node_type> _Left;
		std::shared_ptr<node_type> _Right;
	};

template<typename _TNode>
	class bs_tree_iterator
	{
	public:
		typedef typename _TNode::value_type value_type;
		typedef typename _TNode::node_type node_type;
		typedef typename bs_tree_iterator<_TNode>  iterator;

		bs_tree_iterator()
		{
		}

		bs_tree_iterator(const std::weak_ptr<node_type>& node)
			: _Node(node)
		{
		}

		bs_tree_iterator(const iterator& it)
			: _Node(it._Node)
		{
		}

		value_type& operator*() const
		{
			return _Node->value();
		}

		value_type* operator->() const
		{
			return &(this->operator*());
		}

		iterator& operator++()
		{
			successor();
			return *this;
		}

		iterator& operator--()
		{
			predecessor();
			return *this;
		}

		iterator operator++(int)
		{
			iterator it = *this;
			successor();
			return it;
		}

		iterator operator--(int)
		{
			iterator it = *this;
			predecessor();
			return it;
		}

		void successor(void)
		{
			std::shared_ptr<node_type> x = _Node.lock();
			if (!x)
				;
			else if (x->right())
				_Node = node_type::minimum(x->right());
			else {
				std::shared_ptr<node_type> y = x->parent().lock();
				while (y && y->right() == x) {
					x = y;
					y = y->parent().lock();
				}
				_Node = y;
			}
		}

		void predecessor(void)
		{
			std::shared_ptr<node_type> x = _Node.lock();
			if (!x)
				;
			else if (x->left())
				_Node = node_type::maximum(x->left());
			else {
				std::shared_ptr<node_type> y = x->parent().lock();
				while (y && y->left() == x) {
					x = y;
					y = y->parent().lock();
				}
				_Node = y;
			}
		}
	private:
		std::weak_ptr<node_type> _Node;
	};

// binary search tree structure, P161, <<Introduction to Algorithms>>
template<typename _T>
	class bs_tree
	{
	public:
		typedef typename bs_tree_node<_T>::value_type value_type;
		typedef typename bs_tree_node<_T>::node_type node_type;
		typedef typename bs_tree_iterator<node_type>  iterator;
		typedef size_t  size_type;

		bs_tree()
			: _Size(0)
		{
		}

		bs_tree(const value_type& _Val)
			: _Root(std::make_shared<node_type>(_Val)), _Size(1)
		{
		}

		bs_tree(value_type&& _Val)
			: _Root(std::make_shared<node_type>(std::move(_Val))), _Size(1)
		{
		}

		typedef void(*walk_func)(const value_type&);

		static void preorder_walk(std::shared_ptr<node_type> x, walk_func f)
		{
			if (x) {
				f(x->value());
				preorder_walk(x->left(), f);
				preorder_walk(x->right(), f);
			}
		}

		static void inorder_walk(std::shared_ptr<node_type> x, walk_func f)
		{
			if (x) {
				inorder_walk(x->left(), f);
				f(x->value());
				inorder_walk(x->right(), f);
			}
		}

		static void postorder_walk(std::shared_ptr<node_type> x, walk_func f)
		{
			if (x) {
				postorder_walk(x->left(), f);
				postorder_walk(x->right(), f);
				f(x->value());
			}
		}

		std::shared_ptr<node_type>& root(void)
		{
			return this->_Root;
		}

		size_type size(void) const
		{
			return _Size;
		}
	private:
		std::shared_ptr<node_type> _Root;
		size_type _Size;
	};
}
#endif // !_TREE_H_

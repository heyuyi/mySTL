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
			: _Value(), _Left(nullptr), _Right(nullptr)
		{
		}

		bs_tree_node(const value_type& _Val)
			: _Value(_Val), _Left(nullptr), _Right(nullptr)
		{
		}

		bs_tree_node(value_type&& _Val)
			: _Value(std::move(_Val)), _Left(nullptr), _Right(nullptr)
		{
		}

		bs_tree_node(const value_type& _Val, const std::shared_ptr<node_type> _P)
			: _Value(_Val), _Parent(_P), _Left(nullptr), _Right(nullptr)
		{
		}

		bs_tree_node(value_type&& _Val, const std::shared_ptr<node_type> _P)
			: _Value(std::move(_Val)), _Parent(_P), _Left(nullptr), _Right(nullptr)
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

// binary search tree iterator
template<typename _Node>
	class bs_tree_iterator
	{
	public:
		typedef typename _Node::value_type value_type;
		typedef typename _Node::node_type node_type;
		typedef typename bs_tree_iterator<_Node>  iterator;

		bs_tree_iterator()
			: _Node(nullptr)
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
			else if (x->right()) {
				if (x->parent().lock())
					_Node = node_type::minimum(x->right());
			}
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
				if(!y)
					_Node = y;
			}
		}

		std::weak_ptr<node_type>& get_ptr(void)
		{
			return this->_Node;
		}

	private:
		std::weak_ptr<node_type> _Node;
	};

template<typename _Node>
	bool operator==(const bs_tree_iterator<_Node>& it1,
		const bs_tree_iterator<_Tree>& it2)
	{
		return it1.get_ptr() == it2.get_ptr();
	}

template<typename _Node>
	bool operator!=(const bs_tree_iterator<_Node>& it1,
		const bs_tree_iterator<_Node>& it2)
	{
		return !(it1 == it2);
	}

// binary search tree structure, P161, <<Introduction to Algorithms>>
template<typename _T>
	class bs_tree
	{
	public:
		typedef typename bs_tree_iterator<bs_tree_node<_T>>::value_type value_type;
		typedef typename bs_tree_iterator<bs_tree_node<_T>>::node_type node_type;
		typedef typename bs_tree_iterator<bs_tree_node<_T>>::iterator  iterator;
		typedef size_t  size_type;

		bs_tree()
			: _Head(std::make_shared<node_type>(0)), _Size(0)
		{
		}

		bs_tree(const value_type& _Val)
			: _Head(std::make_shared<node_type>(0)), _Size(1)
		{
			_Head->left() = std::make_shared<node_type>(_Val, _Head);
			_Head->right() = _Head->left();
		}

		bs_tree(value_type&& _Val)
			: _Head(std::make_shared<node_type>(0)), _Size(1)
		{
			_Head->left() = std::make_shared<node_type>(std::move(_Val), _Head);
			_Head->right() = _Head->left();
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

		void preorder_walk(walk_func f)
		{
			preorder_walk(this->root(), f);
		}

		static void inorder_walk(std::shared_ptr<node_type> x, walk_func f)
		{
			if (x) {
				inorder_walk(x->left(), f);
				f(x->value());
				inorder_walk(x->right(), f);
			}
		}

		void inorder_walk(walk_func f)
		{
			inorder_walk(this->root(), f);
		}

		static void postorder_walk(std::shared_ptr<node_type> x, walk_func f)
		{
			if (x) {
				postorder_walk(x->left(), f);
				postorder_walk(x->right(), f);
				f(x->value());
			}
		}

		void postorder_walk(walk_func f)
		{
			postorder_walk(this->root(), f);
		}

		static std::shared_ptr<node_type> search(std::shared_ptr<node_type> x, const value_type& _Val)
		{
			if (!x || x->value() == _Val)
				return x;
			else if (x->value < _Val)
				return search(x->left(), _Val);
			else
				return search(x->right(), _Val);
		}

		std::shared_ptr<node_type> search(const value_type& _Val)
		{
			return search(this->root(), _Val);
		}

		std::shared_ptr<node_type> search_i(const value_type& _Val)
		{
			std::shared_ptr<node_type> x(this->root());
			while (x && x->value() != _Val) {
				if (x->value() < _Val)
					x = x->left();
				else
					x = x->right();
			}
			return x;
		}

		iterator insert(const value_type& _Val)
		{
			std::shared_ptr<value_type> x(std::make_shared<value_type>(_Val));
			return insert(x);
		}

		iterator insert(value_type&& _Val)
		{
			std::shared_ptr<value_type> x(std::make_shared<value_type>(std::move(_Val)));
			return insert(x);
		}

		iterator insert(std::shared_ptr<value_type>& _New)
		{
			std::shared_ptr<value_type> x(this->root());
			std::shared_ptr<value_type> y(nullptr);
			while (x) {
				y = x;
				if (_New->value() < x->value())
					x = x->left();
				else
					x = x->right();
			}
			if (y) {
				_New->parent() = y;
				if (_New->value() < y->value()) {
					y->left() = _New;
					if (y == this->head()->right())
						this->head()->right() = _New;
				}
				else {
					y->right() = _New;
				}
			}
			else {
				this->head()->left() = _New;
				this->head()->right() = _New;
				_New->parent() = this->head();
			}
			++_Size;
			return iterator(_New);
		}

		iterator erase(iterator _It)
		{

		}

		iterator erase(iterator beg, iterator end)
		{

		}

		void transplant(std::shared_ptr<value_type>& u, std::shared_ptr<value_type>& v)
		{

		}

		void clear(void)
		{
			this->head()->right() = nullptr;
			this->head()->left() = nullptr;
			_Size = 0;
		}

		iterator begin(void)
		{
			return iterator(this->head()->right());
		}

		iterator end(void)
		{
			return iterator(this->head());
		}

		std::shared_ptr<node_type>& root(void)
		{
			return this->head()->left();
		}

		std::shared_ptr<node_type>& head(void)
		{
			return this->_Head;
		}

		size_type size(void) const
		{
			return _Size;
		}
	private:
		std::shared_ptr<node_type> _Head;
		size_type _Size;
	};



}
#endif // !_TREE_H_

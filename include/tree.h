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

		static std::weak_ptr<node_type> successor(std::shared_ptr<node_type> x)
		{
			if (!x)
				return x;
			else if (x->right()) {
				if (x->parent().lock())
					return minimum(x->right());
				else
					return x;
			}
			else {
				std::shared_ptr<node_type> y = x->parent().lock();
				while (y && y->left() != x) {
					x = y;
					y = y->parent().lock();
				}
				return y;
			}
		}

		static std::weak_ptr<node_type> predecessor(std::shared_ptr<node_type> x)
		{
			if (!x)
				return x;
			else if (x->left())
				return maximum(x->left());
			else {
				std::weak_ptr<node_type> tmp = x;
				std::shared_ptr<node_type> y = x->parent().lock();
				while (y && y->left() == x) {
					x = y;
					y = y->parent().lock();
				}
				if (y)
					return y;
				else
					return tmp;
			}
		}
	private:
		value_type _Value;
		std::weak_ptr<node_type> _Parent;
		std::shared_ptr<node_type> _Left;
		std::shared_ptr<node_type> _Right;
	};

// tree iterator
// It can be useful to both binary search tree and red black tree
template<typename _Node>
	class tree_iterator
	{
	public:
		typedef typename _Node::value_type value_type;
		typedef typename _Node::node_type node_type;
		typedef typename tree_iterator<_Node>  iterator;

		tree_iterator()
			: _Node(nullptr)
		{
		}

		tree_iterator(const std::shared_ptr<node_type>& node)
			: _Node(node)
		{
		}

		tree_iterator(const iterator& it)
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
			_Node = node_type::successor(_Node.lock());
			return *this;
		}

		iterator& operator--()
		{
			_Node = node_type::predecessor(_Node.lock());
			return *this;
		}

		iterator operator++(int)
		{
			iterator it = *this;
			++*this;
			return it;
		}

		iterator operator--(int)
		{
			iterator it = *this;
			--*this;
			return it;
		}

		std::weak_ptr<node_type>& get_ptr(void)
		{
			return this->_Node;
		}
	private:
		std::weak_ptr<node_type> _Node;
	};

template<typename _Node>
	bool operator==(tree_iterator<_Node>& it1,
		tree_iterator<_Node>& it2)
	{
		return it1.get_ptr().lock() == it2.get_ptr().lock();
	}

template<typename _Node>
	bool operator!=(tree_iterator<_Node>& it1,
		tree_iterator<_Node>& it2)
	{
		return !(it1 == it2);
	}

// binary search tree structure, P161, <<Introduction to Algorithms>>
template<typename _T>
	class bs_tree
	{
	public:
		typedef typename tree_iterator<bs_tree_node<_T>>::value_type value_type;
		typedef typename tree_iterator<bs_tree_node<_T>>::node_type node_type;
		typedef typename tree_iterator<bs_tree_node<_T>>::iterator  iterator;
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

		template<typename _TIt,
			typename = typename std::enable_if<std::_Is_iterator<_TIt>::value, void>::type>
		bs_tree(_TIt beg, _TIt end)
			: _Head(std::make_shared<node_type>(0)), _Size(0)
		{
			for (; beg != end; ++beg)
				insert(*beg);
		}

		bs_tree(std::initializer_list<value_type> list)
			: _Head(std::make_shared<node_type>(0)), _Size(0)
		{
			for (auto it = list.begin(); it != list.end(); ++it)
				insert(*it);
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

		iterator search(std::shared_ptr<node_type> x, const value_type& _Val)
		{
			if (!x || x->value() == _Val)
				return iterator(x);
			else if (x->value < _Val)
				return search(x->left(), _Val);
			else
				return search(x->right(), _Val);
		}

		iterator search(const value_type& _Val)
		{
			return search(this->root(), _Val);
		}

		iterator search_i(const value_type& _Val)
		{
			std::shared_ptr<node_type> x(this->root());
			while (x && x->value() != _Val) {
				if (x->value() < _Val)
					x = x->left();
				else
					x = x->right();
			}
			return iterator(x);
		}

		iterator insert(const value_type& _Val)
		{
			auto x(std::make_shared<node_type>(_Val));
			return insert(x);
		}

		iterator insert(value_type&& _Val)
		{
			auto x(std::make_shared<node_type>(std::move(_Val)));
			return insert(x);
		}

		iterator insert(std::shared_ptr<node_type>& _New)
		{
			std::shared_ptr<node_type> x(this->root());
			std::shared_ptr<node_type> y(nullptr);
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

		iterator erase(iterator It)
		{
			if (It == this->end())
				return It;
			else {
				std::shared_ptr<node_type> x = It.get_ptr().lock();
				iterator ret(x);
				++ret;
				if (!(x->left())) {
					transplant(x, x->right());
					if (It == this->begin())
						this->head()->right() = ret.get_ptr().lock();
				}
				else if (!(x->right()))
					transplant(x, x->left());
				else {
					std::shared_ptr<node_type> y = ret.get_ptr().lock();
					if (y != x->right()) {
						transplant(y, y->right());
						y->right() = x->right();
						y->right()->parent() = y;
					}
					transplant(x, y);
					y->left() = x->left();
					y->left()->parent() = y;
				}
				--_Size;
				return ret;
			}
		}

		iterator erase(iterator first, iterator last)
		{
			if (first == begin() && last == end())
			{
				clear();
				return iterator(end());
			}
			else {
				iterator it = first;
				while (it != last)
					it = erase(it);
				return iterator(last);
			}
		}

		void transplant(std::shared_ptr<node_type>& u, std::shared_ptr<node_type>& v)
		{
			std::shared_ptr<node_type> p = u->parent().lock();
			if(v)
				v->parent() = p;
			if (u == p->left()) {
				p->left() = v;
			}
			else {
				p->right() = v;
			}
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

// red black tree node
template<typename _T>
	class rb_tree_node
	{
	public:
		typedef typename _T value_type;
		typedef typename rb_tree_node<_T> node_type;

		enum node_color {
			red,
			black
		};

		rb_tree_node()
			: _Value(), _Parent(_Nil), _Left(_Nil), _Right(_Nil), _Color(red)
		{
		}

		rb_tree_node(const value_type& _Val)
			: _Value(_Val), _Parent(_Nil), _Left(_Nil), _Right(_Nil), _Color(red)
		{
		}

		rb_tree_node(value_type&& _Val)
			: _Value(std::move(_Val)), _Parent(_Nil), _Left(_Nil), _Right(_Nil), _Color(red)
		{
		}

		rb_tree_node(const node_color& _C)
			: _Value(), _Parent(_Nil), _Left(_Nil), _Right(_Nil), _Color(_C)
		{
		}

		rb_tree_node(const value_type& _Val, const std::shared_ptr<node_type> _P)
			: _Value(_Val), _Parent(_P), _Left(_Nil), _Right(_Nil), _Color(red)
		{
		}

		rb_tree_node(value_type&& _Val, const std::shared_ptr<node_type> _P)
			: _Value(std::move(_Val)), _Parent(_P), _Left(_Nil), _Right(_Nil), _Color(red)
		{
		}

		static bool Is_nil(const std::shared_ptr<node_type>& p)
		{
			return (p == _Nil);
		}

		static std::shared_ptr<node_type> nil(void)
		{
			return _Nil;
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

		node_color& color()
		{
			return this->_Color;
		}

		static std::shared_ptr<node_type> maximum(std::shared_ptr<node_type> x)
		{
			while (!Is_nil(x->right()))
				x = x->right();
			return x;
		}

		static std::shared_ptr<node_type> minimum(std::shared_ptr<node_type> x)
		{
			while (!Is_nil(x->left()))
				x = x->left();
			return x;
		}

		static std::weak_ptr<node_type> successor(std::shared_ptr<node_type> x)
		{
			
		}

		static std::weak_ptr<node_type> predecessor(std::shared_ptr<node_type> x)
		{
			
		}
	private:
		value_type _Value;
		std::weak_ptr<node_type> _Parent;
		std::shared_ptr<node_type> _Left;
		std::shared_ptr<node_type> _Right;
		node_color _Color;
		static std::shared_ptr<node_type> _Nil;
	};

template<typename _T>
	std::shared_ptr<rb_tree_node<_T>> 
		rb_tree_node<_T>::_Nil(std::make_shared<rb_tree_node<_T>>(black));

// red black tree structure, P174, <<Introduction to Algorithms>>
template<typename _T>
	class rb_tree
	{
	public:
		typedef typename tree_iterator<rb_tree_node<_T>>::value_type value_type;
		typedef typename tree_iterator<rb_tree_node<_T>>::node_type node_type;
		typedef typename tree_iterator<rb_tree_node<_T>>::iterator  iterator;
		typedef size_t  size_type;

		rb_tree()
			: _Root(node_type::nil()), _Size(0)
		{
		}

		rb_tree(const value_type& _Val)
			: _Root(std::make_shared<node_type>(_Val)), _Size(1)
		{
		}

		rb_tree(value_type&& _Val)
			: _Root(std::make_shared<node_type>(std::move(_Val))), _Size(1)
		{
		}

		iterator insert(const value_type& _Val)
		{
			auto x(std::make_shared<node_type>(_Val));
			return insert(x);
		}

		iterator insert(value_type&& _Val)
		{
			auto x(std::make_shared<node_type>(std::move(_Val)));
			return insert(x);
		}

		iterator insert(std::shared_ptr<node_type>& _New)
		{
			std::shared_ptr<node_type> x(this->root());
			std::shared_ptr<node_type> y(node_type::nil());
			while (!node_type::Is_nil(x)) {
				y = x;
				if (_New->value() < x->value())
					x = x->left();
				else
					x = x->right();
			}
			_New->parent() = y;
			if (node_type::Is_nil(y))
				_Root = _New;
			else if (_New->value() < y->value())
				y->left() = _New;
			else
				y->right() = _New;
			insert_fixup(_New);
			++_Size;
			return iterator(_New);
		}

		void insert_fixup(std::shared_ptr<node_type> z)
		{
			for (std::shared_ptr<node_type> p = z->parent().lock();
				p->color() == red; 
				p = z->parent.lock()) {
				std::shared_ptr<node_type> pp = p->parent.lock();
				if (p == pp->left()) {

				}
				else {

				}
			}
		}

		void left_rotate(std::shared_ptr<node_type>& x)
		{
			std::shared_ptr<node_type> y = x->right();
			x->right() = y->left();
			y->parent() = x->parent();
			if (!node_type::Is_nil(y->left()))
				y->left()->parent() = x;
			y->left() = x;
			std::shared_ptr<node_type> p = x->parent().lock();
			if (node_type::Is_nil(p))
				root() = y;
			else if (p->left() == x)
				p->left() = y;
			else
				p->right() = y;
			x->parent() = y;
		}

		void right_rotate(std::shared_ptr<node_type>& x)
		{
			std::shared_ptr<node_type> y = x->left();
			x->left() = y->right();
			y->parent() = x->parent();
			if (!node_type::Is_nil(y->right()))
				y->right()->parent() = x;
			y->right() = x;
			std::shared_ptr<node_type> p = x->parent().lock();
			if (node_type::Is_nil(p))
				root() = y;
			else if (p->left() == x)
				p->left() = y;
			else
				p->right() = y;
			x->parent = y;
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

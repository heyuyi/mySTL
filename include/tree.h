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

		static bool Is_nil(const std::shared_ptr<node_type>& p)
		{
			return (p.get() == nullptr);
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

template<typename _Node,
	typename _Value = _Node::value_type,
	typename _FPtr=void (*)(const _Value&)>
	void preorder_walk(std::shared_ptr<_Node> x, _FPtr f)
	{
		if (!_Node::Is_nil(x)) {
			f(x->value());
			preorder_walk(x->left(), f);
			preorder_walk(x->right(), f);
		}
	}

template<typename _Node,
	typename _Value = _Node::value_type,
	typename _FPtr = void(*)(const _Value&)>
	void inorder_walk(std::shared_ptr<_Node> x, _FPtr f)
	{
		if (!_Node::Is_nil(x)) {
			inorder_walk(x->left(), f);
			f(x->value());
			inorder_walk(x->right(), f);
		}
	}

template<typename _Node,
	typename _Value = _Node::value_type,
	typename _FPtr = void(*)(const _Value&)>
	void postorder_walk(std::shared_ptr<_Node> x, _FPtr f)
	{
		if (!_Node::Is_nil(x)) {
			postorder_walk(x->left(), f);
			postorder_walk(x->right(), f);
			f(x->value());
		}
	}

template<typename _Node,
	typename _Value = _Node::value_type,
	typename _It = tree_iterator<_Node>>
	_It search(std::shared_ptr<_Node> x, const _Value& _Val)
	{
		if (_Node::Is_nil(x) || x->value() == _Val)
			return _It(x);
		else if (_Val < x->value())
			return search(x->left(), _Val);
		else
			return search(x->right(), _Val);
	}

template<typename _Node,
	typename _Value = _Node::value_type,
	typename _It = tree_iterator<_Node >>
	_It search_i(std::shared_ptr<_Node> x, const _Value& _Val)
	{
		while (!_Node::Is_nil(x) && x->value() != _Val) {
			if (_Val < x->value())
				x = x->left();
			else
				x = x->right();
		}
		return _It(x);
	}

	enum node_color
	{
		red,
		black
	};

// red black tree node
template<typename _T>
	class rb_tree_node
	{
	public:
		typedef typename _T value_type;
		typedef typename rb_tree_node<_T> node_type;

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
			if (Is_nil(x))
				return x;
			else if (!Is_nil(x->right()))
				return minimum(x->right());
			else {
				std::shared_ptr<node_type> y = x->parent().lock();
				while (!Is_nil(y) && y->left() != x) {
					x = y;
					y = y->parent().lock();
				}
				return y;
			}
		}

		static std::weak_ptr<node_type> predecessor(std::shared_ptr<node_type> x)
		{
			if (Is_nil(x))
				return x;
			else if (!Is_nil(x->left()))
				return maximum(x->left());
			else {
				std::shared_ptr<node_type> y = x->parent().lock();
				while (!Is_nil(y) && y->left() == x) {
					x = y;
					y = y->parent().lock();
				}
				return y;
			}
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
		typedef typename rb_tree_node<_T>::value_type value_type;
		typedef typename rb_tree_node<_T>::node_type node_type;
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

		template<typename _TIt,
			typename = std::enable_if<std::_Is_iterator<_TIt>::value, void>::type>
		rb_tree(_TIt beg, _TIt end)
			: _Root(node_type::nil()), _Size(0)
		{
			for (; beg != end; ++beg)
				insert(*beg);
		}

		rb_tree(std::initializer_list<value_type> list)
			: _Root(node_type::nil()), _Size(0)
		{
			for (auto it = list.begin(); it != list.end(); ++it)
				insert(*it);
		}

		static int black_height(std::shared_ptr<node_type> x)
		{
			if (node_type::Is_nil(x))
				return 0;
			else {
				int a = black_height(x->left());
				int b = black_height(x->right());
				if (a == -1 || b == -1 || a != b)
					return -1;
				if (x->color() == red) {
					if (x->left()->color() == black&&x->right()->color() == black)
						return a;
					else
						return -1;
				}
				else
					return a + 1;
			}
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
					p = z->parent().lock()) {
				std::shared_ptr<node_type> pp = p->parent().lock();
				if (p == pp->left()) {
					if (pp->right()->color() == red) {
						pp->color() = red;
						p->color() = black;
						pp->right()->color() = black;
						z = pp;
					}
					else {
						if (z == p->right()) {
							left_rotate(p);
							z->color() = black;
							z = p;
						}
						else
							p->color() = black;
						pp->color() = red;
						right_rotate(pp);
					}
				}
				else {
					if (pp->left()->color() == red) {
						pp->color() = red;
						p->color() = black;
						pp->left()->color() = black;
						z = pp;
					}
					else {
						if (z == p->left()) {
							right_rotate(p);
							z->color() = black;
							z = p;
						}
						else
							p->color() = black;
						pp->color() = red;
						left_rotate(pp);
					}
				}
			}
			root()->color() = black;
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
			x->parent() = y;
		}

		iterator erase(iterator it)
		{
			std::shared_ptr<node_type> z = it.get_ptr().lock();
			++it;
			std::shared_ptr<node_type> x;
			node_color _color = z->color();
			if (node_type::Is_nil(z->left())) {
				x = z->right();
				transplant(z, x);
			}
			else if (node_type::Is_nil(z->right())) {
				x = z->left();
				transplant(z, x);
			}
			else {
				std::shared_ptr<node_type> y = it.get_ptr().lock();
				_color = y->color();
				x = y->right();
				if (y != z->right()) {
					transplant(y, x);
					y->right() = z->right();
					y->right()->parent() = y;
				}
				transplant(z, y);
				y->left() = z->left();
				y->left()->parent() = y;
				y->color() = z->color();
			}
			if (_color == black)
				erase_fixup(x);
			--_Size;
			return iterator(it);
		}

		void erase_fixup(std::shared_ptr<node_type> x)
		{
			while (x != root() && x->color() == black) {
				std::shared_ptr<node_type> p = x->parent().lock();
				if (x == p->left()) {
					std::shared_ptr<node_type> w = p->right();
					if (w->color() == red) {
						w->color() = black;
						p->color() = red;
						left_rotate(p);
						w = p->right();
					}
					if (w->left()->color() == black && w->right()->color() == black) {
						w->color() = red;
						x = p;
					}
					else {
						if (w->right()->color() == black) {
							w->left()->color() = black;
							w->color() = red;
							right_rotate(w);
							w = p->right();
						}
						w->color() = red;
						p->color() = black;
						w->right()->color() = black;
						left_rotate(p);
						break;
					}
				}
				else {
					std::shared_ptr<node_type> w = p->left();
					if (w->color() == red) {
						w->color() = black;
						p->color() = red;
						right_rotate(p);
						w = p->left();
					}
					if (w->left()->color() == black && w->right()->color() == black) {
						w->color() = red;
						x = p;
					}
					else {
						if (w->left()->color() == black) {
							w->right()->color() = black;
							w->color() = red;
							left_rotate(w);
							w = p->left();
						}
						w->color() = red;
						p->color() = black;
						w->left()->color() = black;
						right_rotate(p);
						break;
					}
				}
			}
			x->color() = black;
		}

		iterator erase(iterator first, iterator last)
		{
			if (first == begin() && last == end()) {
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
			if (node_type::Is_nil(p))
				this->root() = v;
			else if (u == p->left())
				p->left() = v;
			else
				p->right() = v;
			// Next line my be modify nil's parent node, and it is useful.
			// It can help us find y's parent node after erase(iterator it).
//			if (!node_type::Is_nil(v))
				v->parent() = p;
		}

		void clear(void)
		{
			_Root = node_type::nil();
			_Size = 0;
		}

		iterator begin(void)
		{
			return iterator(node_type::minimum(root()));
		}

		iterator end(void)
		{
			return iterator(node_type::nil());
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

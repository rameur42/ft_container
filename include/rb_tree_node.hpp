/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_node.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 03:29:02 by rameur            #+#    #+#             */
/*   Updated: 2022/04/08 10:12:24 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_NODE_HPP
#define RB_TREE_NODE_HPP

#include <iostream>

namespace ft {
	template < typename T >
	class rb_tree_node
	{
		public:
			typedef	rb_tree_node	node;
			typedef rb_tree_node*	node_pointer;
			typedef T*				data_pointer;

			bool			_isRed;
			node_pointer	_nil_node;
			node_pointer	_parent;
			node_pointer	_left;
			node_pointer	_right;
			data_pointer	_data;

			//??
			node_pointer	_min;
			node_pointer	_max;
		
			//default constructor
			rb_tree_node() : _isRed(false), _nil_node(), _parent(), _left(), _right(), _data(), _min(), _max() {}
			//copy constructor
			rb_tree_node(const rb_tree_node & src) { *this = src; }
			rb_tree_node& operator=(const rb_tree_node & src) 
			{
				_isRed = src._isRed;
				_nil_node = src._nil_node;
				_parent = src._parent;
				_left = src._left;
				_right = src._right;
				_data = src._data;
				_min = src._min;
				_max = src._max;
				return *this;
			}
	};

	template<typename T>
	std::ostream	&operator<<(std::ostream &stream, const rb_tree_node<T> & n)
	{
		if (n._data == NULL)
		{
			stream << "Nil node" << std::endl;
			return stream;
		}
		if (n.data != NULL)
			stream << "isRed " <<  n._isRed << " " << *n._data;
		return stream;
	}
}

#endif
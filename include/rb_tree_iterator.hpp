/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 06:17:50 by rameur            #+#    #+#             */
/*   Updated: 2022/04/09 03:30:54 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_ITERATOR_HPP
#define RB_TREE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template< typename T, typename node_type >
	class rb_tree_iterator {
		public:
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef const T&						const_reference;
			typedef const T*						const_pointer;
			typedef	ft::bidirectional_iterator_tag	iterator_categorie;
			typedef ptrdiff_t						difference_type;
			typedef node_type*						node_pointer;

			node_pointer	_node;
			
			//Default constructor 
			rb_tree_iterator() : _node() {}
			//Init constructor
			rb_tree_iterator(node_pointer src) : _node(src) {}
			//Copy constructor
			rb_tree_iterator(rb_tree_iterator const & src) : _node(src._node) {}
			//Assignement
			rb_tree_iterator&	operator=(rb_tree_iterator const & src)
			{
				if (this != &src)
					this->_node = src._node;
				return *this;
			}

			//to const
			operator	rb_tree_iterator<value_type const, node_type const>() const
			{
				return rb_tree_iterator<value_type const, node_type const>(_node);
			}

			reference operator*()
			{
				return *_node->_data;
			}

			pointer	operator->()
			{
				return _node->_data;
			}

			//pre
			rb_tree_iterator&	operator++()
			{
				increment();
				return *this;
			}
			
			//post
			rb_tree_iterator operator++(int)
			{
				rb_tree_iterator tmp(*this);
				increment();
				return tmp;
			}
			
			//pre
			rb_tree_iterator& operator--()
			{
				decrement();
				return *this;
			}
			
			//post
			rb_tree_iterator operator--(int)
			{
				rb_tree_iterator tmp(*this);
				decrement();
				return tmp;
			}
			
			bool	operator==(rb_tree_iterator const & val) const
			{
				return _node == val._node;
			}
			
			bool	operator!=(rb_tree_iterator const & val) const
			{
				return _node != val._node;
			}
		protected:
			void	increment()
			{
				if (_node == _node->_nil_node)
					return ;
				if (_node->_right != _node->_nil_node)
				{
					_node = _node->_right;
					while (_node->_left != _node->_nil_node)
						_node = _node->_left;
				}
				else
				{
					node_pointer tmp = _node->_parent;
					while (tmp != _node->_nil_node && _node == tmp->_right)
					{
						_node = tmp;
						tmp = tmp->_parent;
					}
					_node = tmp;
				}
			}
			void	decrement()
			{
				if (_node == _node->_nil_node)
				{
					//_node = _node->_nil_node->_max;
					return ;
				}
				if (_node->_left != _node->_nil_node)
				{
					_node = _node->_left;
					while (_node->right != _node->_nile_node)
						_node = _node->_right;
				}
				else
				{
					node_pointer tmp = _node->_parent;
					while(tmp != _node->_nile_node && _node == tmp->_left)
					{
						_node = tmp;
						tmp = tmp->parent;
					}
					_node = tmp;
				}
			}
	};
}
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 05:48:01 by rameur            #+#    #+#             */
/*   Updated: 2022/04/08 10:31:21 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <cstddef>
#include <iostream>
#include <sstream>
#include <functional>
#include "rb_tree_node.hpp"
#include "pair.hpp"
#include "rb_tree_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template < typename T, typename Comp, typename Alloc>
		class rb_tree {
			private:
				typedef rb_tree<T, Comp, Alloc>													self;//??
				typedef	size_t																	size_type;
				typedef ptrdiff_t																difference_type;
				typedef T																		value_type;
				typedef ft::rb_tree_node<T>														node_type;
				typedef ft::rb_tree_node<T>*													node_pointer;
				typedef typename Alloc::template rebind<value_type>::other						data_allocator;
				typedef typename Alloc::template rebind<ft::rb_tree_node<value_type> >::other	node_allocator;

				//Allocators
				data_allocator	_data_alloc;
				node_allocator	_node_alloc;
				//Compare function
				Comp			_key_compare;
				//nodes
				node_type		*_root;
				node_type		*_nil;//node NULL
				size_type		_size;

				bool	_is_equal(value_type const & x, value_type const & y) const;
				
				node_pointer	_create_node(const value_type & val)
				{
					node_pointer new_node;
					new_node = _node_alloc.allocate(1);
					new_node->_parent = _nil;
					new_node->_nil_node = _nil;
					new_node->_left = _nil;
					new_node->_right = _nil;
					new_node->_isRed = false;
					new_node->_data = _data_alloc.allocate(1);
					_data_alloc.construct(new_node->_data, val);
					return new_node;
				}
				
				void	_print(node_pointer node, std::stringstream &buffer, bool is_tail, std::string prefix);
			public:
				typedef ft::rb_tree_iterator<value_type, node_type>					iterator;
				typedef	ft::rb_tree_iterator<value_type const, node_type const>		const_iterator;
				typedef ft::reverse_iterator<iterator>								reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
				
				typedef ft::pair<iterator, bool>									pair_type;
				typedef ft::pair<iterator, iterator>								pair_range;
				typedef ft::pair<const_iterator, const_iterator>					const_pair_range;
				
				//Default constructor
				rb_tree();
				//Init constructor
				explicit rb_tree(const Comp compare, const Alloc allocator);

				pair_type	insert_node(const value_type & val, node_pointer start_pos)
				{
					node_pointer y = _nil;
					node_pointer x;
					if (start_pos != _nil)
						x = start_pos;
					else
						x = _root;
					while (x != _nil)
					{
						y = x;
						if (_is_equal(val, *x->_data))
							return (pair_type(iterator(x), false));
						else if (_key_compare(val, *x->_data))
							x = x->_left;
						else
							x = x->_right;
					}
					node_pointer new_node = _create_node(val);
					new_node->_parent = y;
					if (y == _nil)
						_root = new_node;
					else if (_key_compare(val, *y->_data))
						y->_left = new_node;
					else
						y->_right = new_node;
					new_node->_isRed = true;
					//insert_node_fixe(new_node);
					_size++;
					return pair_type(iterator(new_node), true);
				}
				
				pair_type	insert(const value_type & val)
				{
					return insert_node(val, _root);
				}

				size_type	get_size() const { return _size; }
				
				void	print()
				{
					if (get_size() < 1)
						return ;
					std::stringstream buffer;
					this->_print(this->_root, buffer, true, "");
					std::cout << buffer.str();
				}
		};

		template<typename T, typename Comp, typename Alloc>
			bool	rb_tree<T, Comp, Alloc>::_is_equal(const value_type & x, const value_type & y) const
			{
				return !_key_compare(x, y) && !_key_compare(y, x);
			}
		
		template< typename T, typename Comp, typename Alloc > 
			rb_tree<T, Comp, Alloc>::rb_tree(const Comp compare, const Alloc allocator)
			: _data_alloc(allocator), _key_compare(compare)
			{
				_size = 0;
				_nil = _node_alloc.allocate(1);
				_nil->_isRed = false;
				_nil->_data = NULL;
				_nil->_nil_node = _nil;
				_nil->_parent = _nil;
				_nil->_left = _nil;
				_nil->_right = _nil;
				_nil->_min = _nil;
				_nil->_max = _nil;
				_root = _nil;
			}

			template< typename T, typename Comp, typename Alloc>
				void	rb_tree<T, Comp, Alloc>::_print(node_pointer node, std::stringstream &buffer, bool is_tail, std::string prefix)
				{
					if (node->_right != _nil)
						this->_print(node->_right, buffer, false, std::string(prefix).append(is_tail != 0 ? "|	" : " 	"));
					buffer << prefix <<  (is_tail != 0 ? "└── " : "┌── ");
					if (node->_isRed == true)
						    buffer << "\033[31m";
					if (node != _nil)
						buffer << node->_data->second << "\033[0m" << std::endl;
					if (node->_left != _nil)
						this->_print(node->_left, buffer, true, std::string(prefix).append(is_tail != 0 ? "    " : "│   "));
				}
} // namespace ft

#endif
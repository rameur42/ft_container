/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 05:48:01 by rameur            #+#    #+#             */
/*   Updated: 2022/04/09 06:04:02 by rameur           ###   ########.fr       */
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
				node_pointer	_rb_tree_min_node(node_pointer node) const
				{
					if (node == _nil)
						return _nil;
					node_pointer	res = node;
					while (res->_left != _nil)
						res = res->_left;
					return res;
				}
				node_pointer	_rb_tree_max_node(node_pointer node) const
				{
					if (node == _nil)
						return _nil;
					node_pointer res = node;
					while (res->_right != _nil)
						res = res->_right;
					return res;
				}
				void	_clean_node(node_pointer node)
				{
					if (node != _nil)
					{
						_data_alloc.destroy(node->_data);
						_data_alloc.deallocate(node->_data, 1);
						_node_alloc.deallocate(node, 1);
						node = _nil;
					}
				}
				void	_clean_tree(node_pointer node)
				{
					if (node != _nil)
					{
						_clean_tree(node->_left);
						_clean_tree(node->_right);
						_clean_node(node);
					}
					_size = 0;
				}
				void	_clean()
				{
					_clean_tree(_root);
					_root = _nil;
					_root->_left = _nil;
					_root->_right = _nil;
				}
				
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
				
				void	_rb_transplant(node_pointer node_a, node_pointer node_b)
				{
					if (node_a->_parent == _nil)
						_root = node_b;
					else if (node_a->_parent->_left == node_a)
						node_a->_parent->_left = node_b;
					else
						node_a->_parent->_right = node_b;
					node_b->_parent = node_a->_parent;
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
				//Destructor
				rb_tree(const rb_tree & src);
				~rb_tree()
				{
					if (this->_root != _nil)
						_clean();
					_node_alloc.deallocate(_nil, 1);
				}
				//assignement
				rb_tree&	operator=(const rb_tree & src)
				{
					if (this != &src)
					{
						_clean();
						for (const_iterator i = src.rb_begin(); i != src.rb_end(); i++)
							insert(*i);
					}
					return *this;
				}
			
				node_pointer	search_node(const value_type & val) const
				{
					node_pointer res = _root;
					while (res != _nil && !_is_equal(val, *res->_data))
					{
						if (_key_compare(val, *res->_data))
							res = res->_left;
						else
							res = res->_right;
					}
					return res;
				}
				
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

				void		delete_node(node_pointer node)
				{
					node_pointer x;
					node_pointer y;
					y = node;
					//bool node_isRed = node->_isRed;
					if (node->_left == _nil)
					{
						x = node->_right;
						_rb_transplant(node, node->_right);
					}
					else if (node->_right == _nil)
					{
						x = node->_left;
						_rb_transplant(node, node->_left);
					}
					else
					{
						y = _rb_tree_min_node(node->_right);
						//node_isRed = y->_isRed;
						x = y->_right;
						if (y->_parent == node)
							x->_parent = y;
						else
						{
							_rb_transplant(y, y->_right);
							y->_right = node->_right;
							y->_right->_parent = y;
						}
						_rb_transplant(node, y);
						y->_left = node->_left;
						y->_left->_parent = y;
						//y->_isRed = node->_isRed;
					}
					_clean_node(node);
					_nil->_max = _rb_tree_max_node(_root);
					_nil->_min = _rb_tree_min_node(_root);
					_nil->_parent = _nil;
					_size--;
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
				//Iterators
				iterator				rb_begin() { return iterator(_rb_tree_min_node(_root)); }
				const_iterator			rb_begin() const { return const_iterator(_rb_tree_min_node(_root)); }
				iterator				rb_end() { return iterator(_rb_tree_max_node(_root)); }
				const_iterator			rb_end() const { return const_iterator(_rb_tree_min_node(_root)); }
				reverse_iterator		rb_rbegin() { return reverse_iterator(rb_end()); }
				const_reverse_iterator	rb_rbegin() const { return const_reverse_iterator(rb_end()); }
				reverse_iterator		rb_end() { return reverse_iterator(rb_begin()); }
				const_reverse_iterator	rb_end() const { return const_reverse_iterator(rb_begin()); }
				
				data_allocator	get_data_allocator() const { return _data_alloc; }
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
						buffer << node->_data->first << "\033[0m" << std::endl;
					if (node->_left != _nil)
						this->_print(node->_left, buffer, true, std::string(prefix).append(is_tail != 0 ? "    " : "│   "));
				}
} // namespace ft

#endif
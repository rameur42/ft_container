/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 01:20:44 by rameur            #+#    #+#             */
/*   Updated: 2022/04/09 09:06:20 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>
#include "pair.hpp"
#include "rb_tree.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
		class map {
			public:
				typedef	Key													key_type;
				typedef T													mapped_type;
				typedef typename ft::pair<key_type, mapped_type>			value_type;
				typedef	Compare												key_compare;
				typedef Alloc												allocator_type;

				class value_compare : public std::binary_function<value_type, value_type, bool>
				{
					friend class map<Key, T, Compare, Alloc>;
					protected:
						Compare comp;
						value_compare(Compare val) : comp(val) {}
					public:
						bool	operator()(const value_type & x, const value_type & y) const
						{
							return comp(x.first, y.first);
						}
				};

			private:
				typedef typename Alloc::value_type							alloc_value_type;
				typedef rb_tree<value_type, value_compare, allocator_type>	tree_type;
				typedef typename tree_type::pair_type						pair_type;
				typedef typename tree_type::pair_range						pair_range;
				typedef typename tree_type::const_pair_range				const_pair_range;
				
				tree_type	_tree;
				key_compare _key_comp;
			
			public:
				typedef typename allocator_type::reference					reference;
				typedef typename allocator_type::const_reference			const_reference;
				typedef typename allocator_type::pointer					pointer;
				typedef typename allocator_type::const_pointer				const_pointer;
				typedef typename tree_type::iterator 						iterator;
				typedef typename tree_type::const_iterator					const_iterator;
				typedef typename tree_type::reverse_iterator				reverse_iterator;
				typedef typename tree_type::const_reverse_iterator			const_reverse_iterator;
				typedef typename iterator_traits<iterator>::difference_type	difference_type;
				typedef	size_t												size_type;

			//Default constructor
			explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()) : _tree(comp , alloc) {} 
			//Range constructor
			template <class InputIterator>
				map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type()) : _tree(comp, alloc)
						{
							while (first != last)
								_tree.insert(*first++);
						}
			//Copy constructor
			map(const map & src) : _tree(src.key_comp(), src.get_allocator())
			{
				for (const_iterator pos = src.begin(); pos != src.end(); pos++)
					_tree.insert(*pos);
			}
			~map() {}

			map&	operator=(const map & src)
			{
				_tree = src._tree;
				return *this;
			}
			//Iterators
			iterator				begin() { return _tree.rb_begin(); }
			const_iterator			begin() const { return _tree.rb_begin(); }
			iterator				end() { return _tree.rb_end(); }
			const_iterator			end() const {return _tree.rb_end(); }
			reverse_iterator		rbegin() { return _tree.rb_rbegin(); }
			const_reverse_iterator	rbegin() const { return _tree.rb_rbegin(); }
			reverse_iterator		rend() { return _tree.rb_rend(); }
			const_reverse_iterator	rend() const { return _tree.rb_rend(); }
			//Capacity
			bool					empty() const { return _tree.empty(); }
			size_type				size() const { return _tree.get_size(); }
			size_type				max_size() const { return _tree.get_max_size(); }
			//Element access
			mapped_type&			operator[](const key_type& k)
			{
				value_type val = ft::make_pair(k, mapped_type());
				return (((insert(val)).first)->second);
			}
			//Modifiers
			//Single element
			ft::pair<iterator, bool>	insert(const value_type & val) { return _tree.insert(val); }
			//With hint
			iterator					insert(iterator position, const value_type & val) { return _tree.insert_pose(position, val); }
			//Range
			template <class InputIterator>
				void					insert(InputIterator first, InputIterator last)
				{
					while (first != last)
						_tree.insert(*first++);	
				}
			void			erase(iterator position)
			{
				if (position == end())
					return;
				key_type key = position->first;
				value_type val = ft::make_pair(key, mapped_type());
				_tree.delete_node(_tree.search_node(val));
			}
			size_type		erase(const key_type & k)
			{
				value_type val = ft::make_pair(k, mapped_type());
				iterator pos(_tree.search_node(val));
				if (pos != end())
				{
					_tree.delete_node(_tree.search_node(val));
					return 1;
				}
				return 0;
			}
			void			erase(iterator first, iterator last)
			{
				if (first != end())
					while(first != last)
						_tree.delete_node(_tree.search_node(*first++));
			}
			void			swap(map& x) { _tree.rb_swap(x._tree); }
			void			clear() { _tree._clean(); }
			//Observers
			key_compare		key_comp() const { return _key_comp; }
			value_compare	value_comp() const { return _tree.get_key_compare(); }
			//Operations
			iterator		find(const key_type & k)
			{ 
				value_type val = ft::make_pair(k, mapped_type());
				return iterator(_tree.search_node(val));
			}
			const_iterator	find(const key_type & k) const
			{
				value_type val = ft::make_pair(k, mapped_type());
				return const_iterator(_tree.search_node(val));
			}
			size_type		count(const key_type & k) const
			{
				value_type val = ft::make_pair(k, mapped_type());
				const_iterator res = _tree.search_node(val);
				if (res == end())
					return 0;
				else
					return 1;
			}
			//Allocator
			allocator_type	get_allocator() const { return _tree.get_data_allocator(); }
			void			print() { _tree.print(); }
		};
}

#endif
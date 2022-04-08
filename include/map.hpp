/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 01:20:44 by rameur            #+#    #+#             */
/*   Updated: 2022/04/08 10:21:52 by rameur           ###   ########.fr       */
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
				tree_type _tree;
			
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

			explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()) : _tree(comp , alloc) {} 

			ft::pair<iterator, bool>	insert(const value_type & val)
			{
				return _tree.insert(val);
			}

			void	print() { _tree.print(); }
		};
}

#endif
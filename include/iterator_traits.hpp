/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:34:46 by rameur            #+#    #+#             */
/*   Updated: 2022/03/29 20:14:35 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAIT_HPP
#define ITERATOR_TRAIT_HPP

#include "iterator.hpp"

namespace ft{
	
	template <class Category, class T, class Distance = ptrdiff_t,
	          class Pointer = T*, class Reference = T&>
	struct iterator {
	    typedef T         value_type;
	    typedef Distance  difference_type;
	    typedef Pointer   pointer;
	    typedef Reference reference;
	    typedef Category  iterator_category;
	};
	
	template <typename Iterator>
		class iterator_traits {
			public: 
				typedef typename Iterator::difference_type		difference_type;
				typedef typename Iterator::value_type			value_type;
				typedef typename Iterator::pointer				pointer;
				typedef typename Iterator::reference			reference;
				typedef typename Iterator::iterator_category	iterator_category;
		};
}

#endif
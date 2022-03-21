/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:12:25 by rameur            #+#    #+#             */
/*   Updated: 2022/03/21 22:02:02 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

namespace ft {
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};


	template <class Category, class T, class Distance = ptrdiff_t,
	          class Pointer = T*, class Reference = T&>
	struct iterator {
	    typedef T         value_type;
	    typedef Distance  difference_type;
	    typedef Pointer   pointer;
	    typedef Reference reference;
	    typedef Category  iterator_category;
	};
	
	
	template< class T >
	class vecIterator : public ft::iterator<random_access_iterator_tag, T>{
		public:
			typedef typename ft::iterator<random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<random_access_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<random_access_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;
		
			vecIterator() : _p(NULL) {};
			vecIterator(pointer p) : _p(p) {};
			~vecIterator() {};
			vecIterator(vecIterator const & src) {
				this->_p = src->_p;
			}
			
		private:
			pointer	_p;
	};
	
}
#endif
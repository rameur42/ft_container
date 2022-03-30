/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:29:24 by rameur            #+#    #+#             */
/*   Updated: 2022/03/29 23:03:47 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
	
	template <typename Iterator>
	class reverse_iterator/* : public iterator<typename iterator_traits<Iterator>::value_type,
											typename iterator_traits<Iterator>::difference_type,
											typename iterator_traits<Iterator>::pointer,
											typename iterator_traits<Iterator>::reference > */{
		public:
			typedef Iterator												iterator_type;
			typedef	typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
			
			reverse_iterator() : _revP(), _base() {};
			explicit reverse_iterator(iterator_type it) : _revP(it), _base(it - 1) {};

			iterator_type base() const { return this->_base; }
			
			reference	operator*() const { return (*(this->_revP)); }

			reverse_iterator	operator+(difference_type n) const
			{
				return (reverse_iterator(this->_revP - n));
			}

			reverse_iterator	operator-(difference_type n) const
			{
				//this->_base -= n;
				return (reverse_iterator(this->_revP + n));
			}
		private:
			Iterator	_revP;
			Iterator	_base;
	};
}

#endif
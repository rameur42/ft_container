/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:29:24 by rameur            #+#    #+#             */
/*   Updated: 2022/03/30 20:28:18 by rameur           ###   ########.fr       */
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
			
			reverse_iterator() : _revP() {};
			explicit reverse_iterator(iterator_type it) : _revP(it) {};

			iterator_type base() const { return this->_revP; }
			
			reference	operator*() const { return (*(this->_revP)); }

			reverse_iterator	operator+(difference_type n) const
			{
				return (reverse_iterator(this->_revP - n));
			}

			reverse_iterator&	operator++()
			{
				this->_revP--;
				return *this;
			}

			reverse_iterator	operator++(int)
			{
				reverse_iterator tmp = *this;
				this->_revP--;
				return tmp;
			}
			
			reverse_iterator&	operator+=(difference_type n)
			{
				this->_revP -= n;
				return (*this);
			}
			
			reverse_iterator	operator-(difference_type n) const
			{
				return (reverse_iterator(this->_revP + n));
			}

			reverse_iterator&	operator--()
			{
				this->_revP++;
				return *this;
			}

			reverse_iterator	operator--(int)
			{
				reverse_iterator tmp = *this;
				this->_revP++;
				return tmp;
			}

			reverse_iterator&	operator-=(difference_type n)
			{
				this->_revp += n;
				return (*this);
			}

			pointer	operator->() const
			{
				return &(operator*());
			}
			
			reference	operator[] ( difference_type n) const
			{
				return (*(this - n));
			}
			
			Iterator	getRevP() const
			{
				return this->_revP;
			}
		private:
			Iterator	_revP;
	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator> & lhs,
					const reverse_iterator<Iterator> & rhs)
	{
		if (lhs.getRevP() == rhs.getRevP())
			return true;
		return false;
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator> & lhs,
					const reverse_iterator<Iterator> & rhs)
	{
		if (lhs.getRevP() != rhs.getRevP())
			return true;
		return false;
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> & lhs,
					const reverse_iterator<Iterator> & rhs)
	{
		if (lhs.getRevP() < rhs.getRevP())
			return true;
		return false;
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> & lhs,
					const reverse_iterator<Iterator> & rhs)
	{
		if (lhs.getRevP() == rhs.getRevP())
			return true;
		else if (lhs.getRevP() < rhs.getRevP())
			return true;
		return false;
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> & lhs,
					const reverse_iterator<Iterator> & rhs)
	{
		if (lhs.getRevP() > rhs.getRevP())
			return true;
		return false;
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> & lhs,
					const reverse_iterator<Iterator> & rhs)
	{
		if (lhs.getRevP() == rhs.getRevP())
			return true;
		else if (lhs.getRevP() > rhs.getRevP())
			return true;
		return false;
	}
}

#endif
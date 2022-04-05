/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:29:24 by rameur            #+#    #+#             */
/*   Updated: 2022/04/01 18:22:06 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
	
	template <typename Iterator>
	class reverse_iterator : public iterator<typename iterator_traits<Iterator>::value_type,
											typename iterator_traits<Iterator>::difference_type,
											typename iterator_traits<Iterator>::pointer,
											typename iterator_traits<Iterator>::reference > {
		public:
			typedef Iterator												iterator_type;
			//typedef	typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
			
			reverse_iterator() : _revP() {};
			explicit reverse_iterator(iterator_type it) : _revP(it) {};
			reverse_iterator(reverse_iterator const & src) : _revP(src._revP) {};
			reverse_iterator&	operator=(reverse_iterator const & src)
			{
				if (this != &src)
					_revP = src._revP;
				return (*this);
			}
			
			//const reverse_iterator
			template<typename _Iterator>
			reverse_iterator(reverse_iterator<_Iterator> const & x) : _revP(x.base()) {};
			
			friend bool	operator!=(reverse_iterator const & lhs, reverse_iterator const & rhs)
			{
				if (lhs.base() != rhs.base())
					return true;
				return false;
			}
			
			iterator_type base() const { return this->_revP; }
			
			reference	operator*() const { return *(this->_revP - 1); }

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

		private:
			Iterator	_revP;
	};

	template <typename Iterator>
	bool operator==(const reverse_iterator<Iterator> & lhs,
					const reverse_iterator<Iterator> & rhs)
	{
		if (lhs.getRevP() == rhs.getRevP())
			return true;
		return false;
	}

	template <typename Iterator>
	bool operator!=(const reverse_iterator<Iterator> & lhs,
					const reverse_iterator<Iterator> & rhs)
	{
		if (lhs.base() != rhs.base())
			return true;
		return false;
	}


	template <typename Iterator>
	bool operator<(const reverse_iterator<Iterator> & lhs,
					const reverse_iterator<Iterator> & rhs)
	{
		if (lhs.base() < rhs.base())
			return true;
		return false;
	}

	template <typename Iterator>
	bool operator<=(const reverse_iterator<Iterator> & lhs,
					const reverse_iterator<Iterator> & rhs)
	{
		if (lhs.base() == rhs.base())
			return true;
		else if (lhs.base() < rhs.base())
			return true;
		return false;
	}

	template <typename Iterator>
	bool operator>(const reverse_iterator<Iterator> & lhs,
					const reverse_iterator<Iterator> & rhs)
	{
		if (lhs.base() > rhs.base())
			return true;
		return false;
	}

	template <typename Iterator>
	bool operator>=(const reverse_iterator<Iterator> & lhs,
					const reverse_iterator<Iterator> & rhs)
	{
		if (lhs.base() == rhs.base())
			return true;
		else if (lhs.base() > rhs.base())
			return true;
		return false;
	}

	template <typename IteratorL, typename IteratorR>
	bool operator==(const reverse_iterator<IteratorL> & lhs,
					const reverse_iterator<IteratorR> & rhs)
	{
		if (lhs.getRevP() == rhs.getRevP())
			return true;
		return false;
	}

	template <typename IteratorL, typename IteratorR>
	bool operator!=(const reverse_iterator<IteratorL> & lhs,
					const reverse_iterator<IteratorR> & rhs)
	{
		if (lhs.base() != rhs.base())
			return true;
		return false;
	}

template <typename IteratorR, typename IteratorL>
	bool operator<(const reverse_iterator<IteratorR> & lhs,
					const reverse_iterator<IteratorL> & rhs)
	{
		if (lhs.base() < rhs.base())
			return true;
		return false;
	}

	template <typename IteratorR, typename IteratorL>
	bool operator<=(const reverse_iterator<IteratorR> & lhs,
					const reverse_iterator<IteratorL> & rhs)
	{
		if (lhs.base() == rhs.base())
			return true;
		else if (lhs.base() < rhs.base())
			return true;
		return false;
	}

	template <typename IteratorR, typename IteratorL>
	bool operator>(const reverse_iterator<IteratorR> & lhs,
					const reverse_iterator<IteratorL> & rhs)
	{
		if (lhs.base() > rhs.base())
			return true;
		return false;
	}

	template <typename IteratorR, typename IteratorL>
	bool operator>=(const reverse_iterator<IteratorR> & lhs,
					const reverse_iterator<IteratorL> & rhs)
	{
		if (lhs.base() == rhs.base())
			return true;
		else if (lhs.base() > rhs.base())
			return true;
		return false;
	}
}

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:29:24 by rameur            #+#    #+#             */
/*   Updated: 2022/04/11 04:49:21 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
	
	template <typename Iterator>
	class reverse_iterator {
		public:
			typedef	ft::iterator_traits<Iterator>								it_traits;
			typedef Iterator												iterator_type;
			typedef typename it_traits::value_type			value_type;
			typedef typename it_traits::difference_type		difference_type;
			typedef typename it_traits::pointer				pointer;
			typedef typename it_traits::reference			reference;
			
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
			reference	operator*() const;
			reverse_iterator	operator+(difference_type n) const
			{
				return reverse_iterator(this->_revP - n);
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
				this->_revP += n;
				return (*this);
			}

			pointer	operator->() const
			{
				return &(operator*());
			}
			
			reference	operator[] ( difference_type n) const
			{
				return (*(*this + n));
			}

		private:
			Iterator	_revP;
	};

	template <typename Iterator>
	typename reverse_iterator<Iterator>::reference	reverse_iterator<Iterator>::operator*() const
	{
		Iterator tmp = _revP;
		return *--tmp;
	}

	template<typename Iterator>
	reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> & rhs)
	{
		return (reverse_iterator<Iterator>(rhs.base() - n));
	}
	
	template <typename IteratorL, typename IteratorR>
	typename reverse_iterator<IteratorL>::difference_type operator-(const reverse_iterator<IteratorL> & lhs,
					const reverse_iterator<IteratorR> & rhs)
	{
		return rhs.base() - lhs.base();
	}
	
	template <typename Iterator>
	bool operator==(const reverse_iterator<Iterator> & lhs,
					const reverse_iterator<Iterator> & rhs)
	{
		if (lhs.base() == rhs.base())
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
		return rhs.base() < lhs.base();
	}

	template <typename Iterator>
	bool operator<=(const reverse_iterator<Iterator> & lhs,
					const reverse_iterator<Iterator> & rhs)
	{
		if (lhs.base() == rhs.base())
			return true;
		else if (lhs.base() < rhs.base())
			return false;
		return true;
	}

	template <typename Iterator>
	bool operator>(const reverse_iterator<Iterator> & lhs,
					const reverse_iterator<Iterator> & rhs)
	{
		return rhs < lhs;
	}

	template <typename Iterator>
	bool operator>=(const reverse_iterator<Iterator> & lhs,
					const reverse_iterator<Iterator> & rhs)
	{
		if (lhs.base() == rhs.base())
			return true;
		else if (lhs.base() > rhs.base())
			return false;
		return true;
	}

	template <typename IteratorL, typename IteratorR>
	bool operator==(const reverse_iterator<IteratorL> & lhs,
					const reverse_iterator<IteratorR> & rhs)
	{
		if (lhs.base() == rhs.base())
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
		return rhs.base() < lhs.base();
	}

	template <typename IteratorR, typename IteratorL>
	bool operator<=(const reverse_iterator<IteratorR> & lhs,
					const reverse_iterator<IteratorL> & rhs)
	{
		if (lhs.base() == rhs.base())
			return true;
		else if (lhs.base() < rhs.base())
			return false;
		return true;
	}

	template <typename IteratorR, typename IteratorL>
	bool operator>(const reverse_iterator<IteratorR> & lhs,
					const reverse_iterator<IteratorL> & rhs)
	{
		return rhs < lhs;
	}

	template <typename IteratorR, typename IteratorL>
	bool operator>=(const reverse_iterator<IteratorR> & lhs,
					const reverse_iterator<IteratorL> & rhs)
	{
		if (lhs.base() == rhs.base())
			return true;
		else if (lhs.base() > rhs.base())
			return false;
		return true;
	}
}

#endif
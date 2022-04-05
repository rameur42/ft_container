/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:33:42 by rameur            #+#    #+#             */
/*   Updated: 2022/04/01 18:46:44 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"

#include <iostream>
#include <new>
#include <exception>

#include <memory>
#include <iterator>


namespace ft {
	template< class T, class Alloc = std::allocator<T> >
	class vector {
		public:
		
			typedef T														value_type;
			typedef Alloc													allocator_type;
			typedef unsigned int											size_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename ft::vecIterator<value_type>					iterator;
			typedef typename ft::vecIterator<const value_type>				const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef	typename ft::iterator_traits<iterator>::difference_type	difference_type;

			//constructor/copy/destructor-------------------------------------------------------------------------------------
			explicit vector(const allocator_type& alloc = allocator_type())
			{
				this->_alloc = alloc;
				this->_n = 0;
				this->_capacity = 0;
				this->_begin = NULL;
				this->_end = NULL;
			}

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				this->_alloc = alloc;
				this->_n = n;
				this->_capacity = n;
				this->_begin = this->_alloc.allocate(n);
				this->_end = this->_begin;
				try {
					for (size_type i = 0; i < n; i++)
					{
						this->_alloc.construct(this->_end, val);
						this->_end++;
					}
				}
				catch (std::bad_alloc & e)
				{
					std::cout << e.what() << std::endl;
				}
			}

			template <class InputIterator>
				vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				this->_alloc = alloc;
				this->_n = 0;
				for (InputIterator tmp = first; tmp != last; tmp++)
					this->_n++;
				this->_capacity = this->_n;
				this->_begin = this->_alloc.allocate(this->_n);
				this->_end = this->_begin;
				try {
					while (first != last)
					{
						this->_alloc.construct(this->_end, *first);
						this->_end++;
						first++;
					}
				}
				catch (std::bad_alloc & e)
				{
					std::cout << e.what() << std::endl;
				}
			}
			
			vector(const vector & x)
			{
				pointer tmp;
				
				this->_n = x._n;
				this->_capacity = this->_n;
				this->_begin = this->_alloc.allocate(x._n);
				this->_end = this->_begin;

				tmp = x._begin;
				for (unsigned int i = 0; i < x._n; i++)
				{
					this->_alloc.construct(this->_end, *tmp);
					tmp++;
					this->_end++;
				}
			}
			
			~vector() { this->_alloc.deallocate(this->_begin, this->_capacity); }
			
			vector&	operator=(const vector& rhs)
			{
								pointer tmp;

				if (this != &rhs)
				{
					this->_n = rhs._n;
					this->_capacity = rhs._capacity;
					this->_begin = this->_alloc.allocate(rhs._n);
					this->_end = this->_begin;
					tmp = rhs._begin;
					for (unsigned int i = 0; i < rhs._n; i++)
					{
						this->_alloc.construct(this->_end, *tmp);
						tmp++;
						this->_end++;
					}
				}
				return (*this);
			}
			//iterators------------------------------
			iterator	begin()
			{
				iterator res = this->_begin;
				return	res;
			}

			const_iterator begin() const
			{
				const_iterator res = this->_begin;
				return res;
			}
			
			reverse_iterator	rbegin(void)
			{
				return (reverse_iterator(this->_end));
			}
			
			const_reverse_iterator	rbegin(void) const
			{
				return (const_reverse_iterator(this->_end));
			}
			
			reverse_iterator	rend(void)
			{
				return (reverse_iterator(this->_begin));
			}

			const_reverse_iterator	rend(void) const
			{
				return (const_reverse_iterator(this->_begin));
			}
			
			iterator	end()
			{
				iterator res = this->_end;
				return res;
			}
			
			const_iterator end() const
			{
				const_iterator res = this->_end;
				return res;
			}

			//Capacity--------------------------------------------------------
			size_type	size() const { return this->_n; }

			size_type	max_size() const { return this->_alloc.max_size(); }

			void		resize(size_type n, value_type val = value_type()) {
				if (n < this->_n)
				{
					while (this->_n > n)
					{
						this->_alloc.destroy(this->_end);
						this->_end--;
						this->_n--;
					}
				}
				else if (n > this->_n)
				{
					if (n > this->_capacity)
						this->reserve(n);
					while (this->_n < n)
					{
						this->_alloc.construct(this->_begin + this->_n, val);
						this->_n++;
					}
					this->_end = this->_begin + this->_n;
				}
			}

			size_type	capacity() const { return this->_capacity; }
			
			bool		empty() const {
				if (this->_n == 0)
					return true;
				return false;
			}
			
			void	reserve(size_type n) {
				if (n > this->_capacity)
				{
					if (n > this->max_size())
						throw std::length_error("Error: reserve can't alloc more than max_size");
					vector res;
					iterator tmp = this->begin();
	
					res._begin = res._alloc.allocate(n);
					res._end = res._begin;
					for (size_type i = 0; tmp != this->end(); ++tmp)
					{
						res._alloc.construct(res._begin + i, *tmp);
						i++;
						res._end++;
					}
					this->_alloc.deallocate(this->_begin, this->_capacity);
					this->_alloc = res._alloc;
					this->_capacity = n;
					this->_begin = res._begin;
					this->_end = res._end;
					res._begin = NULL;
				}
			}

			//Element access----------------------------------------------------------
			reference		operator[](size_type n) { return (this->_begin[n]); }
			
			const_reference	operator[](size_type n) const { return (this->_begin[n]); }
			
			reference		at(size_type n) {
				if (n > this->_n)
					throw std::out_of_range("Error: out of range");
				return (this->_begin[n]);
			}
			
			const_reference	at(size_type n) const {
				if (n > this->_n)
					throw std::out_of_range("Error: out of range");
				return (this->_begin[n]);
			}
			
			reference		front() {return *(this->_begin);}
			
			const_reference	front() const { return *(this->_begin);}
			
			reference		back() { return *(this->_end - 1); }
			
			const_reference	back() const { return *(this->_end - 1); }
			
			//Modifiers--------------------------------------------------------------
			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				InputIterator tmp = first;
				size_type i = 0;
				while (tmp != last)
				{
					tmp++;
					i++;
				}
				this->clear();
				this->_n = i;
				if (i != this->_capacity)
				{
					this->reserve(i);
				}
				this->_end = this->_begin + this->_n;
				for (size_type j = 0; j < this->_n; j++)
				{
					this->_alloc.construct(this->_begin + j, *first);
					first++;
				}
			}
			
			void	assign(size_type n, const value_type& val)
			{
				this->clear();
				if (n > this->_capacity)
				{
					this->reserve(n);
				}
				this->_n = n;
				this->_end = this->_begin + this->_n;
				for (size_type i = 0; i < this->_n; i++)
					this->_alloc.construct(this->_begin + i, val);
			}

			void	push_back(const value_type & val)
			{
				if (this->_capacity == this->_n)
					this->reserve(this->_capacity + 6);
				this->_alloc.construct(this->_end, val);
				this->_end++;
				this->_n++;
			}
			
			void	pop_back()
			{
				if (this->_n > 0)
				{
					this->_alloc.destroy(this->_end);
					this->_end--;
					this->_n--;
				}
			}

			iterator insert(iterator position, const value_type & val)
			{
				size_type	pos = 0;
				for (iterator tmp = this->begin();tmp != position; tmp++)
				{
					pos++;
					if (tmp == this->end())
						return position;
				}
				iterator pEnd = this->_end;
				resize(this->_n + 1);
				iterator nEnd = this->_end;
				iterator res = this->begin();
				size_type e = this->_n;
				while (e > pos)
				{
					*nEnd = *pEnd;
					pEnd--;
					nEnd--;
					e--;
				}
				for (size_type i = 0; i < pos; i++)
					res++;
				*res = val;
				return res;
			}

			void	insert(iterator position, size_type n, const value_type & val)
			{
				size_type	pos = 0;
				for (iterator tmp = this->begin(); tmp != position; tmp++)
				{
					pos++;
					if (tmp == this->end())
						return ;
				}
				iterator pEnd = this->_end;
				resize(this->_n + n);
				iterator nEnd = this->_end;
				iterator res = this->begin();
				size_type e = this->_n;
				while (e >= (pos + n))
				{
					*nEnd = *pEnd;
					pEnd--;
					nEnd--;
					e--;
				}
				for (size_type i = 0; i < pos; i++)
					res++;
				for (size_type t = 0; t < n; t++)
				{
					*res = val;
					res++;
				}
			}

			template < class InputIterator >
				void	insert (iterator position, InputIterator first, InputIterator last, 
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
				{
					size_type	pos = 0;
					for (iterator tmp = this->begin(); tmp != position; tmp++)
					{
						pos++;
						if (tmp == this->end())
							return ;
					}
					size_type d = 0;
					for (InputIterator tmp = first; tmp != last; tmp++)
						d++;
					iterator pEnd = this->_end;
					resize(this->_n + d);
					iterator nEnd = this->_end;
					iterator res = this->begin();
					size_type e = this->_n;
					while (e >= (pos + d))
					{
						*nEnd = *pEnd;
						pEnd--;
						nEnd--;
						e--;
					}
					for (size_type i = 0; i < pos; i++)
						res++;
					for (size_type t = 0; t < d; t++)
					{
						*res = *first;
						res++;
						first++;
					}
				}
			
			iterator erase(iterator position)
			{
				iterator t = this->end();
				while (t != position)
				{
					if (t == this->begin())
						return position;
					t--;
				}
				t = position.get_p() + 1;
				iterator res = t;
				while (t != this->end())
				{
					*position = *t;
					position++;
					t++;
				}
				this->_alloc.destroy(this->_begin + this->_n);
				this->_n--;
				this->_end--;
				return res;
			}
			//lesk a checker sur linux

			iterator erase(iterator first, iterator last)
			{
				size_type d = 0;
				for (iterator tmp = first; tmp != last; tmp++)
					d++;
				iterator t = this->end();
				while (t != first)
				{
					if (t == this->begin() && this->begin() != first)
						return first;
					t--;
				}
				t = first.get_p() + 1;
				for (size_type i = 0; i <= d; i++)
				{
					*first = *last;
					first++;
					last++;
				}
				for (size_type j = 0; j < d; j++)
				{
					this->_alloc.destroy(this->_begin + this->_n);
					this->_n--;
					this->_end--;
				}
				return t;
			}

			void	swap(vector & x)
			{
				allocator_type	tmpAlloc = x._alloc;
				size_type		tmpN = x._n;
				size_type		tmpCapacity = x._capacity;
				pointer			tmpBegin = x._begin;
				pointer			tmpEnd = x._end;

				x._alloc = this->_alloc;
				x._n = this->_n;
				x._capacity = this->_capacity;
				x._begin = this->_begin;
				x._end = this->_end;

				this->_alloc = tmpAlloc;
				this->_n = tmpN;
				this->_capacity = tmpCapacity;
				this->_begin = tmpBegin;
				this->_end = tmpEnd;
			}
			
			void	clear()
			{
				size_type len = this->size();

				for (size_type i = 0; i < len; i++)
				{
					this->_end--;
					this->_alloc.destroy(this->_end);
				}
				this->_n = 0;
			}

			//Allocator----------------------------------------------
			allocator_type get_allocator() const { return this->_alloc; }
		private:
			allocator_type	_alloc;
			size_type		_n;
			size_type		_capacity;
			pointer			_begin;
			pointer			_end;
	};

	template <class T, class Alloc>
		bool	operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			if (lhs.size() == rhs.size())
			{
				typename vector<T>::const_iterator l = lhs.begin();
				typename vector<T>::const_iterator r = rhs.begin();
				while(l != lhs.end() && r != rhs.end())
				{
					if (*l != *r)
						return (false);
					l++;
					r++;
				}
				return true;
			}
			return false;
		}
	
	template <class T, class Alloc>
		bool	operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (!(lhs == rhs));
		}

	template <class T, class Alloc>
		bool	operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
	
	template <class T, class Alloc>
		bool	operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			if (ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
				return true;
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
	
	template <class T, class Alloc>
		bool	operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			if (ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
				return false;
			return (!(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())));
		}

	template <class T, class Alloc>
		bool	operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			if (ft::equal(rhs.begin(), rhs.end(), lhs.begin()))
				return true;
			return (!(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())));
		}

	template <class T, class Alloc>
		void	swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
		{
			x.swap(y);
		}
}

#endif
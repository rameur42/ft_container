/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:33:42 by rameur            #+#    #+#             */
/*   Updated: 2022/04/06 06:58:55 by rameur           ###   ########.fr       */
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
#include <iterator>
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
			typedef T*														iterator;
			typedef const T*												const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef	typename ft::iterator_traits<iterator>::difference_type	difference_type;

			//constructor/copy/destructor-------------------------------------------------------------------------------------
			/*explicit vector(const allocator_type& alloc = allocator_type())
			{
				this->_alloc = alloc;
				this->_n = 0;
				this->_capacity = 0;
				this->_begin = NULL;
				this->_end = NULL;
			}

			//fill constructor
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				this->_alloc = alloc;
				this->_n = n;
				this->_begin = NULL;
				this->_end = NULL;
				if (n > _alloc.max_size())
					throw std::out_of_range("error");
				if (n)
				{
					this->_capacity = n;
					this->_begin = this->_alloc.allocate(n);
				}
				else
					_capacity = 0;
				this->_end = this->_begin;
				for (size_type i = 0; i < n; i++)
				{
					this->_alloc.construct(this->_end, val);
					this->_end++;
				}
			}

			//range constructor
			template <class InputIterator>
				vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				this->_alloc = alloc;
				difference_type d = std::distance(first, last);
				this->_n = d;
				this->_capacity = this->_n;
				//if (d)
				//{
					if (this->_capacity > _alloc.max_size())
						throw std::out_of_range("error");
					this->_begin = this->_alloc.allocate(this->_capacity);
					while (first != last)
					{
						this->_alloc.construct(this->_end, *first);
						this->_end++;
						first++;
					}
					_end = _begin + _n;
				//}
			}
			
			//copy constructor
			vector(const vector & x)
			{
				pointer tmp;
				
				this->_begin = NULL;
				this->_n = x._n;
				this->_capacity = this->_n;
				if (x._capacity)
					this->_begin = this->_alloc.allocate(x._capacity);
				this->_end = this->_begin;
				tmp = x._begin;
				for (unsigned int i = 0; i < x._n; i++)
				{
					this->_alloc.construct(this->_end, *tmp);
					tmp++;
					this->_end++;
				}
			}
			
			
			~vector()
			{ 
				this->clear();
				if (this->_capacity != 0)
					this->_alloc.deallocate(this->_begin, this->_capacity);
			}
			
			vector&	operator=(const vector& rhs)
			{
				pointer tmp;
				
				if (this != &rhs)
				{
					this->_dealloc();
					if (rhs.empty())
						return (*this);
					this->_n = rhs._n;
					this->_capacity = rhs._capacity;
					if (this->capacity() > _alloc.max_size())
						throw std::out_of_range("error");
					this->_begin = this->_alloc.allocate(rhs._capacity);
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
			}*/

			explicit vector(const allocator_type& alloc = allocator_type()) {
				
				this->_alloc = alloc;
				this->_n = 0;
				this->_capacity = 0;
				this->_begin = NULL;
				this->_end = NULL;
			}

			// fill constructor
			explicit vector(size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type()) {

				_alloc = alloc;
				_begin = NULL;
				if (n > _alloc.max_size())
					throw std::out_of_range("error");
				//_check_range(n);
				if (n)
				{
					_begin = _alloc.allocate(n);
					_capacity = n;
				}
				else
					_capacity = 0;
				_n = n;
				_end = _begin + _n;
				iterator	pos = _begin;
				for (size_type i = 0; i < n; i++)
					_alloc.construct(pos++, val);
			}

			// range constructor
			template < class InputIterator >
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
			
					_alloc = alloc;
					difference_type dist = std::distance(first, last);
					this->_n = static_cast<size_type>(dist);
					this->_capacity = static_cast<size_type>(dist);
					if (dist)
					{    
						if (_capacity > _alloc.max_size())
							throw std::out_of_range("error");
						//_check_range(_capacity);
						_begin = _alloc.allocate(_capacity);
						std::uninitialized_copy(first, last, this->_begin);
					}
					_end = _begin + _n;
			}

			// copy constructor
			vector(const vector& src) {

				_begin = NULL;
				_n = src._n;
				_capacity = src._capacity;
				if (src._capacity)
					_begin = _alloc.allocate(_capacity);
				if (src._capacity)
					std::uninitialized_copy(src._begin, src._begin + src._n, _begin);
				_end = _begin + _n;
			}


//======================================DESTRUCTOR======================================//

			virtual ~vector() {

				this->clear();
				if (_capacity)
					_alloc.deallocate(_begin, _capacity);
			}


//=================================ASSIGNATION OPERATOR=================================//

			vector	&operator=(const vector& rhs) {

				if (*this != rhs)
				{
					this->_dealloc();
					if (rhs.empty())
						return (*this);
					this->_n = rhs.size();
					this->_capacity = rhs.capacity();
					if (this->capacity() > _alloc.max_size())
						throw std::out_of_range("error");
					//_check_range(rhs.capacity());
					_begin = _alloc.allocate(rhs.capacity());
					_capacity = rhs.capacity();
					std::uninitialized_copy(rhs.begin(), rhs.end(), this->_begin);
					_end = _begin + _n;
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

			/*void		resize(size_type n, value_type val = value_type()) {
				if (n == 0)
					return (clear());
				if (n < this->_n)
				{
					while (this->_n > n)
					{
						this->_alloc.destroy(this->_end - 1);
						this->_end--;
						this->_n--;
					}
				}
				else if (n > this->_n)
				{
					std::cout << "this->_n" << this->_n << " | " << n << " | " << this->_capacity << std::endl;
					if (n > this->_capacity)
						this->reserve(n);
					//std::uninitialized_copy(this->_begin)
					while (this->_n < n)
					{
						this->_alloc.construct(this->_begin + this->_n, val);
						this->_n++;
					}
					this->_end = this->_begin + this->_n;
				}
			}*/

			void _dealloc()
			{
			    if (_capacity)
			    {
			        for (size_type i = 0; i < _n; i++)
			            _alloc.destroy(_begin + i);
			        _alloc.deallocate(_begin, _capacity);
			    }
			    _capacity = 0;
			    _n = 0;
				_end = NULL;
				_begin = NULL;
			}

			void _realloc_fill(size_type new_size, value_type const & value)
			{
			    iterator temp = this->_alloc.allocate(new_size);
			    size_type old_size(_n);
			    std::uninitialized_copy(_begin, _begin + _n, temp);
			    _dealloc();
			    _begin = temp;
			    std::uninitialized_fill(_begin + old_size, _begin + new_size, value);
			    _n = new_size;
				_end = _begin + _n;
			    _capacity = new_size;
			}
			
			void resize(size_type size, value_type val = value_type())
			{
				if (size > _alloc.max_size())
					throw std::out_of_range("error");
			    if (size == this->_n)
			        return ;
			    if (size == 0)
			        return (clear());
			    if (size < this->_n)
			    {
			        iterator it = end();
			        size_type diff = this->_n - size;
			        while (diff--)
			        {
			            this->_alloc.destroy(--it);
			            this->_n--;
			        }
					this->_end = this->_begin + this->_n;
			        return ;
			    }
			    if (size > this->_n)
			        this->_realloc_fill(size, val);
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
			
			reference		back() { return *(this->_begin + (this->_n - 1)); }
			
			const_reference	back() const { return *(this->_begin + (this->_n - 1)); }
			
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
				if (this->_capacity <= this->_n)
					this->reserve(this->_capacity + 6);
				this->_alloc.construct(this->_end, val);
				this->_end++;
				this->_n++;
			}
			
			void	pop_back()
			{
				if (this->_n > 0)
				{
					this->_alloc.destroy(this->_end - 1);
					this->_end--;
					this->_n--;
				}
			}

			iterator insert(iterator position, const value_type & val)
			{
				difference_type res = std::distance(this->begin(), position);
				insert(position, 1, val);
				return this->_begin + res;
			}
			
			void	insert(iterator position, size_type n, const value_type& val) {

				difference_type			beginToPos = std::distance(this->begin(), position);
				difference_type			prevSize = this->_n;
				iterator				prevEnd;
				iterator				end;

				this->resize(this->_n + n);

				prevEnd = this->begin() + prevSize;
				position = this->begin() + beginToPos;
				end = this->_begin + this->_n;
				while (prevEnd != position) {

					*(--end) = *(--prevEnd);
				}
				while (0 < n) {

					*position++ = val;
					n--;
				}
				this->_end = this->_begin + this->_n;
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
					size_type d = std::distance(first, last);
					difference_type p = std::distance(this->begin(), this->end());
					resize(this->_n + d);
					iterator pEnd = this->_begin + (p - 1);
					iterator nEnd = this->_end - 1;
					iterator res = this->begin();
					size_type e = this->_n;
					while (e > (pos + d))
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
				if (position == end())
					return position;
				return (this->erase(position, position + 1));
			}

			iterator	erase(iterator first, iterator last) {

				if (first == last)
					return (first);
				if (last == end())
				{
					for (iterator i = first; i != last; i++)
					{
						this->_alloc.destroy(i);
						this->_n--;
						this->_end--;
					}
					return (first);
		
				}
				iterator it = first;
				difference_type size = std::distance(first, last);
				while (it != last)
				{
					this->_alloc.destroy(it);
					it++;
				}
				it = first;
				while (it + size != end())
				{
					this->_alloc.construct(it, *(it + size));
					this->_alloc.destroy(it + size);
					it++;
				}
				this->_n -= static_cast<size_type>(size);
				this->_end = this->_begin + this->_n;
				return (first);
			}

			void	swap(vector & x)
			{
				std::swap(this->_alloc, x._alloc);
				std::swap(this->_n, x._n);
				std::swap(this->_capacity, x._capacity);
				std::swap(this->_begin, x._begin);
				std::swap(this->_end, x._end);
			}
			
			void	clear()
			{
				if (this->_n == 0)
					return;
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
			if (lhs != rhs)
				return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
			return false;
		}
	
	template <class T, class Alloc>
		bool	operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			if (lhs == rhs)
				return true;
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
	
	template <class T, class Alloc>
		bool	operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			if (lhs != rhs)
				return (!(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())));
			return false;
		}

	template <class T, class Alloc>
		bool	operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			if (lhs == rhs)
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
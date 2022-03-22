/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:33:42 by rameur            #+#    #+#             */
/*   Updated: 2022/03/22 18:03:27 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"

#include <iostream>
#include <new>
#include <exception>

#include <memory>
#include <iterator>


namespace ft {
	template< class T, class Alloc = std::allocator<T> >
	class vector {
		public:
		
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef unsigned int									size_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename ft::vecIterator<value_type>			iterator;
			typedef typename ft::vecIterator<const value_type>		const_iterator;
			//typedef typename ft::rVecIterator<value

			//constructor/copy/destructor
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
			
			//iterators
			iterator	begin()
			{
				iterator res = this->_begin;
				return	res;
			}

			const_iterator begin() const
			{
				const_iterator res = this->begin;
				return res;
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

			//Capacity
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
					{
						this->_alloc.allocate(n - this->_n);
						this->_capacity = n;
					}
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
			}
		private:
			allocator_type	_alloc;
			size_type		_n;
			size_type		_capacity;
			pointer			_begin;
			pointer			_end;
	};
}
#endif
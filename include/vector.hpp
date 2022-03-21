/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:33:42 by rameur            #+#    #+#             */
/*   Updated: 2022/03/21 18:54:29 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

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
			//typedef typename value_type::iterator

			explicit vector(const allocator_type& alloc = allocator_type())
			{
				this->_alloc = alloc;
				this->_n = 0;
				this->_val = 0;
				std::cout << "hello there" << std::endl;
			}

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				this->_alloc = alloc;
				this->_n = n;
				this->_val = val;
				try {
					for (size_type i = 0; i < n; i++)
						this->_alloc.construct(this->_alloc.allocate(1), val);
				}
				catch (std::bad_alloc & e)
				{
					std::cout << e.what() << std::endl;
				}
			}
			
		private:
			value_type		_val;
			allocator_type	_alloc;
			unsigned int	_n;
	};
}
#endif
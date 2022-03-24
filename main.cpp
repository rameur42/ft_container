/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:33:32 by rameur            #+#    #+#             */
/*   Updated: 2022/03/24 18:29:35 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>

template< typename T >
void	ft_print_vector(ft::vector<T> & src)
{
	for (typename ft::vector<T>::iterator it = src.begin(); it != src.end(); it++)
		std::cout << *it << std::endl;
}

template< typename T >
void	ft_print_vector(std::vector<T> & src)
{
	for (typename std::vector<T>::iterator it = src.begin(); it != src.end(); it++)
		std::cout << *it << std::endl;
}

int	main()
{
	//std::vector<int> v(10, 4);
	ft::vector<int> test(5, 4);

	//ft::vector<int> cp(test);
	
	//ft_print_vector(cp);
	test.resize(8, 6);
	std::cout << "test-<" << test.back() << std::endl;
	//test.reserve(25);
	//test.resize(30, 54);
	//test.reserve(45);
	//v.resize(8, 6);
	//ft_print_vector(v);
	std::cout << "size->" << test.size() << "| capacity->" << test.capacity() << std::endl;
	ft_print_vector(test);
	
	/*std::vector<int>	test;
	test = std::vector<int>(10, 2);
	for (std::vector<int>::iterator it = test.begin(); it < test.end(); it++)
		std::cout << *it << std::endl;
	std::cout << test.size() << "|" << test.capacity() << "|" << test.max_size() << "|" << std::endl;*/
	return 0;
}
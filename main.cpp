/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:33:32 by rameur            #+#    #+#             */
/*   Updated: 2022/03/27 22:45:59 by rameur           ###   ########.fr       */
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
	//std::vector<int> tes(8, 23);
	//std::vector<int>::iterator l = tes.end();
	ft::vector<int> test(10, 42);
	ft::vector<int>::iterator b = test.begin();

	//test.assign(b, l);
	//test.assign(10, 42);
	b++;
	test.insert(b, 68);
	//ft_print_vector(test);
	//std::cout << "size->" << test.size() << "| capacity->" << test.capacity() << std::endl;
	//ft::vector<int> cp(test);
	
	//ft_print_vector(cp);
	//test.resize(8, 6);
	//std::cout << "test-<" << test.back() << std::endl;
	//test.reserve(25);
	//test.resize(30, 54);
	//test.reserve(45);
	//v.resize(8, 6);
	//ft_print_vector(v);
	//test.clear();
	//std::cout << *(test.begin()) << " | " << *(test.end()) << std::endl;
	//test.push_back(58);
	//std::cout << "size->" << test.size() << "| capacity->" << test.capacity() << std::endl;
	//ft_print_vector(test);

	//test.pop_back();
	std::cout << "size->" << test.size() << "| capacity->" << test.capacity() << std::endl;
	ft_print_vector(test);
	/*std::vector<int>	test;
	test = std::vector<int>(10, 2);
	for (std::vector<int>::iterator it = test.begin(); it < test.end(); it++)
		std::cout << *it << std::endl;
	std::cout << test.size() << "|" << test.capacity() << "|" << test.max_size() << "|" << std::endl;*/
	return 0;
}

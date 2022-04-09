/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:33:32 by rameur            #+#    #+#             */
/*   Updated: 2022/04/09 05:58:09 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <string>
#include <iterator>
#include <cstdlib>
#include <climits>
#include <cstddef>
#define MAX_TEST_SIZE 512

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

	//ft::vector<std::string> x(10, "Why are you being so stubborn?");
	std::vector<std::string> y;
	ft::map<int, std::string> test;
	
	ft::pair<int, std::string> p1 = ft::make_pair<int, std::string>(2, "salut");
	ft::pair<int, std::string> p2 = ft::make_pair<int, std::string>(1, "ca");
	ft::pair<int, std::string> p3 = ft::make_pair<int, std::string>(5, "marche");
	ft::pair<int, std::string> p5 = ft::make_pair<int, std::string>(4, "?");
	ft::pair<int, std::string> p6 = ft::make_pair<int, std::string>(0, "ceci");
	ft::pair<int, std::string> p7 = ft::make_pair<int, std::string>(6, "la");
	ft::pair<int, std::string> p8 = ft::make_pair<int, std::string>(9, "test");
	ft::pair<int, std::string> p9 = ft::make_pair<int, std::string>(7, "chaine");
	ft::pair<int, std::string> p10 = ft::make_pair<int, std::string>(12, "bounce");
	ft::pair<int, std::string> p11 = ft::make_pair<int, std::string>(6, "player");
	ft::pair<int, std::string> p12 = ft::make_pair<int, std::string>(8, "nouveau");

	test.insert(p1);
	test.insert(p2);
	test.insert(p3);
	test.insert(p5);
	test.insert(p6);
	test.insert(p7);
	test.insert(p8);
	test.insert(p9);
	test.insert(p10);
	test.insert(p11);
	test.insert(p12);
	
 	test.print();
	
	test.erase(2);
	
	ft::map<int, std::string>::iterator b = test.begin();
	ft::map<int, std::string>::iterator e = test.end();
	ft::map<int, std::string> test1(b, e);
	//std::cout << test1[3] << " | " << test1.size() << std::endl;
 	test1.print();
	//test1.print();
	//ft::vector<std::string> z;
	//x = ft::vector<std::string>(std::rand() % MAX_TEST_SIZE, "Why are you being so stubborn?");
	
    //y.assign(x.begin(), x.end() - (std::rand() % x.size()));
	//std::cout << y.capacity() << std::endl;
	y.push_back("SALUT");
	y.assign(10, "Why are you beingbeing so stubborn?");
	y.assign(10, "Why are you beingbeing so stubborn?");
	y.assign(10, "Why are you beingbeing so stubborn?");
	y.assign(10, "Why are you beingbeing so stubborn?");
	y.assign(10, "Why are you beingbeing so stubborn?");
	y.assign(10, "Why are you beingbeing so stubborn?");
	//y.insert(y.begin(), 46, "salut");
	//y = x;
//	y.push_back("salut");/

	/*std::vector<std::string> i(10, "Why are you being so stubborn?");
	std::vector<std::string> j = std::vector<std::string>(i.begin(), i.end());
	//x = ft::vector<std::string>(std::rand() % MAX_TEST_SIZE, "Why are you being so stubborn?");
	int ft = 0;
	j.push_back("salut");
	for (ft::vector<std::string>::const_iterator it = y.begin(); it != y.end(); it++)
	{
		std::cout << "ft=" << *it << std::endl;
		ft++;
	}
	std::cout << "reverse->" << std::endl;
	for (ft::vector<std::string>::const_reverse_iterator it = y.rbegin(); it != y.rend(); it++)
	{
		std::cout << "r ft=" << *it << std::endl;
		ft++;
	}
	int std = 0;
	std::cout << "|||||||||||||||||||||||||||||||||||" << std::endl;
	for (std::vector<std::string>::const_iterator it = j.begin(); it != j.end(); it++)
	{
		std::cout << "std=" << *it << std::endl;
		std++;
	}
	std::cout << "reverse->" << std::endl;
	for (std::vector<std::string>::const_reverse_iterator it = j.rbegin(); it != j.rend(); it++)
	{
		std::cout << "r std=" << *it << std::endl;
		std++;
	}
	std::cout << "ft-> " << ft << " std-> " << std << std::endl;*/
 	//ft::vector<int> test;
	//ft::vector<int> tmp;
	//test.push_back(2);
	//test.push_back(5);
	//test.push_back(4);
	//test.push_back(6);
	//test.push_back(7);
	//test.push_back(1);
	//test.push_back(3);
	//ft::vector<int>::iterator b = test.begin();
	//b += 4;
	//ft::vector<int>::reverse_iterator it = test.rbegin();
	//std::cout << "it->" << *it<< std::endl;
	//it += 2;
	//std::cout << "base-> " << *(it.base()) << std::endl;
	//std::cout << "it->" << *it << std::endl;
	//ft_print_vector(test);
	//if (stmp >= stest)
	//	std::cout << "real ouaaaaaaaaa" << std::endl;
	//if (tmp >= test)
	//	std::cout << "my ouaaaaaaaaa" << std::endl;
	
	//ft::swap(test, tmp);
	//test.assign(b, l);
	//test.assign(10, 42);
	//ft::vector<int>::iterator p = test.begin();
	//ft::vector<int>::iterator b = test.begin();
	//std::vector<int>::iterator e = test.end();
	//ft::vector<int> range(b, e);
	//b -= 1;
	//e--;
	//e--;
	//e--;
	//p++;
	//std::cout << *b << " | " << std::endl;
	//test.erase(b);
	//b = test.end();
	//b--;
	//b--;
	//test.insert(b, 7, 32);
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
	//test.swap(tmp);
	//std::cout << "size->" << test.size() << "| capacity->" << test.capacity() << std::endl;
	//std::cout << "test-> " << std::endl;
	//ft_print_vector(test);
	//std::cout << "range-> " << std::endl;
	//ft_print_vector(range);
	/*std::vector<int>	test;
	test = std::vector<int>(10, 2);
	for (std::vector<int>::iterator it = test.begin(); it < test.end(); it++)
		std::cout << *it << std::endl;
	std::cout << test.size() << "|" << test.capacity() << "|" << test.max_size() << "|" << std::endl;*/
	return 0;
}

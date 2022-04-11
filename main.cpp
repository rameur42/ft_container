/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:33:32 by rameur            #+#    #+#             */
/*   Updated: 2022/04/11 05:06:53 by rameur           ###   ########.fr       */
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

template <typename _map>
    void test_count(_map &X, _map &Y)
    {
        std::cout << "TEST : ";
        std::cout << " - COUNT" << std::endl;
        
        _map Z(Y);

        for (int i = 0; i < 1024; i++)
        {
            std::cout << i ;
            if (Z.count(i) > 0)
                std::cout << " is in map" << std::endl;
            else
                std::cout << std::endl;
        }
        (void)X;
		std::cout << "double free" << std::endl;
    }

template <typename T>
class _const_test {
	public:
		typedef T	value_type;

		_const_test(void) : value() { };
		_const_test(value_type src) : value(src) { };
		_const_test(_const_test const &src) : value(src.value) { };
		~_const_test(void) { };
        
		void print(std::ostream &o) { o << "_const_test::print called [" << this->value << "]"; }
		void print(std::ostream &o) const { o << "_const_test::print const called [" << this->value << "]"; }
		_const_test &operator=(value_type src) { this->value = src; return *this; };
		_const_test &operator=(_const_test const &src) {
			this->value = src.value;
			return *this;
		}
		value_type	getValue(void) const { return this->value; }

		operator value_type(void) const
        {
			return value_type(this->value);
		}
        
	private:
		value_type	value;
};

template <typename _Type>
_Type rdm_val()
{
    return (_Type());
}

template <>
std::string rdm_val<std::string>()
{
    std::string default_val[24] =
    {
        "Take me with you.",
        "It's four in the morning. What are you doing?",
        "Why are you being so stubborn?",
        "I just wanted to do something good for once.",
        "How many times have I told you? You can't visit me here.",
        "I hope to repay your kindness someday.",
        "How did you get this scar?",
        "I thought you... I saw you get shot.",
        "I bought two. Here.",
        "I don't know. Shut up. I'm not blushing.",
        "Anything to eat around here?",
        "You want me? Here I am.",
        "You know you aren't allowed in here, right?",
        "Just let me do this for you.",
        "This isn't just about you. It's about what's best for all of us.",
        "Could you be happy here with me?",
        "Life is about more than just surviving.",
        "What was that for?",
        "Is... that my shirt you're wearing?",
        "Why can't you let me in? What are you so afraid of?",
        "Give me one good reason why I should believe you.",
        "I don't know how you do this every day...",
        "Your plan's gonna get us all killed, and you know it.",
        "I'm not even going to pretend to understand what you're talking about."
    };
    return (std::string(default_val[std::rand() % 18]));
}

template <>
int rdm_val<int>()
{
    return (int(std::rand() % 1024));
}

template <>
_const_test<int>	rdm_val<_const_test<int> >()
{
    return (_const_test<int>(rdm_val<int>()));
}

int	main()
{
    ft::pair<int, std::string> p1 = ft::make_pair<int, std::string>(23, "s");
    ft::pair<int, std::string> p2 = ft::make_pair<int, std::string>(2, "s");
    ft::pair<int, std::string> p3 = ft::make_pair<int, std::string>(3, "s");
    ft::pair<int, std::string> p4 = ft::make_pair<int, std::string>(24, "s");
    ft::pair<int, std::string> p5 = ft::make_pair<int, std::string>(29, "s");
    ft::pair<int, std::string> p6 = ft::make_pair<int, std::string>(28, "l");
	ft::map<int, std::string> Z;
	Z.insert(p1);
	Z.insert(p2);
	Z.insert(p3);
	Z.insert(p4);
	Z.insert(p5);
	Z.insert(p6);
	ft::map<int, int> M;
	Z.erase(3);

    std::pair<int, std::string> L1 = std::make_pair<int, std::string>(23, "s");
    std::pair<int, std::string> L2 = std::make_pair<int, std::string>(2, "s");
    std::pair<int, std::string> L3 = std::make_pair<int, std::string>(3, "s");
    std::pair<int, std::string> L4 = std::make_pair<int, std::string>(24, "s");
    std::pair<int, std::string> L5 = std::make_pair<int, std::string>(29, "s");
    std::pair<int, std::string> L6 = std::make_pair<int, std::string>(28, "l");
	std::map<int, std::string> X;
	X.insert(L1);
	X.insert(L2);
	X.insert(L3);
	X.insert(L4);
	X.insert(L5);
	X.insert(L6);
	std::map<int, int> N;
	X.erase(3);
	std::cout << "ft->  " << M.max_size() << std::endl;
	std::cout << "std-> " << X.max_size() << std::endl;
	std::cout << "std-> " << N.max_size() << std::endl;
	return 0;
}

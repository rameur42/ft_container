/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:10:02 by rameur            #+#    #+#             */
/*   Updated: 2022/03/29 17:13:26 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
#define EQUAL_HPP

namespace ft {
	template <class InputIterator1, class InputIterator2>
		bool equal (InputIterator1 first1, InputIterator1 last1,
					InputIterator2 first2)
		{
			while (first1 != last1)
			{
				if (*first1 != *first2)
					return false;
				first1++;
				first2++;
			}
			return true;
		}
}
#endif
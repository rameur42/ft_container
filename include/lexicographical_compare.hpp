/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:15:34 by rameur            #+#    #+#             */
/*   Updated: 2022/04/10 09:31:46 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICALE_COMPARE_HPP
#define LEXICOGRAPHICALE_COMPARE_HPP

namespace ft
{
	template <class InputIterator1, class InputIterator2>
		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2)
			{
				while (first1 != last1)
				{
					if (first2 == last2 || *first2 < *first1)
						return false;
					else if (*first1 < *first2)
						return true;
					first1++;
					first2++;
				}
				return (first2 != last2);
			}
} // namespace ft

#endif
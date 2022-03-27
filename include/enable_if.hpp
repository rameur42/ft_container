/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rameur <rameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:51:01 by rameur            #+#    #+#             */
/*   Updated: 2022/03/27 18:28:08 by rameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft
{
	template <bool Cond, class T = void>
		struct enable_if {};

	template <class T>
		struct enable_if<true, T> {typedef T type;};
} // namespace ft


#endif
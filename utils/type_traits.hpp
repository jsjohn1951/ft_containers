/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:08:34 by wismith           #+#    #+#             */
/*   Updated: 2023/03/29 12:38:30 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

# include <iostream>

/*
*	@brief : concept SFINAE (Substitution Failure Is Not An Error)
*	@example :
*		used in vector range functions to deduce if the iterators are indeed
*			iterators by checking if the iterators are integral.
*/

namespace ft
{
	template <bool, class T>
	struct enable_if{};

	template <class T>
	struct enable_if<true, T>{typedef T type;};

	/*
	*	@brief : generic is_integral has a const bool value of false
	*/
	template <class T>
	struct is_integral{static const bool value = false;};

	/*
	*	@brief : template specializations of is_integral has a const bool value of true
	*/

	template <>
	struct is_integral<bool>{static const bool value = true;};

	template <>
	struct is_integral<int>{static const bool value = true;};

	template <>
	struct is_integral<char>{static const bool value = true;};

	template <>
	struct is_integral<wchar_t>{static const bool value = true;};

	template <>
	struct is_integral<signed char>{static const bool value = true;};

	template <>
	struct is_integral<short>{static const bool value = true;};

	template <>
	struct is_integral<long>{static const bool value = true;};

	template <>
	struct is_integral<long long>{static const bool value = true;};

	template <>
	struct is_integral<unsigned char>{static const bool value = true;};

	template <>
	struct is_integral<unsigned short>{static const bool value = true;};

	template <>
	struct is_integral<unsigned int>{static const bool value = true;};

	template <>
	struct is_integral<unsigned long>{static const bool value = true;};

	template <>
	struct is_integral<unsigned long long>{static const bool value = true;};
};

#endif
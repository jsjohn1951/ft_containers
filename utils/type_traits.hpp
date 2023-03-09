/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:08:34 by wismith           #+#    #+#             */
/*   Updated: 2023/01/27 12:46:11 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

# include <iostream>

namespace ft
{
	template <bool, class T>
	struct enable_if{};

	template <class T>
	struct enable_if<true, T>{typedef T type;};

	template <class T>
	struct is_integral{static const bool value = false;};

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
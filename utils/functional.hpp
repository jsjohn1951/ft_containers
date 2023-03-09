/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functional.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:26:17 by wismith           #+#    #+#             */
/*   Updated: 2023/02/14 15:29:23 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef FUNCTIONAL_HPP
# define FUNCTIONAL_HPP

namespace ft
{
	//! Base class for standard binary function objects
	template <class Arg1, class Arg2, class Result>
  	struct binary_function
	{
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};
};

#endif
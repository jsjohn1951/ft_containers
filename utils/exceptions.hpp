/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:25:53 by wismith           #+#    #+#             */
/*   Updated: 2023/03/13 13:15:23 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

#include <iostream>

namespace ft
{
	class out_of_range : public std::exception
	{
		public :
			const char *what() const throw()
			{
				return ("vector");
			}
	};

	class length_error : public std::exception
	{
		public :
			const char *what() const throw() {
				return ("vector");
			}
	};
};

#endif
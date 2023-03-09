/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:25:53 by wismith           #+#    #+#             */
/*   Updated: 2023/02/26 16:29:02 by wismith          ###   ########.fr       */
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
				return ("Out Of Range Exception");
			}
	};
};

#endif
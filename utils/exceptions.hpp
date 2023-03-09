/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:25:53 by wismith           #+#    #+#             */
/*   Updated: 2023/03/10 00:09:37 by wismith          ###   ########.fr       */
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

	class logic_error : public std::exception
	{
		private :
			const std::string &s;
		public :
			explicit logic_error(const std::string& what_arg) : s(what_arg){}
			const char *what() const throw() { return (s.c_str()); }
	};

	class length_error : public ft::logic_error
	{
		public :
			explicit length_error (const std::string& what_arg): logic_error(what_arg) {}
	};
};

#endif
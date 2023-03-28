/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_it.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 01:30:14 by wismith           #+#    #+#             */
/*   Updated: 2023/03/29 01:45:35 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef VALID_IT_HPP
# define VALID_IT_HPP

# include "iterator_traits.hpp"
# include "type_traits.hpp"
# include <iterator>
# include <stdexcept>

namespace ft
{
	template <class InputIter>
	void	is_valid(InputIter first, InputIter last, typename ft::input_iterator_tag)
	{ (void) first; (void) last; }

	template <class InputIter>
	void	is_valid(InputIter first, InputIter last, typename std::input_iterator_tag)
	{ (void) first; (void) last; }

	template <class InputIter>
	void	is_valid(InputIter first , InputIter last, typename ft::random_access_iterator_tag)
	{
		if (first > last)
			throw (std::length_error("cannot create ft::vector larger than max_size()"));
	}

	template <class InputIter>
	void	is_valid(InputIter first , InputIter last, typename std::random_access_iterator_tag)
	{
		if (first > last)
			throw (std::length_error("cannot create ft::vector larger than max_size()"));
	}

	/*
	*	@brief : calls an is_valid function which is overloaded with iter_tags
	*	@note :
	*		the is_valid function throws std::length_error if first > last
	*/
	template <class InputIter>
	void	range_check(InputIter first, InputIter last)
	{
		is_valid(first, last, typename ft::iterator_traits<InputIter>::iterator_category());
	}
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:26:53 by wismith           #+#    #+#             */
/*   Updated: 2023/03/29 12:14:56 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <cstddef>

namespace ft
{

//! ----------------------- Iterator tags ------------------------------ !//
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
//! ----------------------- End Iterator tags -------------------------- !//

//* ----------------------- Iterator Traits ---------------------------- *//
	/*
	*	@brief : Iterator traits define properties of iterators
	*	@note :
	*		for every iterator type there is a corresponding iterator specialization
	*			of iterator_traits.
	*	@sources :
	*		https://cplusplus.com/reference/iterator/iterator_traits/
	*/
	template <class Iterator>
	struct iterator_traits
	{
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef const pointer							const_pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
			typedef T										value_type;
			typedef std::ptrdiff_t							difference_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef	ft::random_access_iterator_tag			iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
			typedef T										value_type;
			typedef std::ptrdiff_t							difference_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef	ft::random_access_iterator_tag			iterator_category;
	};
//* ----------------------- End Iterator Traits ------------------------ *//

	template <class tag, class T, class ptr = T*, class ref = T&, class diff = std::ptrdiff_t>
	struct iterator
	{
			typedef T										value_type;
			typedef diff									difference_type;
			typedef ptr										pointer;
			typedef const ptr								const_pointer;
			typedef ref										reference;
			typedef tag										iterator_category;
	};
};

#endif
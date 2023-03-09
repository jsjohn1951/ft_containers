/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:26:53 by wismith           #+#    #+#             */
/*   Updated: 2023/03/08 22:57:56 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <cstddef>

namespace ft
{
	class input_iterator_tag {};
	class output_iterator_tag;
	class forward_iterator_tag : public input_iterator_tag {};
	class bidirectional_iterator_tag : public forward_iterator_tag {};
	class random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class Iterator>
	class iterator_traits
	{
		public :

			iterator_traits(){}
			iterator_traits(const iterator_traits &iter)
			{
				if (this != &iter)
					*this = iter;
			}

			~iterator_traits(){}

			iterator_traits	&operator=(const iterator_traits &iter)
			{
				if (this != &iter)
					*this = iter;
				return (*this);
			}

			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef	typename Iterator::const_pointer		const_pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	class iterator_traits<T*>
	{
		public :

			iterator_traits(){}
			iterator_traits(const iterator_traits &iter)
			{
				if (this != &iter)
					*this = iter;
			}

			~iterator_traits(){}

			iterator_traits	&operator=(const iterator_traits &iter)
			{
				if (this != &iter)
					*this = iter;
				return (*this);
			}

			typedef T										value_type;
			typedef std::ptrdiff_t							difference_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef	ft::random_access_iterator_tag			iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>
	{
		public :

			iterator_traits(){}
			iterator_traits(const iterator_traits &iter)
			{
				if (this != &iter)
					*this = iter;
			}

			~iterator_traits(){}

			iterator_traits	&operator=(const iterator_traits &iter)
			{
				if (this != &iter)
					*this = iter;
				return (*this);
			}

			typedef T										value_type;
			typedef std::ptrdiff_t							difference_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef	ft::random_access_iterator_tag			iterator_category;
	};

	template <class tag, class T, class ptr = T*, class ref = T&, class diff = std::ptrdiff_t>
	class iterator
	{
		public :

			iterator(){}
			iterator(const iterator &iter)
			{
				if (this != &iter)
					*this = iter;
			}

			~iterator(){}

			iterator	&operator=(const iterator &iter)
			{
				if (this != &iter)
					*this = iter;
				return (*this);
			}

			typedef T										value_type;
			typedef diff									difference_type;
			typedef ptr										pointer;
			typedef const ptr								const_pointer;
			typedef ref										reference;
			typedef tag										iterator_category;
	};
};

#endif
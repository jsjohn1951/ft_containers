/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:08:03 by wismith           #+#    #+#             */
/*   Updated: 2023/02/09 16:22:08 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef REVITERATOR_HPP
# define REVITERATOR_HPP

#include "../utils/iterator_traits.hpp"

namespace ft
{
	template <class T>
	class revIterator
	{
		public :
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::const_pointer		const_pointer;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;

		private :
			pointer	ptr;

		public :
			//! Constructors
			revIterator(){}
			revIterator(pointer n_ptr) : ptr(n_ptr){}
			revIterator(const revIterator &Iter) : ptr(Iter.base()){}
			//! End Constructors

			//! Destructor
			~revIterator(){};
			//! End Destructor

			//! Operators
			revIterator	&operator=(const revIterator &Iter)
			{
				if (this != &Iter)
					this->ptr = Iter.base();
				return (*this);
			}

			reference	operator*() const
			{
				return (*this->ptr);
			}

			pointer		operator->() const
			{
				return (this->ptr);
			}


			revIterator	operator+(difference_type n)
			{
				return (revIterator(this->ptr - n));
			}

			revIterator	operator-(difference_type n)
			{
				return (revIterator(this->ptr + n));
			}

			revIterator	&operator+=(difference_type n)
			{
				this->ptr -= n;
				return (*this);
			}

			revIterator	&operator-=(difference_type n)
			{
				this->ptr += n;
				return (*this);
			}

			revIterator	operator++(int)
			{
				revIterator	nIter = *this;
				this->ptr--;
				return (nIter);
			}

			revIterator	&operator++()
			{
				this->ptr--;
				return (*this);
			}

			revIterator	operator--(int)
			{
				revIterator	nIter = *this;
				this->ptr++;
				return (nIter);
			}

			revIterator	&operator--()
			{
				this->ptr++;
				return (*this);
			}

			//! End Operators

			//! Member functions

			pointer base() const
			{
				return (this->ptr);
			}

			//! End Member functions
	};

	template <class T>
	bool	operator==(const revIterator<T> &Iter, const revIterator<T> &Iter2)
	{
		return (Iter.base() == Iter2.base());
	}

	template <class T>
	bool	operator!=(const revIterator<T> &Iter, const revIterator<T> &Iter2)
	{
		return (Iter.base() != Iter2.base());
	}
};

#endif
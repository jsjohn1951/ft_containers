/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:20:40 by wismith           #+#    #+#             */
/*   Updated: 2023/03/08 22:33:22 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef VECTORITERATOR
# define VECTORITERATOR

#include "../utils/iterator_traits.hpp"

namespace ft
{
	template <class T>
	class vectorIterator
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
			vectorIterator(){}
			vectorIterator(pointer n_ptr) : ptr(n_ptr){}

			template <class U>
			vectorIterator(const vectorIterator<U> &Iter) : ptr(Iter.base()){}
			//! End Constructors

			//! Destructor
			~vectorIterator(){};
			//! End Destructor

			//! Operators
			vectorIterator	&operator=(const vectorIterator &Iter)
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


			vectorIterator	operator+(difference_type n) const
			{
				return (vectorIterator(this->ptr + n));
			}

			vectorIterator	operator-(difference_type n) const
			{
				return (vectorIterator(this->ptr - n));
			}

			vectorIterator	&operator+=(difference_type n)
			{
				this->ptr += n;
				return (*this);
			}

			vectorIterator	&operator-=(difference_type n)
			{
				this->ptr -= n;
				return (*this);
			}

			vectorIterator	operator++(int)
			{
				vectorIterator	nIter = *this;
				this->ptr++;
				return (nIter);
			}

			vectorIterator	&operator++()
			{
				this->ptr++;
				return (*this);
			}

			vectorIterator	operator--(int)
			{
				vectorIterator	nIter = *this;
				this->ptr--;
				return (nIter);
			}

			vectorIterator	&operator--()
			{
				this->ptr--;
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

	template <class T, class U>
	bool	operator==(const vectorIterator<T> &Iter, const vectorIterator<U> &Iter2)
	{
		return (Iter.base() == Iter2.base());
	}

	template <class T, class U>
	bool	operator!=(const vectorIterator<T> &Iter, const vectorIterator<U> &Iter2)
	{
		return (Iter.base() != Iter2.base());
	}

	template <class T, class U>
	typename ft::vectorIterator<T>::difference_type
		operator-(const vectorIterator<T> &Iter, const vectorIterator<U> &Iter2)
	{
		return (Iter.base() - Iter2.base());
	}
};

#endif
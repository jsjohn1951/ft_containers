/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:08:03 by wismith           #+#    #+#             */
/*   Updated: 2023/03/17 12:29:54 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef REVITERATOR_HPP
# define REVITERATOR_HPP

#include "../utils/iterator_traits.hpp"
#include "vectorIterator.hpp"

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
			template <class IterType>
			revIterator(const revIterator<IterType> &Iter) : ptr(Iter.base()) {}
			revIterator(const ft::vectorIterator<T> &Iter) : ptr(Iter.base()){}
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
				pointer	tmp = this->ptr;
				return (*(--tmp));
			}

			reference	operator[](const difference_type n)
			{
				return (*(*this + n));
			}

			pointer		operator->() const
			{
				return (this->ptr - 1);
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

	template <class T, class U>
	bool	operator==(const revIterator<T> &Iter, const revIterator<U> &Iter2)
	{
		return (Iter.base() == Iter2.base());
	}

	template <class T, class U>
	bool	operator!=(const revIterator<T> &Iter, const revIterator<U> &Iter2)
	{
		return (Iter.base() != Iter2.base());
	}

	template <class T, class U>
	typename ft::revIterator<T>::difference_type
		operator-(const revIterator<T> &Iter, const revIterator<U> &Iter2)
	{
		return (Iter2.base() - Iter.base());
	}

	template <class T, class U>
	typename ft::revIterator<T>::difference_type
		operator+(const revIterator<T> &Iter, const revIterator<U> &Iter2)
	{
		return (Iter.base() + Iter2.base());
	}

	template <class T, class U>
	bool	operator<(const revIterator<T> &Iter, const revIterator<U> &Iter2)
	{
		return (Iter.base() > Iter2.base());
	}

	template <class T, class U>
	bool	operator>(const revIterator<T> &Iter, const revIterator<U> &Iter2)
	{
		return (Iter.base() < Iter2.base());
	}

	template <class T, class U>
	bool	operator<=(const revIterator<T> &Iter, const revIterator<U> &Iter2)
	{
		return (Iter.base() >= Iter2.base());
	}

	template <class T, class U>
	bool	operator>=(const revIterator<T> &Iter, const revIterator<U> &Iter2)
	{
		return (Iter.base() <= Iter2.base());
	}

	template <class T>
	revIterator<T>
	operator+(typename revIterator<T>::difference_type n,
		const revIterator<T> &it)
	{
		return revIterator<T>(it.base() - n);
	}

	template <class T>
	revIterator<T>
	operator-(typename revIterator<T>::difference_type n,
		const revIterator<T> &it)
	{
		return revIterator<T>(it.base() + n);
	}

	template <class T>
	bool	operator==(const vectorIterator<T> &vec, const T* t)
	{
		return (vec.base() == t);
	}
};

#endif
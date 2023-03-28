/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:39:44 by wismith           #+#    #+#             */
/*   Updated: 2023/03/29 02:28:29 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft
{
	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		InputIterator1 fst = first1;
		InputIterator2 fst2 = first2;
		while (fst != last1)
		{
			if (*fst != *fst2)
				return (false);
			fst++;
			fst2++;
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		InputIterator1 fst = first1;
		InputIterator2 fst2 = first2;
		while (fst != last1)
		{
			if (!pred(*fst, *fst2))
				return (false);
			fst++;
			fst2++;
		}
		return (true);
	}


	/*
	*	@brief : Used to iterate through and compare two iterators, will return true if values from iter1 < iter2
	*	@note :
	*		1. will iterate through the values while fst1 == fst2,
	*			returns as soon as it is not.
	*		2. if fst2 == lst2 the end has been reached for iter2, 
	*			iter1 would be greater, or equal to iter2.
	*		3. if *fst2 < *fst1 then the values in fst1 are greater
	*			again lexicographical_compare will return false.
	*		4. At the end of the loop if fst2 has reached lst2
	*			then the iterators are equal and the return will be
	*				false.
	*/
	template <class InputIter1, class InputIter2>
	bool	lexicographical_compare(InputIter1 fst1, InputIter1 lst1,
			InputIter2 fst2, InputIter2 lst2)
	{
		for (; fst1 != lst1; ++fst1, ++fst2)
		{
			if (fst2 == lst2 || *fst2 < *fst1)
				return (false);
			else if (*fst1 < *fst2)
				return (true);
		}
		return (fst2 != lst2);
	}

	/*
	*	@brief : this function overload exchanges the < operator with a compare function
	*/
	template <class InputIter1, class InputIter2, class Compare>
	bool	lexicographical_compare(InputIter1 fst1, InputIter1 lst1,
			InputIter2 fst2, InputIter2 lst2, Compare comp)
	{
		for (; fst1 != lst1; ++fst1, ++fst2)
		{
			if (fst2 == lst2 || comp(*fst2, *fst1))
				return (false);
			else if (*fst1 < *fst2)
				return (true);
		}
		return (fst2 != lst2);
	}
};

#endif
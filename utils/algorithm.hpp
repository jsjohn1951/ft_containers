/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:39:44 by wismith           #+#    #+#             */
/*   Updated: 2023/03/29 12:07:33 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft
{
	/*
	*	@brief : compares each iteration of two iterators
	*	@note :
	*		Given first and last of iter1, and first of iter2 as arguments, 
	*			the function will increment iter1's first
	*			and iter2's first, and compares each iteration.
	*		The first iteration that is != will cause the function to return a false.
	*/
	template <class InputIter1, class InputIter2>
	bool	equal(InputIter1 first1, InputIter1 last1, InputIter2 first2)
	{
		for (;first1 != last1; first1++, first2++)
			if (*first1 != *first2)
				return (false);
		return (true);
	}

	/*
	*	@brief : overload substitutes the != operator for a pred.
	*	@note :
	*		pred is a function.
	*/
	template <class InputIter1, class InputIter2, class BP>
	bool	equal(InputIter1 first1, InputIter1 last1, InputIter2 first2, BP pred)
	{
		for (;first1 != last1; first1++, first2++)
			if (!pred(*first1, *first2))
				return (false);
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
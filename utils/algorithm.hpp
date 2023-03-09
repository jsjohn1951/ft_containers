/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:39:44 by wismith           #+#    #+#             */
/*   Updated: 2023/02/12 15:41:25 by wismith          ###   ########.fr       */
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

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		InputIterator1 fst;
		InputIterator2 fst2;
		for (fst = first1, fst2 = first2; fst != last1; ++fst, ++fst2)
		{
			if (fst2 == last2 || *fst2 < *fst)
				return (false);
			else if (*fst < *fst2)
				return (true);
		}
		return (fst2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		InputIterator1 fst;
		InputIterator2 fst2;
		for (fst = first1, fst2 = first2; fst != last1; ++fst, ++fst2)
		{
			if (fst2 == last2 || comp(*fst, *fst2))
				return (false);
			else if (comp(*fst2, *fst))
				return (true);
		}
		return (fst2 != last2);
	}
};

#endif
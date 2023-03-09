/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:36:30 by wismith           #+#    #+#             */
/*   Updated: 2023/03/02 19:41:03 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template <class _T1, class _T2>
	class pair
	{
		public :
			typedef _T1	first_type;
			typedef _T2	second_type;

			first_type	first;
			second_type	second;
		
			pair(): first(), second(){}

			template<class U, class V>
			pair (const pair<U, V> &pr) : first(pr.first), second(pr.second){}

			pair (const first_type& a, const second_type& b) : first(a), second(b) {}

			pair	&operator=(const pair &pr)
			{
				if (this != &pr)
				{
					this->first = pr.first;
					this->second = pr.second;
				}
				return (*this);
			}
	};

	template <class T1, class T2>
	bool	operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	
	template <class T1, class T2>
	bool	operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		if (lhs.first != rhs.first)
			return (true);
		if (lhs.second != rhs.second)
			return (true);
		return (false);
	}

	template <class T1, class T2>
	bool	operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool	operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (rhs >= lhs);
	}

	template <class T1, class T2>
	bool	operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool	operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return (lhs >= rhs);
	}

	template <class T1, class T2>
	pair<T1, T2>	make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}
};

#endif
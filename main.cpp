/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 23:33:52 by wismith           #+#    #+#             */
/*   Updated: 2023/03/20 22:39:29 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map/map.hpp"
#include <map>
#include <string>
#include <list>

#if !defined(NAMESPACE)
# define NAMESPACE ft
#endif

#define T1 char
#define T2 int
typedef NAMESPACE::pair<const T1, T2> T3;

template <class F, class T>
void	printMap(NAMESPACE::map<F, T>	&map)
{
	typename NAMESPACE::map<F, T>::iterator	start, end;
	start = map.begin();
	end = map.end();
	char	c = 'A';
	for (; start != end; start++, c++)
	{
		std::cout << c << ") fst-> " << start->first << "  snd-> " << start->second << "\n";
		if (c == 'z' || c == 'Z')
			(std::islower(c) ? c = 'A' - 1 : c = 'a' - 1);
	}
}

template <class T>
void	printPair(const T &t)
{
	std::cout << "first : " << t->first << " second: " << t->second << std::endl;
}

template <class T>
T	&dec(T &it, int num)
{
	for (int i = 0; i < num; i++)
		it--;
	return (it);
}

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3('a' + i, (i + 1) * 7));

	NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	NAMESPACE::map<T1, T2>::iterator it_ = mp.begin();
	NAMESPACE::map<T1, T2>::reverse_iterator it(it_), ite;

	std::cout << (it_ == it.base()) << std::endl;
	std::cout << (it_ == dec(it, 3).base()) << std::endl;

	std::cout << "\nforward iterator:\n";
	printPair(it_);
	std::cout << "\nreverse iterator:\n";
	printPair(it);

	std::cout << "\nbase:\n";
	printPair(it.base());
	printPair(++(it.base()));

	std::cout << "TEST OFFSET" << std::endl;
	--it;
	printPair(it);
	printPair(it.base());

	return (0);
}

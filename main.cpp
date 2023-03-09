/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 23:33:52 by wismith           #+#    #+#             */
/*   Updated: 2023/03/09 00:53:27 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector/vector.hpp"
#include <vector>
#include <iostream>

int	main(void)
{
	ft::vector<int>	vec;
	ft::vector<int>::iterator it;

	vec.push_back(12);
	vec.push_back(9);
	vec.push_back(8);
	vec.push_back(13);
	vec.push_back(42);
	vec.push_back(2);
	
	ft::vector<int>	vec2;

	vec2.push_back(-9);
	vec2.push_back(-10);
	vec2.push_back(-8);
	
	std::cout << "vec2 capacity: " << vec2.capacity() << std::endl;
	std::cout << "vec2 size: " << vec2.size() << std::endl;
	for (it = vec2.begin(); it != vec2.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	vec.insert(--vec.end(), vec2.begin(), vec2.end());
	std::cout << "vec capacity: " << vec.capacity() << std::endl;
	std::cout << "vec size: " << vec.size() << std::endl;
	for (it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

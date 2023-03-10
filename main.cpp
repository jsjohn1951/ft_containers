/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 23:33:52 by wismith           #+#    #+#             */
/*   Updated: 2023/03/11 00:19:24 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector/vector.hpp"
#include "stack/stack.hpp"
#include <vector>
#include <stack>
#include <iostream>
#include <sys/time.h>
#include <iomanip>

# define NAMESPACE ft
int main() {
	timeval exec_time;
	gettimeofday(&exec_time, NULL);
	double start = 1.0e6 * exec_time.tv_sec + exec_time.tv_usec;

	NAMESPACE::stack<int> stack;

	stack.push(7);
	stack.push(9);
	stack.push(-3);
	stack.push(4);

	for (;stack.size(); stack.pop())
		std::cout << stack.top() << " ";
	std::cout << "\n";

	gettimeofday(&exec_time, NULL);
	double end = 1.0e6 * exec_time.tv_sec + exec_time.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}
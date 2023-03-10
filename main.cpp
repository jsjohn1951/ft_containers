/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 23:33:52 by wismith           #+#    #+#             */
/*   Updated: 2023/03/10 23:38:46 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector/vector.hpp"
#include <vector>
#include <iostream>
#include <sys/time.h>
#include <iomanip>

# define NAMESPACE std

static void basicTests();
static void exceptionTests();

template <typename T>
void pushRandomValues(NAMESPACE::vector<T> &vector, size_t size) {
	for (size_t i = 0; i < size; i++) {
		vector.push_back(10000 + (std::rand() % 50000));
	}
}

static void backTests();

int main() {
	timeval exec_time;
	gettimeofday(&exec_time, NULL);
	double start = 1.0e6 * exec_time.tv_sec + exec_time.tv_usec;

	backTests();

	gettimeofday(&exec_time, NULL);
	double end = 1.0e6 * exec_time.tv_sec + exec_time.tv_usec;
	std::cout << std::fixed << std::setprecision(3) << (end - start) / 1000 << " ms" << std::endl;
	return 0;
}

template <typename T>
void printVectorInfo(NAMESPACE::vector<T> &vector) {
	std::cout << "--------------------------------------------------" << std::endl << std::boolalpha
	          << "vector::empty() = " << vector.empty() << std::endl
	          << "vector::size() = " << vector.size() << std::endl
	        //   << "vector::max_size() = " << vector.max_size() << std::endl
	          << "Contents:" << std::endl;
}

template <typename T>
void printByOperator(NAMESPACE::vector<T> &vector) {
	printVectorInfo(vector);
	for (size_t i = 0; i < vector.size(); i++) {
		std::cout << "vector[" << i << "] = " << vector[i] << std::endl;
	}
}

static void backTests() {
	std::cout << "\n--------------------------------------------------" << std::endl
	          << "vector::back Tests" << std::endl;
	NAMESPACE::vector<int> test;
	pushRandomValues(test, 10);

	test.resize(1);
	test.resize(5, 987654321);
	printByOperator(test);
}
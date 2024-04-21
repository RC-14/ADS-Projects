/*
	Algorithms and data structures - Summer Semester 2024
	Exercise01 - Basic data structures and their operations and input processing
	---
	© FH Aachen - Facultie 5, Electrical Engineering and Information Technology - Insitute for Mobile Autonomous Systems and Cognitive Robotics
	Prof. Ingrid Scholl - scholl@fh-aachen.de
	---
	Please refer to the tasks provided in the PDF for this exercise.
	The PDF for this exercise can be found in the ILIAS course at https://www.ili.fh-aachen.de/.
*/

////// =================================================
////// Task05
////// =================================================

// # include "ads_excercise01/DoubleStack.hpp"
# include "../include/ads_excercise01/DoubleStack.hpp"
#include <iostream>

DoubleStack::DoubleStack(int allocation_size) {
	m_size = m_allocation_size = allocation_size;
	m_array = new int(m_size);

	m_i_stack0 = -1;
	m_i_stack1 = m_size / 2 - 1;
}

void DoubleStack::push0(const int& item) {
	if (m_i_stack0 == m_size / 2 - 1) {
		resize();
	}
	m_i_stack0++;
	m_array[m_i_stack0] = item;
}

void DoubleStack::push1(const int& item) {
	if (m_i_stack1 == m_size - 1) {
		resize();
	}
	m_i_stack1++;
	m_array[m_i_stack1] = item;
}

int DoubleStack::pop0() {
	if (m_i_stack0 == -1) throw "pop0";
	return m_array[m_i_stack0--];
}

int DoubleStack::pop1() {
	if (m_i_stack1 == m_size / 2 - 1) throw "pop1";
	return m_array[m_i_stack1--];
}

void DoubleStack::resize() {
	int* new_array = new int(m_size + m_allocation_size);

	for (int i = 0; i <= m_i_stack0; i++) {
		new_array[i] = m_array[i];
	}
	for (int i = m_size / 2; i <= m_i_stack1; i++) {
		new_array[i + m_allocation_size / 2] = m_array[i];
	}
	m_i_stack1 += m_allocation_size / 2;

	m_size += m_allocation_size;

	delete[] m_array;
	m_array = new_array;
}

int main() {
	DoubleStack test = DoubleStack(10);

	for (int i = 0; i < 15; i++) {
		test.push0(i);
		test.push1(100 - i);
	}

	for (int i = 0; i < 15; i++) {
		std::cout << test.pop0() << ' ' << test.pop1() << std::endl;
	}

	return 0;
}

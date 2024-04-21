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
////// Task03
////// =================================================

// # include "ads_excercise01/Deque.hpp"
# include "../include/ads_excercise01/Deque.hpp"
#include <iostream>

void Deque::push_front(const int& item) {
	if (m_head == nullptr) {
		m_head = m_tail = new NodeD();
	} else {
		m_head->prev = new NodeD();

		m_head->prev->next = m_head;
		m_head = m_head->prev;
	}

	m_head->item = item;

	return;
}

int Deque::pop_front() {
	if (m_head == nullptr) throw "Technisch gesehen fordert die aufgabenstellung das hier nicht mal (pop_front)";

	int item = m_head->item;

	if (m_head->next == nullptr) {
		delete m_head;
		m_head = m_tail = nullptr;

		return item;
	}

	m_head = m_head->next;
	delete m_head->prev;
	m_head->prev = nullptr;

	return item;
}

void Deque::push_back(const int& item) {
	if (m_tail == nullptr) {
		m_head = m_tail = new NodeD();
	} else {
		m_tail->next = new NodeD();

		m_tail->next->prev = m_tail;
		m_tail = m_tail->next;
	}

	m_tail->item = item;

	return;
}

int Deque::pop_back() {
	if (m_head == nullptr) throw "Technisch gesehen fordert die aufgabenstellung das hier nicht mal (pop_back)";

	int item = m_tail->item;

	// Handle the deque losing its last entry
	if (m_tail->prev == nullptr) {
		delete m_tail;
		m_tail = m_head = nullptr;

		return item;
	}

	m_tail = m_tail->prev;
	delete m_tail->next;
	m_tail->next = nullptr;

	return item;
}

void Deque::print_all() const {
	std::cout << '[';

	NodeD* ptr = m_head;
	while (ptr != nullptr) {
		// Detect the first element and don't add a comma there
		if (ptr->prev == nullptr) {
			std::cout << ' ';
		} else {
			std::cout << ", ";
		}

		std::cout << ptr->item;

		ptr = ptr->next;
	}

	std::cout << " ]" << std::endl;

	return;
}

int main() {
	// Testing
	Deque test = { 1, 2, 3, 4, 5 };

	test.print_all();
	test.push_back(test.pop_front());
	test.print_all();
	test.push_front(test.pop_back());
	test.print_all();

	return 0;
}

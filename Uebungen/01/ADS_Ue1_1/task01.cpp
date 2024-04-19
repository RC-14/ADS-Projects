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
////// Task01
////// =================================================

// # include "ads_excercise01/ListE.hpp"
// # include "ads_excercise01/ListD.hpp"
# include "../include/ads_excercise01/ListE.hpp"
# include "../include/ads_excercise01/ListD.hpp"

bool ListE::swap(const int& index) {
	// Check that the index is valid and that there's a node after the one the index specifies
	if (index < 0 || index >= m_length - 1) return false;

	NodeE* after;

	if (index == 0) {
		// Edge case for swapping the first element because m_head has to be set

		// Saving a reference to the node after the two nodes we'll swap
		after = m_head->next->next;

		// Swapping the positions
		m_head->next->next = m_head;
		m_head = m_head->next;
		m_head->next->next = after;

		// Setting tail if necessary
		if (m_length == 2) {
			m_tail = m_head->next;
		} else if (m_length == 3) {
			m_tail = after;
		}
	} else {
		// Extra variable because we can't overwrite m_head
		NodeE* before = m_head;

		// Following the liked list to the node before the node at index
		for (int i = 1; i < index; i++) before = before->next;

		// Saving a reference to the node after the two nodes we'll swap
		after = before->next->next->next;

		// Swapping positions
		before->next->next->next = before->next;
		before->next = before->next->next;
		before->next->next->next = after;

		// Setting tail if necessary
		if (index == m_length - 2) {
			m_tail = before->next->next;
		} else if (index == m_length - 3) {
			m_tail = after;
		}
	}

	return true;
}

bool ListD::swap(const int& index) {
	// Check that the index is valid and that there's a node after the one the index specifies
	if (index < 0 || index >= m_length - 1) return false;

	// Following the linked list to the node at index
	NodeD* node = m_head;
	for (int i = 0; i < index; i++) node = node->next;

	// Swapping positions
	if (node->prev != nullptr) node->prev->next = node->next;
	node->next->prev = node->prev;
	node->prev = node->next;
	node->next = node->prev->next;
	node->prev->next = node;
	if (node->next != nullptr) node->next->prev = node;

	// Set m_head and m_tail if necessary
	if (node->prev->prev == nullptr) m_head = node->prev;
	if (node->next == nullptr) m_tail = node;

	return true;
}

int main() {
	//// Example lists for the task

	ListE list_singleLinkedexmpl_init = ListE({ 0,1,2,3,4,5,6,7,8,9 });
	ListD list_doubleLinkedexmpl_init = ListD({ 0,1,2,3,4,5,6,7,8,9 });

	std::cout
		<< list_singleLinkedexmpl_init.swap(-1)
		<< list_singleLinkedexmpl_init.swap(0)
		<< list_singleLinkedexmpl_init.swap(1)
		<< list_singleLinkedexmpl_init.swap(8)
		<< list_singleLinkedexmpl_init.swap(9)
		<< std::endl;
	list_singleLinkedexmpl_init.print();

	std::cout
		<< list_doubleLinkedexmpl_init.swap(-1)
		<< list_doubleLinkedexmpl_init.swap(0)
		<< list_doubleLinkedexmpl_init.swap(1)
		<< list_doubleLinkedexmpl_init.swap(8)
		<< list_doubleLinkedexmpl_init.swap(9)
		<< std::endl;
	list_doubleLinkedexmpl_init.print();

	return 0;

}

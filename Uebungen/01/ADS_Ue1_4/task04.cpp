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
////// Task04
////// =================================================

// # include "ads_excercise01/ListE.hpp"
# include "../include/ads_excercise01/ListE.hpp"

void ListE::print_reversed() const {
	std::cout << '[';
	if (m_head != nullptr) print_reversed_helper(m_head);
	std::cout << " ]" << std::endl;
}

// NOTE: If the algorithm is implemented recursively, the following method should be used as a helper
void ListE::print_reversed_helper(NodeE* node) const {
	if (node->next != nullptr) {
		print_reversed_helper(node->next);
		std::cout << ", ";
	} else {
		std::cout << ' ';
	}
	std::cout << node->item;
}

int main() {
	ListE test = { 1, 2, 3, 4, 5 };

	test.print_reversed();

	return 0;
}

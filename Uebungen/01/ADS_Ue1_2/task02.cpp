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
////// Task02
////// =================================================

# include <iostream>
# include <list>

void print_list(const std::list<int>& l) {
	std::cout << "[";

	bool first = true;
	for (const int& x : l) {
		if (first) {
			first = false;
			std::cout << ' ';
		} else {
			std::cout << ", ";
		}
		std::cout << x;
	}

	std::cout << " ]" << std::endl;
}

std::list<int> union_of_lists(const std::list<int>& l1, const std::list<int>& l2) {
	std::list<int> result_union = l1;

	/*
	 * Using merge()
	 */
	 // std::list<int> tmp = l2;
	 // result_union.merge(tmp);

	 /*
	  * Written "from scratch"
	  */
	std::list<int>::const_iterator l2_it = l2.cbegin();
	for (std::list<int>::const_iterator l1_it = result_union.cbegin(); l1_it != result_union.cend(); l1_it++) {
		// Insert values from l2 into result_union while keeping it sorted
		while (l2_it != l2.cend() && *l1_it > *l2_it) {
			result_union.insert(l1_it, *l2_it);
			l2_it++;
		}

		// Detect if we can exit early
		if (l2_it == l2.cend()) {
			return result_union;
		}
	}

	// Reusing it2 to append the rest to the end
	for (; l2_it != l2.cend(); l2_it++) {
		result_union.push_back(*l2_it);
	}

	return result_union;
}

std::list<int> intersection_of_lists(const std::list<int>& l1, const std::list<int>& l2) {
	std::list<int> result_intersection = {};

	std::list<int>::const_iterator l2_it = l2.cbegin();

	for (const int& l1_item : l1) {
		// Take advantage of the fact that the lists are sorted and skip every entry in l2 that's lower than the current entry of l1
		while (l2_it != l2.cend() && *l2_it < l1_item) {
			l2_it++;
		}
		// Exit early if we reached the end of l2
		if (l2_it == l2.cend()) return result_intersection;

		// Skip the value if the entries aren't equal
		if (l1_item != *l2_it) continue;

		// Check if result_intersection already contains the value
		bool new_val = true;
		for (const int& inter_item : result_intersection) {
			if (inter_item != l1_item) continue;

			new_val = false;
			break;
		}
		// Prevent adding values twice to result_intersection
		if (!new_val) continue;

		result_intersection.push_back(l1_item);
	}

	return result_intersection;
}

int main() {
	// Given example lists from the task describtion
	std::list<int> l1 = { 10, 11, 13, 15, 18, 20, 21 };
	std::list<int> l2 = { 4, 8, 10, 12, 14, 15, 18, 23 };

	std::cout << "l1: ";
	print_list(l1);
	std::cout << "l2: ";
	print_list(l2);

	std::cout << std::endl;

	// Call your implementation of the union_of_lists function and output the list
	std::list<int> list_unionResult = union_of_lists(l1, l2);
	std::cout << "list_unionResult:        ";
	print_list(list_unionResult);

	// Call your implementation of the list_intersectionResult function and output the list
	std::list<int> list_intersectionResult = intersection_of_lists(l1, l2);
	std::cout << "list_intersectionResult: ";
	print_list(list_intersectionResult);

	return 0;
}

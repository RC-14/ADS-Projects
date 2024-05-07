/*************************************************
* ADS Praktikum 1.1
* Ring.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .cpp
#include "Ring.h"
#include <iostream>

void Ring::addNewNode(std::string description, std::string symbolicData) {
	RingNode* newNode = new RingNode(0, description, symbolicData);

	if (m_anker == nullptr) {
		m_anker = newNode;
		m_anker->setNext(m_anker);

		m_countNodes++;

		return;
	}

	RingNode* lastNode = m_anker->getNext();
	m_anker->setNext(newNode);
	m_anker = newNode;

	if (m_countNodes < 6) {
		m_anker->setNext(lastNode);
		m_countNodes++;
	} else {
		m_anker->setNext(lastNode->getNext());
		delete lastNode;
	}

	RingNode* ptr = m_anker->getNext();
	while (ptr != m_anker) {
		ptr->setOldAge(ptr->getOldAge() + 1);

		ptr = ptr->getNext();
	}
}

bool Ring::search(std::string symbolicData) {
	if (m_anker == nullptr) return false;

	RingNode* ptr = m_anker;

	do {
		if (ptr->getSymbolicData() == symbolicData) {
			lastSearchResult = ptr;
			return true;
		}
		ptr = ptr->getNext();
	} while (ptr != m_anker);

	lastSearchResult = nullptr;
	return false;
}

void recPrint(RingNode* ptr, int i, bool first) {
	if (first) {
		std::cout
			<< "Alter: " << ptr->getOldAge() << ", "
			<< "Beschreibung: " << ptr->getDescription() << ", "
			<< "Daten: " << ptr->getSymbolicData()
			<< std::endl;
	}

	if (i > 1) recPrint(ptr->getNext(), i - 1, false);

	if (first) return;

	std::cout << "--------------------------" << std::endl;
	std::cout
		<< "Alter: " << ptr->getOldAge() << ", "
		<< "Beschreibung: " << ptr->getDescription() << ", "
		<< "Daten: " << ptr->getSymbolicData()
		<< std::endl;
}

void Ring::print() {
	if (m_anker == nullptr) return;
	recPrint(m_anker, m_countNodes, true);
}

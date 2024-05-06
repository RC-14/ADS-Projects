/*************************************************
* ADS Praktikum 1.1
* RingNode.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#pragma once
#include <string>

class RingNode {
private:
	int m_oldAge;
	std::string m_description;
	std::string m_symbolicData;
	RingNode* m_next = nullptr;

public:
	RingNode() : m_oldAge{ 0 }, m_description{ "" }, m_symbolicData{ "" } { }
	RingNode(int oldAge, std::string description, std::string symbolicData) : m_oldAge{ oldAge }, m_description{ description }, m_symbolicData{ symbolicData } { }

	int getOldAge() {
		return m_oldAge;
	}

	void setOldAge(int newOldAge) {
		m_oldAge = newOldAge;
	}

	std::string getDescription() {
		return m_description;
	}

	void setDescription(std::string newDescription) {
		m_description = newDescription;
	}

	std::string getSymbolicData() {
		return m_symbolicData;
	}

	void setSymbolicData(std::string newSymbolicData) {
		m_symbolicData = newSymbolicData;
	}

	RingNode* getNext() {
		return m_next;
	}

	void setNext(RingNode* newNext) {
		m_next = newNext;
	}
};

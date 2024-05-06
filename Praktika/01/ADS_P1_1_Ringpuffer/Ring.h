/*************************************************
* ADS Praktikum 1.1
* Ring.h
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
// Ring .h
#pragma once
#include<string>
#include "catch.h"
#include"RingNode.h"

class Ring {
private:
	int m_countNodes = 0;
	RingNode* m_anker = nullptr;

public:
	Ring() {};

	RingNode* lastSearchResult = nullptr;

	void addNewNode(std::string description, std::string symbolicData);
	bool search(std::string symbolicData);
	void print();

	// friend Funktionen müssen unangetastet bleiben! 
	friend RingNode* get_anker(Ring& r);
	friend int get_countNodes(Ring& r);
};

/*************************************************
 * ADS Praktikum 1.2
 * TreeNode.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "TreeNode.h"
#include <iostream>
#include <string>

using namespace std;

TreeNode::TreeNode(int nNodePos, int id, string name, int alter, double einkommen, int plz) {
	this->m_NodeOrderID = nNodePos;
	this->m_NodeChronologicalID = id;
	this->m_Name = name;
	this->m_Age = alter;
	this->m_Income = einkommen;
	this->m_PostCode = plz;
	this->m_red = true;
	this->m_left = nullptr;
	this->m_right = nullptr;
	this->m_parent = nullptr;
}

void TreeNode::print() {
	cout
		<< "NodeID: " << m_NodeChronologicalID << ", "
		<< "Name: " << m_Name << ", "
		<< "Alter: " << m_Age << ", "
		<< "Einkommen: " << m_Income << ", "
		<< "PLZ: " << m_PostCode << ", "
		<< "PosID: " << m_NodeOrderID << ", "
		<< "Red: " << m_red << endl;
};

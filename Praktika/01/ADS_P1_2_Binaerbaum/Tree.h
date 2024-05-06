/*************************************************
 * ADS Praktikum 1.2
 * Tree.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include "TreeNode.h"
#include "catch.h"
#include <string>

using namespace std;

class Tree {
private:
	TreeNode* m_anker;
	int m_currentNodeChronologicalID;

	void printPreOrder();
	void printInOrder();
	void printPostOrder();

public:
	Tree() : m_anker{ nullptr }, m_currentNodeChronologicalID{ 0 } { };
	~Tree();

	void addNode(string name, int age, double income, int postCode);
	bool deleteNode(int id);
	bool searchNode(string name);
	void printAll();
	void levelOrder();

	friend void printPrePostIn(Tree*& binTree);

	// friend-Funktionen sind für die Tests erforderlich und müssen unangetastet
	// bleiben!
	friend TreeNode* get_anker(Tree& TN);
};

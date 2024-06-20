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

	void balance(TreeNode* node);
	bool split4Node(TreeNode* node);
	bool rotateTreeRight(TreeNode* node);
	bool rotateTreeLeft(TreeNode* node);
	// Custom Helper
	void addNodeToTree(TreeNode*& anker, TreeNode*& node);

public:
	Tree() : m_anker{ nullptr }, m_currentNodeChronologicalID{ 0 } { };
	~Tree();

	void addNode(string name, int age, double income, int postCode);
	bool searchNode(string name);
	void printAll();
	int proofRBCriterion(TreeNode* node);
	void printLevelOrder();
	void printLevelOrder(int nivea);

	// friend-Funktionen sind für die Tests erforderlich und müssen unangetastet
	// bleiben!
	friend TreeNode* get_anker(Tree& TN);
};

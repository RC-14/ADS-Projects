/*************************************************
 * ADS Praktikum 1.2
 * TreeNode.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include <string>

using namespace std;

class TreeNode {
private:
	int m_NodeOrderID;
	int m_NodeChronologicalID;
	string m_Name;
	int m_Age;
	double m_Income;
	int m_PostCode;
	TreeNode* m_left;
	TreeNode* m_right;

public:
	TreeNode(int NodeOrderID, int NodeChronologicalID, string Name, int Age, double Income, int PostCode);

	int getNodeOrderID() {
		return m_NodeOrderID;
	}

	void setNodeOrderID(int newNodeOrderID) {
		m_NodeOrderID = newNodeOrderID;
	}

	int getNodeChronologicalID() {
		return m_NodeChronologicalID;
	}

	void setNodeChronologicalID(int newNodeChronologicalID) {
		m_NodeChronologicalID = newNodeChronologicalID;
	}

	string getName() {
		return m_Name;
	}

	void setName(string newName) {
		m_Name = newName;
	}

	int getAge() {
		return m_Age;
	}

	void setAge(int newAge) {
		m_Age = newAge;
	}

	double getIncome() {
		return m_Income;
	}

	void setIncome(double newIncome) {
		m_Income = newIncome;
	}

	int getPostCode() {
		return m_PostCode;
	}

	void setPostCode(int newPostCode) {
		m_PostCode = newPostCode;
	}

	TreeNode* getLeft() {
		return m_left;
	}

	void setLeft(TreeNode* newLeft) {
		m_left = newLeft;
	}

	TreeNode* getRight() {
		return m_right;
	}

	void setRight(TreeNode* newRight) {
		m_right = newRight;
	}

	void print();
};

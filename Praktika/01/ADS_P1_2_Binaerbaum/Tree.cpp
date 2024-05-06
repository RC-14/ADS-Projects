/*************************************************
 * ADS Praktikum 1.2
 * Tree.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iostream>
#include <queue>

using namespace std;

void recDeleteTreeNodes(TreeNode* anker) {
	if (anker->getLeft() != nullptr) recDeleteTreeNodes(anker->getLeft());
	if (anker->getRight() != nullptr) recDeleteTreeNodes(anker->getRight());
	delete anker;
}

Tree::~Tree() {
	if (m_anker != nullptr) recDeleteTreeNodes(m_anker);
}

void addNodeToTree(TreeNode*& anker, TreeNode*& node) {
	if (anker == nullptr) {
		anker = node;
		return;
	}

	TreeNode* ptr = anker;
	while (true) {
		if (ptr->getNodeOrderID() == node->getNodeOrderID()) return;

		if (ptr->getNodeOrderID() > node->getNodeOrderID()) {
			if (ptr->getLeft() == nullptr) {
				ptr->setLeft(node);
				return;
			}

			ptr = ptr->getLeft();
			continue;
		}

		if (ptr->getRight() == nullptr) {
			ptr->setRight(node);
			return;
		}
		ptr = ptr->getRight();
	}
}

void Tree::addNode(string name, int age, double income, int postCode) {
	TreeNode* node = new TreeNode(age + income + postCode, m_currentNodeChronologicalID++, name, age, income, postCode);
	addNodeToTree(m_anker, node);
}

bool Tree::deleteNode(int id) {
	TreeNode* leftChild = nullptr;
	TreeNode* rightChild = nullptr;

	if (m_anker->getNodeOrderID() == id) {
		leftChild = m_anker->getLeft();
		rightChild = m_anker->getRight();

		delete m_anker;

		if (leftChild == nullptr || rightChild == nullptr) {
			if (rightChild == nullptr) {
				m_anker = leftChild;
			} else {
				m_anker = rightChild;
			}
			return true;
		}

		m_anker = nullptr;
	} else {
		TreeNode* ptr = m_anker;
		bool right = false;

		while (true) {
			if (ptr->getNodeOrderID() > id) {
				if (ptr->getLeft() == nullptr) return false;
				if (ptr->getLeft()->getNodeOrderID() == id) {
					right = false;
					break;
				}
				ptr = ptr->getLeft();
				continue;
			}

			if (ptr->getRight() == nullptr) return false;
			if (ptr->getRight()->getNodeOrderID() == id) {
				right = true;
				break;
			}
			ptr = ptr->getRight();
		}

		if (right) {
			leftChild = ptr->getRight()->getLeft();
			rightChild = ptr->getRight()->getRight();

			delete ptr->getRight();

			if (leftChild == nullptr || rightChild == nullptr) {
				if (rightChild == nullptr) {
					ptr->setRight(leftChild);
				} else {
					ptr->setRight(rightChild);
				}
				return true;
			}

			ptr->setRight(nullptr);
		} else {
			leftChild = ptr->getLeft()->getLeft();
			rightChild = ptr->getLeft()->getRight();

			delete ptr->getLeft();

			if (leftChild == nullptr || rightChild == nullptr) {
				if (rightChild == nullptr) {
					ptr->setLeft(leftChild);
				} else {
					ptr->setLeft(rightChild);
				}
				return true;
			}

			ptr->setLeft(nullptr);
		}
	}

	if (rightChild->getLeft() == nullptr) {
		rightChild->setLeft(leftChild);
		addNodeToTree(m_anker, rightChild);
		return true;
	}

	TreeNode* almostRightMinimum = rightChild;

	while (almostRightMinimum->getLeft()->getLeft() != nullptr) almostRightMinimum = almostRightMinimum->getLeft();

	TreeNode* rightMinimum = almostRightMinimum->getLeft();
	almostRightMinimum->setLeft(rightMinimum->getRight());

	rightMinimum->setLeft(leftChild);
	rightMinimum->setRight(rightChild);
	addNodeToTree(m_anker, rightMinimum);
	return true;
}

bool recNodeSearcher(TreeNode* node, string name) {
	if (node == nullptr) return false;

	bool result = node->getName() == name;
	if (result) node->print();

	bool resultLeft = recNodeSearcher(node->getLeft(), name);
	bool resultRight = recNodeSearcher(node->getRight(), name);

	return result || resultLeft || resultRight;
}

bool Tree::searchNode(string name) {
	return recNodeSearcher(m_anker, name);
}

void printPreInPostOrderTableHead() {
	cout
		<< "       ID       |     Name     | Age |   Income   |   PostCode   |   OrderID" << endl
		<< "----------------+--------------+-----+------------+--------------+-------------" << endl;
}

void printRightAligned(string text, int space) {
	for (; space > text.length(); space--) {
		cout << " ";
	}
	cout << text;
}

void printNodeHelper(TreeNode* node) {
	cout << " ";
	printRightAligned(to_string(node->getNodeOrderID()), 14);
	cout << " | ";
	printRightAligned(node->getName(), 12);
	cout << " | ";
	printRightAligned(to_string(node->getAge()), 3);
	cout << " | ";
	printRightAligned(to_string(int(node->getIncome())), 10);
	cout << " | ";
	printRightAligned(to_string(node->getPostCode()), 12);
	cout << " | ";
	printRightAligned(to_string(node->getNodeOrderID()), 11);
}

void Tree::levelOrder() {
	cout
		<< "       ID       |     Name     | Age |   Income   |   PostCode   |   OrderID   | Level" << endl
		<< "----------------+--------------+-----+------------+--------------+-------------+-------" << endl;

	if (m_anker == nullptr) return;

	queue<TreeNode*> q;
	q.push(m_anker);

	unsigned level = 0;
	unsigned nNextLevel = 0;
	unsigned n = 1;

	while (!q.empty()) {
		TreeNode* node = q.front();
		q.pop();

		printNodeHelper(node);
		cout << " | ";
		printRightAligned(to_string(level), 5);
		cout << endl;

		if (node->getLeft() != nullptr) {
			q.push(node->getLeft());
			nNextLevel++;
		}
		if (node->getRight() != nullptr) {
			q.push(node->getRight());
			nNextLevel++;
		}

		if (--n == 0) {
			n = nNextLevel;
			nNextLevel = 0;
			level++;
		}
	}
}

void recPreOrderHelper(TreeNode* node) {
	printNodeHelper(node);
	cout << endl;

	if (node->getLeft() != nullptr) recPreOrderHelper(node->getLeft());
	if (node->getRight() != nullptr) recPreOrderHelper(node->getRight());
}

void Tree::printPreOrder() {
	printPreInPostOrderTableHead();

	if (m_anker != nullptr) recPreOrderHelper(m_anker);
}

void recInOrderHelper(TreeNode* node) {
	if (node->getLeft() != nullptr) recPreOrderHelper(node->getLeft());

	printNodeHelper(node);
	cout << endl;

	if (node->getRight() != nullptr) recPreOrderHelper(node->getRight());
}

void Tree::printInOrder() {
	printPreInPostOrderTableHead();

	if (m_anker != nullptr) recInOrderHelper(m_anker);
}

void recPostOrderHelper(TreeNode* node) {
	if (node->getLeft() != nullptr) recPreOrderHelper(node->getLeft());
	if (node->getRight() != nullptr) recPreOrderHelper(node->getRight());

	printNodeHelper(node);
	cout << endl;
}

void Tree::printPostOrder() {
	printPreInPostOrderTableHead();

	if (m_anker != nullptr) recPostOrderHelper(m_anker);
}

void Tree::printAll() {
	levelOrder();
	printPreOrder();
	printInOrder();
	printPostOrder();
}

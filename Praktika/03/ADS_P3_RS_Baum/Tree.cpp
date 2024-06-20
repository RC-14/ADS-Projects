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

int proofRBCriterionBottomUpHelper(TreeNode* node) {
	if (node == nullptr) throw;

	// L==null && R==null
	if (node->getLeft() == nullptr && node->getRight() == nullptr) {
		return 0;
	}

	// L==null || R==null
	if (node->getLeft() == nullptr) {
		if (node->getRight()->getRed()) {
			return proofRBCriterionBottomUpHelper(node->getRight());
		}
		int result = proofRBCriterionBottomUpHelper(node->getRight());
		if (result == -1) return -1;
		return result + 1;
	} else if (node->getRight() == nullptr) {
		if (node->getLeft()->getRed()) {
			return proofRBCriterionBottomUpHelper(node->getLeft());
		}
		int result = proofRBCriterionBottomUpHelper(node->getLeft());
		if (result == -1) return -1;
		return result;
	}

	// L->red && R->red
	if (node->getLeft()->getRed() && node->getRight()->getRed()) {
		int l = proofRBCriterionBottomUpHelper(node->getLeft());
		if (l == -1) return -1;

		int r = proofRBCriterionBottomUpHelper(node->getRight());
		if (r == -1) return -1;

		if (l != r) return -1;
		return l;
	}

	// L->red && !R->red || !L->red && R->red
	if (node->getLeft()->getRed() && !node->getRight()->getRed()) {
		int l = proofRBCriterionBottomUpHelper(node->getLeft());
		if (l == -1) return -1;

		int r = proofRBCriterionBottomUpHelper(node->getRight());
		if (r == -1) return -1;

		if (l + 1 != r) return -1;
		return l;
	} else if (!node->getLeft()->getRed() && node->getRight()->getRed()) {
		int l = proofRBCriterionBottomUpHelper(node->getLeft());
		if (l == -1) return -1;

		int r = proofRBCriterionBottomUpHelper(node->getRight());
		if (r == -1) return -1;

		if (l + 1 != r) return -1;
		return l;
	}

	// !L->red && !R->red
	int l = proofRBCriterionBottomUpHelper(node->getLeft());
	if (l == -1) return -1;

	int r = proofRBCriterionBottomUpHelper(node->getRight());
	if (r == -1) return -1;

	if (l != r) return -1;
	return l + 1;
}

int Tree::proofRBCriterion(TreeNode* node) {
	return proofRBCriterionBottomUpHelper(node);
}

bool Tree::split4Node(TreeNode* node) {
	if (node == m_anker) return false;
	if (node->getRed()) return false;

	TreeNode* left = node->getLeft();
	if (left == nullptr || !left->getRed()) return false;

	TreeNode* right = node->getRight();
	if (right == nullptr || !right->getRed()) return false;

	node->setRed(true);
	left->setRed(false);
	right->setRed(false);

	return true;
}

bool Tree::rotateTreeRight(TreeNode* node) {
	if (node->getParent() == nullptr) return false;
	if (node != node->getParent()->getLeft()) throw;

	cout << "LR(" << node->getNodeOrderID() << ',' << node->getParent()->getNodeOrderID() << ")" << endl;

	node->getParent()->setLeft(node->getRight());
	if (node->getParent()->getLeft() != nullptr) {
		node->getParent()->getLeft()->setParent(node->getParent());
	}
	node->setRight(node->getParent());
	node->setParent(node->getParent()->getParent());
	if (node->getParent() == nullptr) {
		m_anker = node;
	} else if (node->getParent()->getLeft() == node->getRight()) {
		node->getParent()->setLeft(node);
	} else {
		node->getParent()->setRight(node);
	}
	node->getRight()->setParent(node);

	return true;
}

bool Tree::rotateTreeLeft(TreeNode* node) {
	if (node->getParent() == nullptr) return false;
	if (node != node->getParent()->getRight()) throw;

	cout << "LR(" << node->getNodeOrderID() << ',' << node->getParent()->getNodeOrderID() << ")" << endl;

	node->getParent()->setRight(node->getLeft());
	if (node->getParent()->getRight() != nullptr) {
		node->getParent()->getRight()->setParent(node->getParent());
	}
	node->setLeft(node->getParent());
	node->setParent(node->getParent()->getParent());
	if (node->getParent() == nullptr) {
		m_anker = node;
	} else if (node->getParent()->getLeft() == node->getLeft()) {
		node->getParent()->setLeft(node);
	} else {
		node->getParent()->setRight(node);
	}
	node->getLeft()->setParent(node);

	return true;
}

void Tree::balance(TreeNode* node) {
	if (!node->getRed()) return;
	if (node->getParent() == nullptr) return;
	if (!node->getParent()->getRed()) return;

	if (node->getParent()->getLeft() == node) {
		if (node->getParent()->getParent()->getRight() == node->getParent()) {
			rotateTreeRight(node);
			rotateTreeLeft(node);
			node->setRed(false);
			node->getRight()->setRed(false);
		} else {
			rotateTreeRight(node->getParent());
			node->setRed(false);
			node->getParent()->setRed(false);
		}
	} else {
		if (node->getParent()->getParent()->getLeft() == node->getParent()) {
			rotateTreeLeft(node);
			rotateTreeRight(node);
			node->setRed(false);
			node->getLeft()->setRed(false);
		} else {
			rotateTreeLeft(node->getParent());
			node->setRed(false);
			node->getParent()->setRed(false);
		}
	}
}

void Tree::addNode(string name, int age, double income, int postCode) {
	int nodeOrderID = age + income + postCode;

	if (m_anker == nullptr) {
		m_anker = new TreeNode(nodeOrderID, m_currentNodeChronologicalID++, name, age, income, postCode);
		m_anker->setRed(false);
		return;
	}

	TreeNode* ptr = m_anker;
	while (true) {
		split4Node(ptr);

		if (ptr->getNodeOrderID() == nodeOrderID) {
			return;
		}

		if (ptr->getNodeOrderID() > nodeOrderID) {
			if (ptr->getLeft() == nullptr) {
				ptr->setLeft(new TreeNode(nodeOrderID, m_currentNodeChronologicalID++, name, age, income, postCode));
				ptr->getLeft()->setParent(ptr);
				ptr = ptr->getLeft();
				break;
			}

			ptr = ptr->getLeft();
			continue;
		}

		if (ptr->getRight() == nullptr) {
			ptr->setRight(new TreeNode(nodeOrderID, m_currentNodeChronologicalID++, name, age, income, postCode));
			ptr->getRight()->setParent(ptr);
			ptr = ptr->getRight();
			break;
		}
		ptr = ptr->getRight();
	}

	while (ptr != nullptr) {
		balance(ptr);
		ptr = ptr->getParent();
	}
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

void printTableHead() {
	cout
		<< "       ID       |     Name     | Age |   Income   |   PostCode   |   OrderID   | Red" << endl
		<< "----------------+--------------+-----+------------+--------------+-------------+----" << endl;
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
	cout << " | ";
	printRightAligned(to_string(node->getRed()), 3);
}

void Tree::printAll() {
	printTableHead();

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

void recPrintLevelOrderNiveauHelper(int niveau, TreeNode* node) {
	if (niveau > 0) {
		if (!node->getRed()) niveau--;

		if (node->getLeft() != nullptr) recPrintLevelOrderNiveauHelper(niveau, node->getLeft());
		if (node->getRight() != nullptr) recPrintLevelOrderNiveauHelper(niveau, node->getRight());

		return;
	}

	cout << " (";
	if (node->getLeft() != nullptr && node->getLeft()->getRed()) cout << node->getLeft()->getNodeOrderID() << ", ";
	cout << node->getNodeOrderID();
	if (node->getRight() != nullptr && node->getRight()->getRed()) cout << ", " << node->getRight()->getNodeOrderID();
	cout << ")";
}

void Tree::printLevelOrder(int niveau) {
	cout << "Niv. " << niveau << ':';
	recPrintLevelOrderNiveauHelper(niveau, m_anker);
	cout << endl;
}

int recGetBlackDepth(TreeNode* node) {
	if (node == nullptr) return 0;

	int l = recGetBlackDepth(node->getLeft());
	int r = recGetBlackDepth(node->getRight());

	if (node->getRed()) {
		if (l > r) return l;
		return r;
	}

	if (l > r) return l + 1;
	return r + 1;
}

void Tree::printLevelOrder() {
	if (m_anker == nullptr) return;

	int h = recGetBlackDepth(m_anker);
	if (h == -1) throw;

	for (int i = 0; i < h; i++) {
		printLevelOrder(i);
	}
}

#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size, double threshold, int methode) {
	hashTable = new vector<int>(size, -1);

	this->size = size;
	m_sondierMethode = methode;
	threshold_rehashing = threshold;
}

HashTable::~HashTable() {
	delete hashTable;
}

int get_next_prime(int x) {
	x = x + 1;
	bool found = true;
	while (true) {
		found = true;
		for (int i = 2; i <= sqrt(x); i++) {
			if (x % i == 0) {
				found = false;
				break;
			}
		}
		if (found) {
			return x;
		}
		x += 1;
	}
}

int get_last_prime(int x) {
	x = x - 1;
	bool found = true;
	while (true) {
		found = true;
		for (int i = 2; i <= sqrt(x); i++) {
			if (x % i == 0) {
				found = false;
				break;
			}
		}
		if (found) {
			return x;
		}
		x -= 1;
	}
}

// Berechnung des Hashwertes 
int HashTable::hashValue(int item) {
	int hash = 0;
	int i = 0;

	switch (m_sondierMethode) {
	case (1):
		// Lineares Sondieren
		hash = (item + i) % size;

		while ((*hashTable)[hash] != -1) {
			i++;
			collisionCount++;
			hash = (item + i) % size;
		}
		return hash;

	case (2):
		// Quadr. Sondieren
		hash = (item + i * i) % size;

		while ((*hashTable)[hash] != -1) {
			i++;
			collisionCount++;
			hash = (item + i * i) % size;
		}
		return hash;

	case (3):
		// Doppeltes Hashing
		int R = get_last_prime(size);
		hash = (item + i * (R - item % R)) % size;

		while ((*hashTable)[hash] != -1) {
			i++;
			collisionCount++;
			hash = (item + i * (R - item % R)) % size;
		}
		return hash;
	}
	return 1;
}

void HashTable::rehashing() {
	vector<int>* oldHashTable = hashTable;

	collisionCount = 0;
	elements = 0;
	size = get_next_prime(2 * size);
	hashTable = new vector<int>(size, -1);

	for (int i = 0; i < oldHashTable->size(); i++) {
		if (oldHashTable->at(i) == -1) continue;
		insert(oldHashTable->at(i));
	}

	delete oldHashTable;
}

int HashTable::insert(int item) {
	if (double(elements + 1) / double(size) >= threshold_rehashing) {
		rehashing();
	}
	int index = hashValue(item);
	(*hashTable)[index] = item;
	elements++;
	return index;
}

int HashTable::at(int i) {
	return hashTable->at(i);
}

int HashTable::getCollisionCount() {
	return this->collisionCount;
}

int HashTable::getSize() {
	return this->size;
}

int HashTable::getElements() {
	return this->elements;
}

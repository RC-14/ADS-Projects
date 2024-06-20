#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include <iostream>
#include"hashtable.h"

using namespace std;

int main() {
	Catch::Session().run();

	HashTable t(1000);

	for (int i = 0; i < 200; i++) {
		int v = 1000 + rand() % 500;
		t.insert(v);
	}

	cout << endl << "Collisions: " << t.getCollisionCount() << endl;

	return 0;
}

/*************************************************
* ADS Praktikum 1.1
* main.cpp
*
*************************************************/
#define CATCH_CONFIG_RUNNER

#include <iostream>
#include <string>
#include "Ring.h"
#include "catch.h"

using namespace std;

void print_menu() {
	cout << "====================================" << endl
		<< " SuperBackUp-Organizer over 9000, by. Son Goku" << endl
		<< "====================================" << endl
		<< "1) Backup anlegen" << endl
		<< "2) Backup suchen" << endl
		<< "3) Alle Backups ausgeben" << endl
		<< "4) Programm beenden" << endl
		<< "?> ";
}

void create(Ring& backupRing) {
	cout << "+Neuen Datensatz anlegen" << endl;

	string description, data;

	cout << "Beschreibung ?> ";
	getline(cin, description);
	cout << "Daten ?> ";
	getline(cin, data);

	backupRing.addNewNode(description, data);

	cout << "+Ihr Datensatz wurde hinzugefuegt.";
}

void search(Ring& backupRing) {
	cout << "+Nach welchen Daten soll gesucht werden?" << endl;
	cout << "?> " << endl;

	string daten;
	getline(cin, daten);

	if (!backupRing.search(daten)) {
		cout << "+ Nicht gefunden." << endl;
		return;
	}

	cout << "+ Gefunden in Backup: "
		<< "Alter: " << backupRing.lastSearchResult->getOldAge() << ", "
		<< "Beschreibung: " << backupRing.lastSearchResult->getDescription() << ", "
		<< "Daten: " << backupRing.lastSearchResult->getSymbolicData()
		<< endl;
}

int main() {
	int result = Catch::Session().run();

	Ring backupRing = Ring();

	int choice = 0;
	while (choice != 4) {
		print_menu();
		cin >> choice;
		cin.ignore();

		switch (choice) {
		case 1:
			create(backupRing);
			break;

		case 2:
			search(backupRing);
			break;

		case 3:
			backupRing.print();
			break;

		case 4:
			cout << "Tschüss" << endl;
			break;

		default:
			cout << "Nicht existente Option." << endl;
			break;
		}
	}

	return result;
}

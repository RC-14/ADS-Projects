/*************************************************
 * ADS Praktikum 1.2
 * main.cpp
 *
 *************************************************/
#define CATCH_CONFIG_RUNNER
#include "Tree.h"
#include "catch.h"
#include <iostream>

using namespace std;

///////////////////////////////////////
// Hilfsmethoden fürs Menü hier:

/***************************
 ** Vorgegebene  Funktion **
 ***************************
   "mainscreen_addTreeCSV"

Importiert CSV Datei in bestehenden Baum.
Bei Aufruf in der main() Methode, muss der Pointer auf den Anker des Baums, als Parameter übergeben werden.
Es wird die im gleichen Verzeichnis liegende Datei "ExportZielanalyse.csv" geladen.
****************************/

void mainscreen_addTreeCSV(Tree*& ref) {
	char j;
	cout << "+ Moechten Sie die Daten aus der Datei ExportZielanalyse.csv "
		"importieren(j / n) ? >";
	cin >> j;
	if (j == 'j') {
		ifstream csvread;
		csvread.open("ExportZielanalyse.csv", ios::in);
		if (!csvread.is_open()) {
			cout << "Fehler beim Lesen!" << endl;
			return;
		} else {
			string name, age, postcode, income;

			while (!csvread.eof()) {
				getline(csvread, name, ';');
				getline(csvread, age, ';');
				getline(csvread, income, ';');
				getline(csvread, postcode, '\n');
				ref->addNode(name, stoi(age), stod(income), stoi(postcode));
			}
			csvread.close();
		}
		cout << "+ Daten wurden dem Baum hinzugefuegt." << endl;
	}
}

//
///////////////////////////////////////

void print_menu() {
	cout
		<< "=========================================" << endl
		<< "     ADS BinTree Interface by F.T.W.     " << endl
		<< "=========================================" << endl
		<< "1) Datensatz einfuegen, manuell" << endl
		<< "2) Datensatz einfuegen, CSV Datei" << endl
		<< "3) Datensatz loeschen" << endl
		<< "4) Suchen" << endl
		<< "5) Datenstruktur anzeigen (pre/post/in)" << endl
		<< "6) Level-Order Ausgabe" << endl
		<< "7) Beenden" << endl
		<< "?> ";
}

void add(Tree*& binTree) {
	cout << "+ Bitte geben Sie die den Datensatz ein:" << endl;

	string name;
	int age, postCode;
	double income;

	cout << " Name ?> ";
	getline(cin, name);

	cout << " Alter ?> ";
	cin >> age;

	cout << " Einkommen ?> ";
	cin >> income;

	cout << " PLZ ?> ";
	cin >> postCode;

	binTree->addNode(name, age, income, postCode);

	cout << endl;
}

void del(Tree*& binTree) {
	cout << "+ Bitte geben Sie den zu loeschenden Datensatz an" << endl;

	int id;
	cout << " NodeOrderID ?> ";
	cin >> id;

	bool result = binTree->deleteNode(id);

	cout << "+ Eintrag wurde";
	if (!result) cout << " nicht";
	cout << " gelöscht." << endl;

	cout << endl;
}

void search(Tree*& binTree) {
	cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << endl;

	string name;
	cout << " Name ?> ";
	getline(cin, name);

	cout << "+ Fundstellen:" << endl;
	binTree->searchNode(name);

	cout << endl;
}

void printPrePostIn(Tree*& binTree) {
	string method;
	cout << " Ausgabereihenfolge ?>";
	getline(cin, method);

	if (method == "pre") {
		binTree->printPreOrder();
	} else if (method == "post") {
		binTree->printPostOrder();
	} else if (method == "in") {
		binTree->printInOrder();
	} else {
		cout << "+ Unbekannte Ausgabemethode." << endl;
	}

	cout << endl;
}

int main() {
	int result = Catch::Session().run();

	Tree* binTree = new Tree();

	int choice = 0;
	while (choice != 7) {
		print_menu();
		cin >> choice;
		cin.ignore();

		switch (choice) {
		case 1:
			add(binTree);
			break;

		case 2:
			mainscreen_addTreeCSV(binTree);
			break;

		case 3:
			del(binTree);
			break;

		case 4:
			search(binTree);
			break;

		case 5:
			printPrePostIn(binTree);
			break;

		case 6:
			binTree->levelOrder();
			cout << endl;
			break;

		case 7:
			cout << "Tschüss" << endl;
			break;

		default:
			cout << "Nicht existente Option." << endl;
			break;
		}
	}


	return result;
}

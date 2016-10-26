#include <iostream>
#include <string>
#include <stack>
#include "Tree.h"
using namespace std;


int menu() {
	int komanda;

	// ispis menija
	cout << "[0] Izlaz iz programa" << endl;
	cout << "[1] Ispis stabla" << endl;
	cout << "[2] Pretraga stabla" << endl;
	cout << "[3] Umetanje kljuca" << endl;
	cout << "[4] Brisanje kljuca" << endl;
	cout << "[5] AVL kriterijum cvora" << endl;

	cout << "Komanda: ";
	cin >> komanda;
	cout << endl;

	return komanda;
}

int main() {
	int koren, komanda;
	
	// Inicijalizacija stabla
	cout << "Unesite koren stabla: ";
	cin >> koren;
	cout << endl;
	Tree t(koren); // inicijalizacija stabla

	// ispis menija 
	komanda = menu();
	

	while (komanda != 0) {

		// upravljanje komandom
		switch (komanda)
		{
		default: case 1: // ispis stabla
			t.ispis();
			break;
		case 2: // pretraga stabla
			cout << endl << "Uneti trazeni kljuc: ";
			cin >> koren;
			cout << endl;
			t.pretraga(koren, true);
			break;
		case 3:  // unos kljuca
			cout << endl << "Uneti kljuc za unos: ";
			cin >> koren;
			t.unos(koren).ispis();
			break;
		case 4: // brisanje kljuca
			cout << endl << "Uneti kljuc za brisanje: ";
			cin >> koren;
			t.brisanje(t.pretraga(koren), true).ispis();
			break;
		case 5: // AVL kriterijum
			cout << endl << "Uneti kljuc za AVL kriterijum: ";
			cin >> koren;
			t.pretraga(koren)->avlBalance(true);
			break;
		}

		komanda = menu();
	}
}

#pragma once 
#include <iostream>
#include <stack>
#include <string>
#include "Node.h"
using namespace std;

class Tree {
	Node *root;
	// vraca minimum
	Node * minimum(Node * curr)  const {
		if (curr == nullptr) return nullptr; // vraca null ako smo postavili da pretrazujemo od nullptr
		if (curr->getLeft() == nullptr && curr->getRight() == nullptr) return curr;

		while (!curr->getLeft()->isLimit()) // dok sledeci levi nije granicnik
			curr = curr->getLeft();

		return curr;
	}

	// vraca roditelja
	Node * roditelj(Node *needle) const {
		if (needle == nullptr || needle == root || needle->isLimit()) return nullptr; // vraca null ako je nullptr ili ako je koren
		Node * pre = nullptr, *temp = root; // pretrhodnik svake iteracije

		while (temp != needle) { // sve dok ga nismo pronasli
			pre = temp;

			if (needle->val() < temp->val())
				temp = temp->getLeft();
			else
				temp = temp->getRight();
		}

		return pre;
	}
	// sledbenik




public:

	Tree() {
		root = new Node(); // vraca pokazivac na cvor granicnik
	}
	Tree(int startVal) {
		root = new Node(startVal); // vraca pokazivac na aociran cvor
	}
	Tree(Node *r) { // konstruktor na osnovu cvora
		root = r;
	}
	Tree(const Tree& copy) { // kopirajuci konstruktor samo kopira adresu
		root = copy.root;
	}

	// ispis tree-a
	Tree ispis() const {


		// u steku cuvamo cvorove koji ce tek biti poseceni
		stack<Node *> stck;
		stack<int> level; // cuvamo levele na stack
		int lvl = 0;
		Node *node = root;

		// prvi posecen je levi
		while ( !node->isLimit() ) {
			stck.push(node);
			node = node->getLeft();
		}

		// prolazak kroz stablo
		while (!stck.empty()) {

			// skidanje sa vrha steka
			node = stck.top();
			stck.pop();


			
			for (int i = 0; i < node->depth(); i++)
				cout << "\t";
			cout << node->val() << endl;

			if (!node->getRight()->isLimit()) {
				node = node->getRight();

				// sledeci posecen cvor ce biti najlevlji
				while (!node->isLimit()) {
					stck.push(node);
					node = node->getLeft();
				}
			}
		}


		return *this;
	} // kraj ispisa

	// unos
	Tree unos(int vrednost, bool showMsg = false) {
		Node *curr = root, *pre = nullptr,
			*newLeft = new Node(), // novi levi granicnik
			*newRight = new Node(); // novi desni granicnik

		if (curr != nullptr) {
			// prolazimo kroz stablo
			while (!curr->isLimit()) {
				pre = curr;
				if (vrednost < curr->val()) {
					curr = curr->getLeft();
				}
				else {
					curr = curr->getRight();
				}
			}
		}
		else { // curr je nullptr
			root = new Node(vrednost);
		}
		// podesavamo novi element
		curr->setVal(vrednost);
		curr->setLeft(newLeft); // novi granicnik
		curr->setRight(newRight); // novi desni granicnik

		if (showMsg) cout << "Unet je kljuc " << vrednost << endl;

		return *this;
	}

	// pretrazuje  stablo
	Node * pretraga(int key, bool showMessage = false) const {
		Node *curr = root;

		while (!curr->isLimit()) {
			// provera manje
			if (key < curr->val()) {
				curr = curr->getLeft();
			}
			else if (key == curr->val()) {
				if (showMessage)cout << "Pronasli smo cvor sa vrednoscu: " << key << endl;
				return curr;
			}
			else {
				curr = curr->getRight();
			}
		}

		if (curr->isLimit()) cout << "Nismo pronasli cvor sa vrednosti " << key << endl;
		return curr;

	}

	// Vraca cvor sledbenika, nullptr ako nema sledbenika
	Node * sledbenik(Node * curr, bool showMsg = false) const {
		if (curr == nullptr || curr->isLimit()) return nullptr;
		Node * p = curr;

		if (p->getRight() != nullptr) {
			Node * q = minimum(p->getRight());

			if (showMsg && q != nullptr) cout << "Sledbenik cvora [" << curr->val() << "] je cvor [" << q->val() << "] " << endl;
			return q;
		}

		// q je pocetni roditelj
		Node * q = roditelj(p);

		while (q != nullptr && p == q->getRight()) { // sve dok nije p desni sin q-a penjemo se
			p = q;
			q = roditelj(q);
		}
		if (showMsg && q != nullptr) cout << "Sledbenik cvora [" << curr->val() << "] je cvor [" << q->val() << "] " << endl;
		return q;


	} // end sledbenik

	// brisanje
	Tree brisanje(Node * needle, bool showMsg = false) {
		if (needle == nullptr || needle->isLimit()) return nullptr;

		Node * parent = roditelj(needle), // Nalazimo roditelja
			*ancestor = sledbenik(needle),
			*parsled = roditelj(ancestor); // roditelj sledbenika
		const int vrednost = needle->val();

		// ako nije koren
		if (needle != root) {
			// ako nema ni levo ni desno pod stablo
			if (needle->noTree()) {

				needle->makeLimit();
			}
			// ako ima samo desno podstablo
			else if (needle->onlyRightTree()) {


				// ako je roditelj sledbenika trazeni samo prevezujemo jer sledbenik nema desno podstablo 
				if (parsled == needle) {
					if (parent->getLeft() == needle) // ako je levi sin
						parent->setLeft(ancestor);
					else if (parent->getRight() == needle) // ako je desni sin
						parent->setRight(ancestor);


					delete needle;
				}
				// u ostalim slucajevima  proveravamo da li sledbenik ima desno podstablo
				else {

					// ako sledbenik ima desno podstablo prevezujeo ga na njegovog roditelja
					if (ancestor->getRight() != nullptr) {
						parsled->setLeft(ancestor->getRight());
					}

					needle->setVal(ancestor->val()); // samo prepisujemo vrednsot sledbenika u trazeni cvor

					delete ancestor; // brisemo sledbenika jer smo mu premestili val	
				}
			}
			// ako ima samo levo podstablo
			else if (needle->onlyLeftTree()) {


				// ako nema sledbenika
				if (parent->getRight() == needle) {
					parent->setRight(needle->getLeft());
				}
				else if (parent->getLeft() == needle) {
					parent->setLeft(needle->getLeft());
				}

				delete needle;
			}
			// ako ima oba stabla
			else if (needle->bothTree()) {

				// menjamo vrednosti 
				needle->setVal(ancestor->val());

				if (!ancestor->getRight()->isLimit()) // ako sledbenik ima desno podstablo prevezujemo
					needle->setRight(ancestor->getRight());
				else
					needle->setRight(new Node());

				delete ancestor;
			}

		}
		else { // ako jeste koren
			   // ako nema desno podstablo
			if (!needle->getRight()->isLimit()) {

				root->setVal(ancestor->val()); // prepisujemo vrednost

				if (!ancestor->getRight()->isLimit()) { // ako sledbenik ima desno 
					// prevezujemo ga na roditelja njegovog
					if (parsled->getLeft() == ancestor)
						parsled->setLeft(ancestor->getRight());
					else if (parsled->getRight() == ancestor)
						parsled->setRight(ancestor->getRight());
				}
				else { // ako nema desnog podstabla brisemo

					// od levog ili desnog sina pravimo granicni
					if (parsled->getLeft() == ancestor) parsled->getLeft()->makeLimit();
					else if (parsled->getRight() == ancestor) parsled->getRight()->makeLimit();
				}

			}
			else { // ako nema desno podstablo
				root = needle->getLeft();
				delete needle;

			}
		} // end ako jeste koren
		if (showMsg) cout << "Uklonili smo cvor [" << vrednost << "] " << endl;
		return *this;
	}

};
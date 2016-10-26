#pragma once
#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Node {
	Node *left, *right;
	int value;


	void setLimit() {
		value = 0;
		left = nullptr;
		right = nullptr;
	}

	// uklanja granicnike cvora
	Node * removeLimits() {

		if (getLeft()->isLimit()) delete getLeft();
		if (getRight()->isLimit()) delete getRight();

		return this;
	}

public:
	Node() { // default konstruktor na cvor granicnik
		setLimit();
	}
	Node(int val, Node* l = nullptr, Node* r = nullptr) {
		Node * newLeft = new Node(), * newRight = new Node();
		value = val;
		left = newLeft;
		right = newRight;
	}
	~Node() {
		removeLimits();
	}

	// vrati vrednost
	int val() const {
		return value;
	}
	// postavi vrednost
	void setVal(int v) {
		value = v;
	}
	// postavi oba
	void setBoth(Node *l, Node *r) {
		left = l;
		right = r;
	}
	// postavi levo
	void setLeft(Node *l) {
		left = l;
	}
	// postavi desno
	void setRight(Node *r) {
		right = r;
	}
	// pokazivac na levo
	Node * getLeft() const {
		if (left)
			return left;
		return nullptr;
	}
	// pokazivac na desno
	Node * getRight() const {
		if (right)
			return right;
		return nullptr;
	}
	// iskljucivo desno stablo
	bool onlyRightTree() {
		if (left->isLimit() &&  !right->isLimit() )
			return true;
		return false;
	}
	// ima iskljucivo levo stablo
	bool onlyLeftTree() {
		if (left != nullptr && right == nullptr)
			return true;
		return false;
	}
	// ima iskljucivo oba stabla
	bool bothTree() {
		if (left != nullptr && right != nullptr)
			return true;
		return false;
	}
	// nema podstabala
	bool noTree() {
		if (left->isLimit() && right->isLimit() )
			return true;
		return false;
	}

	// da li je cvor granicnik
	bool isLimit() {
		if (this != nullptr && left == nullptr && right == nullptr && value == 0)
			return true;
		return false;
	}
	// uklanja sve granicnike
	Node * makeLimit() {
		// brisemo sledbenike granicnike ako postoje
		removeLimits();
		// postavljamo trenutni kao granicnika
		setLimit();
		return this;
	}

	// depth
	int depth(bool showMsg = false) {
		stack<Node *> nodes;
		stack<int> levels;
		Node * t;
		int maxLevel = -1, tempLevel;

		// initial stack values
		nodes.push(this);
		levels.push(0);

		// while stack not empty
		while (!nodes.empty()) {

			// skidamo sa steka
			t = nodes.top();	nodes.pop();
			tempLevel = levels.top();	levels.pop();

			// pushujemo decu
			// left
			if (!t->getLeft()->isLimit()) {
				nodes.push(t->getLeft());
				levels.push(tempLevel + 1);
				// update maxLevela
				if (maxLevel < (tempLevel + 1)) maxLevel = tempLevel + 1;
			}

			if (!t->getRight()->isLimit()) {
				nodes.push(t->getRight());
				levels.push(tempLevel + 1);
				// update maxLevela
				if (maxLevel < (tempLevel + 1)) maxLevel = tempLevel + 1;
			}



		}// endwhile

		if (showMsg) cout << "Cvor " << this->val() << " ima maksimalnu visinu podstabla : " << maxLevel << endl;
		return maxLevel;

	}

	// AVL balance

	int avlBalance(bool showMsg = false){ 
		int leftDepth = 0, rightDepth = 0, avl;

		// leva visina podstabla
		if (!this->getLeft()->isLimit()) leftDepth = this->getLeft()->depth();

		// desna visina podstabla
		if (!this->getRight()->isLimit()) rightDepth = this->getRight()->depth();
		
		avl = leftDepth - rightDepth;
		if (showMsg) cout << "Avl kriterijum cvora [" << this->val() << "] je: " << avl << endl;
		return avl;
	}
	
};

#include <iostream>
#include <fstream>

using namespace std;

struct Node {
	int value;
	int maxleft;
	int maxright;
	int max;
	Node* parent;
	Node* left;
	Node* right;
	Node* operator =(const Node *T) {
		if (T == nullptr) {
			*this = nullptr;
			return nullptr;
		}
		value = T->value;
		maxleft = T->maxleft;
		maxright = T->maxright;
		max = T->max;
		parent = T->parent;
		left = T->left;
		right = T->right;
		return this;
	}
};

bool check = false;

void Put(int value, Node *current) {
	if (current->value == 0 && !check) {
		if (value == 0) // ѕроверка на то, что мы вставили в дерево число нуль
			check = true;
		current->value = value;
		return;
	}
	if (current->value < value)
		if (current->right != nullptr) Put(value, current->right);
		else {
			Node *T = new Node;
			T->parent = current;
			T->left = nullptr;
			T->right = nullptr;
			T->value = value;
			current->right = T;
		}
	else if (current->left != nullptr) Put(value, current->left);
	else {
		Node *T = new Node;
		T->parent = current;
		T->left = nullptr;
		T->right = nullptr;
		T->value = value;
		current->left = T;
	}
}

int Count(Node *current) {
	if (current == nullptr) return 0;
	current->maxleft = Count(current->left);
	current->maxright = Count(current->right);
	if (current->maxleft < current->maxright) current->max = 1 + current->maxright;
	else current->max = 1 + current->maxleft;
	return current->max;
}

Node* Found(Node * current) {
	if (current == nullptr) return nullptr;
	Node* LT = new Node;
	Node* RT = new Node;
	Node* Max = new Node;
	LT = Found(current->left);
	RT = Found(current->right);
	if (LT != nullptr&&RT != nullptr) {
		if (LT->maxleft + LT->maxright > RT->maxleft + RT->maxright)
			Max = LT;
		else Max = RT;
	}
	if (LT == nullptr) Max = RT;
	else Max = LT;
	if (!Max) return current;
	if (current->maxleft + current->maxright >= Max->maxleft + Max->maxright) return current;
	return Max;
}

void Out(ofstream &out, Node* current) {
	if (current == nullptr) return;
	out << current->value << '\n';
	Out(out, current->left);
	Out(out, current->right);
}

int main()
{
	Node *root = new Node;
	root->left = nullptr;
	root->right = nullptr;
	root->parent = nullptr;
	root->value = 0;
	ifstream in("in.txt");
	ofstream out("out.txt");
	int number;
	while (in >> number) Put(number, root);
	Count(root);
	Node* Needed = Found(root);
	Node* Swaped = Needed;
	Swaped = Swaped->right;
	if (Swaped == nullptr) {
		root = Needed->left;
		Out(out, root);
		return 0;
	}
	if (Swaped->left == nullptr) {
		Needed->value = Swaped->value;
		Swaped->parent->right = Swaped->right;
		Out(out, root);
		return 0;
	}
	while (Swaped->left != nullptr) Swaped = Swaped->left;
	Needed->value = Swaped->value;
	Swaped->parent->left = Swaped->right;
	delete Swaped;
	Out(out, root);
	return 0;
}

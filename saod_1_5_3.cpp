#include <iostream>

using namespace std;

typedef struct Node {
	int data;
	struct Node* left;
	struct Node* right;
}Node;

Node* root = NULL;

Node* search(Node* node, int value) {
	if (node == NULL || node->data == value) {
		return node;
	}

	if (value < node->data) {
		return search(node->left, value);
	}
	else {
		return search(node->right, value);
	}
}

void add(Node* parent, int value, int side) {
	Node* new_node = new Node;
	new_node->data = value;
	new_node->left = NULL;
	new_node->right = NULL;

	if (side == 0) {
		if (parent->left == NULL) {
			parent->left = new_node;
		}
		else {
			cout << "Левый потомок уже есть" << endl;
			delete new_node;
		}
	}
	else if (side == 1) {
		if (parent->right == NULL) {
			parent->right = new_node;
		}
		else {
			cout << "Правый потомок уже есть" << endl;
			delete new_node;
		}
	}
}

void print(Node* node, int level) {
	if (node != NULL) {
		print(node->right, level + 1);
		for (int i = 0; i < level * 5; i++) cout << " ";
		cout << node->data << endl;
		print(node->left, level + 1);
	}
}

void remove(Node* node) {
	if (node != NULL) {
		remove(node->left);
		remove(node->right);
		delete node;
	}
}

void add_root(int value) {
	root = new Node;
	root->left = NULL;
	root->right = NULL;
	root->data = value;
}

int main() {
	setlocale(LC_ALL, "");
	while (true) {
		int choice, value;
		cout << "1 - поиск вершины" << endl;
		cout << "2 - добавление вершины" << endl;
		cout << "3 - вывод дерева" << endl;
		cout << "4 - удаление дерева" << endl;
		cout << "5 - выход" << endl;
		cin >> choice;
		if (choice == 1) {
			if (root != NULL) {
				cout << "Введите значение для поиска" << endl;
				cin >> value;
				if (search(root, value) != NULL) {
					cout << "Вершина найдена" << endl;
				}
				else {
					cout << "Вершина не найдена" << endl;
				}
			}
			else {
				cout << "Дерево пустое" << endl;
			}
		}
		else if (choice == 2) {
			if (root != NULL) {
				cout << "Введите родителя" << endl;
				cin >> value;
				Node* parent = search(root, value);
				if (parent == NULL) {
					cout << "Такой вершины не найдено" << endl;
				}
				cout << "Введите значение для добавления" << endl;
				cin >> value;
				int side{ 0 };
				cout << "Куда добавить\n0 - лево\n1 - право" << endl;
				cin >> side;
				add(parent, value, side);
			}
			else {
				cout << "Введите значение" << endl;
				cin >> value;
				add_root(value);
			}
		}
		else if (choice == 3) {
			cout << "Дерево: " << endl;
			print(root, 0);
		}
		else if (choice == 4) {
			remove(root);
			root = NULL;
			cout << "Дерево удалено" << endl;
		} else if (choice == 5) {
			remove(root);
			exit(0);
		}
		else {
			cout << "некорректный ввод" << endl;
		}
	}
	return 0;
}
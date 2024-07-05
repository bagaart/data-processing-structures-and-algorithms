#include <iostream>
#include <locale.h>

using namespace std;
typedef struct Node {
	int data;
	int count;
	struct Node* left;
	struct Node* right;
} Node;

Node* root = NULL;
Node* parent = NULL;

Node* find_node(int value) {
	Node* current = root;
	bool stop = false;
	while (current != NULL && !stop) {
		if (value < current->data) {
			parent = current;
			current = current->left;
		}
		else if (value > current->data) {
			parent = current;
			current = current->right;
		}
		else {
			stop = true;
		}
	}
	return current;
}

void print_branch(int level) {
	for (int i = 0; i < level; i++) {
		if (i == level - 1) {
			cout << "|--";
		}
		else {
			cout << "|  ";
		}
	}
}

void post_order(Node* node, int level) {
	if (node != NULL) {
		post_order(node->right, level + 1);
		print_branch(level);
		cout << node->data << endl;
		post_order(node->left, level + 1);
	}
}

void line_print(Node* node) {
	if (node != NULL) {
		line_print(node->left);
		cout << node->data << " (" << node->count << ")\t";
		line_print(node->right);
	}
}

void find_menu() {
	int value;
	cout << "Введите значение для поиска" << endl;
	cin >> value;
	Node* result = find_node(value);
	if (result != NULL) {
		cout << "Значение " << value << " было найдено " << result->count << " раз(а)" << endl;
	}
	else {
		cout << "Значение " << value << " не найдено" << endl;
	}
}

void print_menu() {
	if (root != NULL) {
		int choice;
		cout << "1 - Вывод в строку" << endl;
		cout << "2 - Вывод oбратнно-симметричном порядок" << endl;
		cin >> choice;
		if (choice == 1) {
			cout << "Дерево в виде строки" << endl;
			line_print(root);
		}
		else if (choice == 2) {
			cout << "Обратно-симметричный порядок" << endl;
			post_order(root, 0);
		}
		else {
			cout << "Некорректный ввод" << endl;
		}
	}
	else {
		cout << "Дерево пустое" << endl;
	}
}

Node* add_rec(Node* node, int value) {
	if (node == NULL) {
		node = new Node;
		node->data = value;
		node->count = 1;
		node->left = NULL;
		node->right = NULL;
	}
	else {
		if (value < node->data) {
			node->left = add_rec(node->left, value);
		}
		else if (value > node->data) {
			node->right = add_rec(node->right, value);
		}
		else {
			node->count++;
		}
	}
	return node;
}

void add_norec(int value) {
	if (root == NULL) {
		root = new Node;
		root->count = 1;
		root->data = value;
		root->right = NULL;
		root->left = NULL;
		return;
	}

	Node* parent = NULL;
	Node* current = root;
	
	while (current != NULL) {
		parent = current;
		if (value < current->data) {
			current = current->left;
		}
		else if (value > current->data) {
			current = current->right;
		}
		else {
			current->count++;
		}
	}

	current = new Node;
	current->left = NULL;
	current->right = NULL;
	current->count = 1;
	current->data = value;
	if (value < parent->data) {
		parent->left = current;
	}
	else {
		parent->right = current;
	}
}

void add_menu() {
	int value, choice;
	cout << "Введите значение для добавления" << endl;
	cin >> value;
	cout << endl;
	cout << "1 - рекурсивный" << endl << "2 - нерекурсивный" << endl;
	cin >> choice;
	if (choice == 1) {
		root = add_rec(root, value);
	}
	else if (choice == 2) {
		add_norec(value);
	}
	else {
		cout << "некорректная операция" << endl;
	}
}

Node* delete_node(Node* root, int value) {
	if (root == NULL) {
		cout << "Такой вершины нет" << endl;
		return root;
	}

	if (value < root->data) {
		root->left = delete_node(root->left, value);
	}
	else if (value > root->data) {
		root->right = delete_node(root->right, value);
	}
	else {
		if (root->left == NULL) {
			Node* temp = root->right;
			delete root;
			cout << "Удалено" << endl;
			return temp;
		}
		else if (root->right == NULL) {
			Node* temp = root->left;
			delete root;
			cout << "Удалено" << endl;
			return temp;
		}

		Node* temp = root->right;
		while (temp->left != NULL) {
			temp = temp->left;
		}

		root->data = temp->data;
		root->right = delete_node(root->right, temp->data);
	}
	return root;
}

void create_tree() {
	srand(time(NULL));
	int n;
	cout << "Введите количество вершин дерева" << endl;
	cin >> n;
	for (int i = 0; i < n; i++) {
		root = add_rec(root, rand() % 100);
	}
}

void clean(Node* node) {
	if (node != NULL) {
		clean(node->left);
		clean(node->right);
		delete node;
	}
}

void delete_menu() {
	int value;
	cout << "Введите значение для удаления" << endl;
	cin >> value;
	root = delete_node(root, value);
}

int main() {
	setlocale(LC_ALL, "");
	while (true) {
		int choice, value;
		cout << endl;
		cout << "1 - Создать дерево" << endl;
		cout << "2 - Добавить вершину" << endl;
		cout << "3 - Поиск вершины" << endl;
		cout << "4 - Вывод дерева" << endl;
		cout << "5 - Удалить вершину" << endl;
		cout << "6 - Удалить дерево" << endl;
		cout << "7 - Выход" << endl;
		cin >> choice;
		if (choice == 1) {
			clean(root);
			root = NULL;
			create_tree();
		}
		else if (choice == 2) {
			add_menu();
		}
		else if (choice == 3) {
			find_menu();
		}
		else if (choice == 4) {
			print_menu();
		}
		else if (choice == 5) {
			delete_menu();
		}
		else if (choice == 6) {
			clean(root);
			root = NULL;
		}
		else if (choice == 7) {
			clean(root);
			root = NULL;
			exit(0);
		}
		else {
			cout << "Некорректный ввод" << endl;
		}
	}
}
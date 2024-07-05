#include <iostream>
#include <locale.h>

using namespace std;

typedef struct Node {
	int data;
	struct Node* next;
	struct Node* prev;
} Node;

Node* head = NULL;

bool is_eempty() {
	return head == NULL;
}

void clean();

Node* create_node(int data) {
	Node* new_node = new Node;
	if (new_node == NULL) {
		cout << "-! Не удалось выделить память" << endl;
		clean();
		exit(1);
	}
	new_node->data = data;
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}

void add(int data) {
	Node* new_node = create_node(data);
	if (head == NULL) {
		head = new_node;
		head->prev = head;
		head->next = head;
	}
	else {
		Node* last = head->prev;
		last->next = new_node;
		new_node->prev = last;
		new_node->next = head;
		head->prev = new_node;
	}
}

void print_forward() {
	if (head == NULL) {
		cout << "Список пуст" << endl;
		return;
	}
	Node* current = head;
	cout << "Вывод списка в прямом порядке:" << endl;
	do {
		cout << current->data << " ";
		current = current->next;
	} while (current != head);
	cout << endl;
}

void print_backward() {
	if (head == NULL) {
		cout << "Список пуст" << endl;
		return;
	}
	Node* current = head->prev;
	cout << "Вывод списка в обратном порядке:" << endl;
	do {
		cout << current->data << " ";
		current = current->prev;
	} while (current != head->prev);
	cout << endl;
}

Node* search_forward(int inf) {
	if (head == NULL) {
		cout << "Список пуст" << endl;
		return NULL;
	}
	Node* current = head;
	do {
		if (current->data == inf) {
			cout << inf << " найден в списке" << endl;
			return current;
		}
		current = current->next;
	} while (current != head);
	cout << inf << " не найден в списке" << endl;
	return NULL;
}

Node* search_backward(int inf) {
	if (head == NULL) {
		cout << "Список пуст" << endl;
		return NULL;
	}
	Node* current = head->prev;
	do {
		if (current->data == inf) {
			cout << inf << " найден в списке" << endl;
			return current;
		}
		current = current->prev;
	} while (current != head->prev);
	cout << inf << " не найден в списке" << endl;
	return NULL;
}

void insert_after(int key, int data) {
	Node* index = search_forward(key);
	if (index == NULL) {
		cout << key << " не найден" << endl;
		return;
	}
	Node* new_node = create_node(data);
	new_node->next = index->next;
	new_node->prev = index;
	index->next->prev = new_node;
	index->next = new_node;
}

void insert_before(int key, int data) {
	Node* index = search_forward(key);
	if (index == NULL) {
		cout << key << " не найден" << endl;
		return;
	}
	Node* new_node = create_node(data);
	new_node->next = index;
	new_node->prev = index->prev;
	index->prev->next = new_node;
	index->prev = new_node;

	if (index == head) {
		head = new_node;
	}
}

void remove_node(int key) {
	Node* index = search_forward(key);
	if (index == NULL) {
		cout << key << " не найдено" << endl;
		return;
	}
	if (index == head) head = index->next;
	index->prev->next = index->next;
	index->next->prev = index->prev;
	delete index;
	cout << key << " удален" << endl;
}

void clean() {
	if (!is_eempty()) {
		Node* current = head;
		Node* temp;
		do {
			temp = current->next;
			delete current;
			current = temp;
		} while (current != head);
	}
}

int main() {
	setlocale(LC_ALL, "");
	while (true) {
		cout << "1 - пустота списка" << endl;
		cout << "2 - вывести список" << endl;
		cout << "3 - добавить элемент в список" << endl;
		cout << "4 - удалить элемент из списка" << endl;
		cout << "5 - найти элемент" << endl;
		cout << "6 - выход" << endl;
		int choice{ 6 };
		cin >> choice;
		if (choice == 1) {
			if (is_eempty()) {
				cout << "Список пуст" << endl;
			}
			else {
				cout << "Список не пуст" << endl;
			}
		}
		else if (choice == 2) {
			if (is_eempty()) {
				cout << "Список пуст" << endl;
				continue;
			}
			cout << "1 - в прямом" << endl;
			cout << "2 - в обратном" << endl;
			int n{ 1 };
			cin >> n;
			if (n == 1) {
				print_forward();
			}
			else if (n == 2) {
				print_backward();
			}
			else {
				cout << "некорректный ввод" << endl;
			}
		}
		else if (choice == 3) {
			if (!is_eempty()) {
				cout << "1 - до" << endl;
				cout << "2 - после" << endl;
				int i{ 0 };
				cin >> i;
				if (i == 1) {
					cout << "введите элемент до которого добавить" << endl;
					int key{ 0 };
					cin >> key;
					cout << "введите значение для добавления" << endl;
					int data{ 0 };
					cin >> data;
					insert_before(key, data);
				}
				else if (i == 2) {
					cout << "введите элемент после которого добавить" << endl;
					int key{ 0 };
					cin >> key;
					cout << "введите значение для добавления" << endl;
					int data{ 0 };
					cin >> data;
					insert_after(key, data);
				}
				else {
					cout << "некорректный ввод" << endl;
				}
			} else{
				cout << "введите значение" << endl;
				int n{ 0 };
				cin >> n;
				add(n);
			}
		}
		else if (choice == 4) {
			if (!is_eempty()) {
				cout << "Введите значение для удаления" << endl;
				int del{ 0 };
				cin >> del;
				remove_node(del);
			}
			else {
				cout << "Список пуст" << endl;
			}
		}
		else if (choice == 5) {
			if (!is_eempty()) {
				cout << "введите значение для поиска" << endl;
				int find{ 0 };
				cin >> find;
				cout << "1 - в прямом" << endl;
				cout << "2 - в обратном" << endl;
				int n{ 0 };
				cin >> n;
				if (find == 1) {
					search_forward(find);
				}
				else if (find == 2) {
					search_backward(find);
				}
				else {
					cout << "некорректный ввод" << endl;
				}
			}
		}
		else if (choice == 6) {
			clean();
			exit(0);
		}
		else {
			cout << "некорректный код" << endl;
		}
	}
}

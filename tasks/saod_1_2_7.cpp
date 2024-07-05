#include <iostream>
#include <locale.h>
#include <windows.h>
#include <ctime>

using namespace std;

struct node {
	char data;
	node* next;
};

struct queue {
	node* head;
	int size;
};

node* create_node() {
	node* new_node = new node;
	new_node->next = NULL;
	new_node->data = 0;
	return new_node;
}

void init_queue(queue* que) {
	que->head = NULL;
	que->size = 0;
}

bool empty(queue* que) {
	return que->size == 0;
}

void push(queue* que, int value) {
	node* new_node = create_node();
	if (new_node != NULL) {
		if (!empty(que)) {
			node* current = que->head;
			while (current->next != NULL) {
				current = current->next;
			}
			current->next = new_node;
		}
		else {
			que->head = new_node;
		}
		new_node->data = value;
		que->size++;
	}
	else {
		cout << "Добавление не удалось" << endl;
	}
}

void pop(queue* que) {
	if (!empty(que)) {
		node* temp = que->head;
		que->head = temp->next;
		delete temp;
		que->size--;
	}
	else {
		cout << "Очередь пуста" << endl;
	}
}

void print_queue(queue* que) {
	cout << endl;
	if (!empty(que)) {
		node* current = que->head;
		while (current != NULL) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}
	else {
		cout << "Очередь пуста" << endl;
	}
	cout << endl;
}

void clean(queue* que) {
	node* current = que->head;
	while (current != NULL) {
		que->head = current->next;
		delete current;
		current = que->head;
	}
}

int main() {
	queue que;
	init_queue(&que);
	setlocale(LC_ALL, "");
	srand((unsigned int)time(NULL));
	bool exit = false;
	int t = 0;
	while (!exit) {
		int choice = rand() % 2;
		if (choice == 0) {
			int n = rand() % 3 + 1;

			for (int i = 0; i < n; i++) {
				char value = rand() % 26 + 65;
				push(&que, value);
			}
			cout << "Добавлено " << n << " элементов" << endl;
		}
		else {
			if (!empty(&que)) {
				cout << "Удален один элемент" << endl;
			}
			else {
				cout << "Была попытка удаления элемента" << endl;
			}
			pop(&que);
		}
		cout << endl;
		cout << "Состояние очереди";
		print_queue(&que);
		cout << endl;
		Sleep(1000);
		if (t == 10) {
			char ch;
			cout << endl << "Нажмите 5 для выхода, чтобы продолжить любую другую." << endl;
			cin >> ch;
			if (ch == '5') exit = !exit;
			cout << endl;
			t = 0;
		}
		t++;
	}
	clean(&que);
	return 0;
}

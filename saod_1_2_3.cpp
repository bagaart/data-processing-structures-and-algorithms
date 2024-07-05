﻿#include <iostream>
#include <locale.h>
#include <ctime>

using namespace std;

struct node {
	int data;
	node* next;
};

struct stack {
	node* head;
	int size;
};

void init_stack(stack* st) {
	st->head = NULL;
	st->size = 0;
}

bool empty(stack* st) {
	return st->size == 0;
}

void push(stack* st) {
	int value{ 0 };
	cout << "Введите значение\n";
	cin >> value;
	node* new_node = new node;
	if (new_node != NULL) {
		new_node->data = value;
		new_node->next = st->head;
		st->head = new_node;
		st->size++;
	}
	else {
		cout << "Не удалось добавить\n";
	}
}

void push(stack* st, int value) {
	node* new_node = new node;
	if (new_node != NULL) {
		new_node->data = value;
		new_node->next = st->head;
		st->head = new_node;
		st->size++;
	}
	else {
		cout << "Не удалось добавить\n";
	}
}

void pop(stack* st) {
	node* temp = st->head;
	if (!empty(st)) {
		node* temp = st->head;
		st->head = temp->next;
		delete temp;
		st->size--;
	}
	else {
		cout << "Стек пуст" << endl;
	}
}

void print_stack(stack* st) {
	cout << endl;
	if (!empty(st)) {
		node* temp = st->head;
		while (temp != NULL) {
			cout << temp->data << endl;
			temp = temp->next;
		}
	}
	else {
		cout << "Стек пуст" << endl;
	}
	cout << endl;
}

void clean(stack* st) {
	while (!empty(st)) {
		pop(st);
	}
}

void random_push(stack* st) {
	srand((unsigned int)time(NULL));
	int n{ 0 }, value{ 0 };
	cout << "Введите количество элементов\n";
	cin >> n;
	while (n) {
		value = rand() % 10000;
		push(st, value);
		n--;
	}
}

int main() {
	stack st;
	init_stack(&st);
	int choice{ 0 };
	setlocale(LC_ALL, "");
	while (true) {
		cout << "1. - проверка пустоты.\n";
		cout << "2. - добавление элемента.\n";
		cout << "3. - удаление элемента.\n";
		cout << "4. - вывод списка.\n";
		cout << "5. - выход.\n";
		cin >> choice;
		if (choice == 1) {
			if (empty(&st)) {
				cout << "Стек пуст" << endl;
			}
			else {
				cout << "Стек не пуст" << endl;
			}
		}
		else if (choice == 2) {
			cout << "0. - ввести вручную" << endl;
			cout << "1. - ввести случайные значения" << endl;
			cin >> choice;
			if (choice == 0) push(&st);
			else if (choice == 1) random_push(&st);
			else cout << "Неверный выбор" << endl;
		}
		else if (choice == 3) {
			pop(&st);
		}
		else if (choice == 4) {
			print_stack(&st);
		}
		else {
			break;
		}
	}
	clean(&st);
	return 0;
}

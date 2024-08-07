﻿#include <iostream>
#include <locale.h>

#define list_size 5
using namespace std;

struct node {
	int data;
};

node list[list_size];
int lsize = 0;

void init_list() {
	for (int i = 0; i < list_size; i++) {
		list[i].data = -1;
	}
}

bool empty() {
	return lsize == 0;
}

bool full() {
	return lsize == list_size;
}

void print_list() {
	cout << endl;
	if (!empty()) {
		for (int i = 0; i < list_size; i++) {
			if (list[i].data != -1) {
				cout << list[i].data << " ";
			}
		}
	}
	else {
		cout << "Список пуст";
	}
	cout << endl;
	cout << endl;
}

void finder() {
	if (empty()) {
		cout << "Список пуст" << endl;
		return;
	}
	else {
		cout << "Введите значение" << endl;
		int value;
		cin >> value;
		for (int i = 0; i < list_size; i++) {
			if (list[i].data == value) {
				cout << "Такой элемент есть на позиции " << i << endl;
				return;
			}
		}
	}
	cout << "Такого элемента нет" << endl;
}

int finder(int value) {
	if (empty()) {
		return -1;
	}
	else {
		for (int i = 0; i < list_size; i++) {
			if (list[i].data == value) {
				return i;
			}
		}
	}
	return -1;
}

void push() {
	//if (full()) {
		//cout << "Список полон" << endl;
		//return;
	//}
	int value;
	cout << "Введите значение" << endl;
	cin >> value;
	if (empty()) {
		list[0].data = value;
		lsize++;
		return;
	}
	int pos;
	for (int i = 0; i < list_size; i++) {
		pos = i;
		if (list[i].data >= value || list[i].data == -1) break;

	}
	for (int i = list_size - 1; i >  pos; i--) {
		list[i].data = list[i - 1].data;
	}
	list[pos].data = value;
	lsize++;
}

void pop() {
	int pos;
	if (empty()) {
		cout << "Список пуст" << endl;
		return;
	}
	cout << "Ведите элемент для удаления" << endl;
	cin >> pos;
	pos = finder(pos);
	if (pos == -1) {
		cout << "Такого элемента нет" << endl;
		return;
	}
	for (int i = pos; i < lsize; i++) {
		if (i + 1 >= list_size) {
			list[i].data = -1;
		}
		else {
			list[i].data = list[i + 1].data;
			list[i + 1].data = -1;
		}
	}
	lsize--;
}

int main() {
	init_list();
	setlocale(LC_ALL, "");
	while (true) {
		cout << "1 - вывод списка" << endl;
		cout << "2 - поиск элемента" << endl;
		cout << "3 - добавление" << endl;
		cout << "4 - удаление" << endl;
		cout << "5 - выход" << endl;
		int choice;
		cin >> choice;
		if (choice == 1) {
			print_list();
		}
		else if (choice == 2) {
			finder();
		}
		else if (choice == 3) {
			push();
		}
		else if (choice == 4) {
			pop();
		}
		else if (choice == 5){
			break;
		}
	}
	return 0;
}

#include <iostream>
#include <locale.h>

#define list_size 5
using namespace std;

struct node {
	int data;
	int next;
};

node list[list_size];
int lsize = 0;

void init_list() {
	for (int i = 0; i < list_size; i++) {
		list[i].data = -1;
		list[i].next = -1;
	}
	list[0].data = -404;
}

bool empty() {
	return lsize == 0;
}

bool full() {
	return lsize + 1 == list_size;
}

void print_list() {
	cout << endl;
	if (!empty()) {
		int i = 0;
		while (list[i].data != -1) {
			if (list[i].data != -404) {
				cout << list[i].data << " ";
			}
			if (list[i].next == -1) break;
			i = list[i].next;
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
		int i = 0;
		while (list[i].data != -1) {
			if (list[i].data == value) {
				cout << "Такой элемент есть на позиции " << i << endl;
				return;
			}
			if (list[i].next == -1) break;
			i = list[i].next;
		}
	}
	cout << "Такого элемента нет" << endl;
}

int finder(int value) {
	if (empty()) {
		return -1;
	}
	else {
		int i = 0;
		while (list[i].data != -1) {
			if (list[i].data == value) {
				return i;
			}
			if (list[i].next == -1) break;
			i = list[i].next;
		}
	}
	return -1;
}

void push() {
	if (full()) {
		cout << "Список полон" << endl;
		return;
	}
	int value;
	if (empty()) {
		cout << "Введите значение" << endl;
		cin >> value;
		list[1].data = value;
		list[0].next = 1;
		lsize++;
		return;
	}
	int choice;
	cout << "1 - вставить до" << endl;
	cout << "2 - вставить после" << endl;
	cin >> choice;
	if (choice == 1) {
		int pos;
		cout << "Ведите элемент перед которым вставить" << endl;
		cin >> value;
		pos = finder(value);
		if (pos == -1) {
			cout << "Такого элемента нет" << endl;
			return;
		}
		cout << "Введите элемент" << endl;
		cin >> value;

		int k = 0;
		while (list[k].next != pos) {
			k = list[k].next;
		}
		int free_place = -1;
		for (int i = 1; i < list_size; i++) {
			if (list[i].data == -1) {
				free_place = i;
				break;
			}
		}
		list[free_place].data = value;
		list[free_place].next = list[k].next;
		list[k].next = free_place;
		lsize++;
	}
	else if (choice == 2) {
		int pos;
		cout << "Ведите элемент после которого вставить" << endl;
		cin >>  value;
		pos = finder(value);
		if (pos == -1) {
			cout << "Такого элемента нет" << endl;
			return;
		}
		cout << "Введите элемент" << endl;
		cin >> value;

		int free_place = -1;
		for (int i = 1; i < list_size; i++) {
			if (list[i].data == -1) {
				free_place = i;
				break;
			}
		}
		list[free_place].data = value;
		list[free_place].next = list[pos].next;
		list[pos].next = free_place;
		lsize++;
	}
}

void pop() {
	int epos;
	if (empty()) {
		cout << "Список пуст" << endl;
		return;
	}
	cout << "Ведите элемент для удаления" << endl;
	cin >> epos;
	int pos = finder(epos);
	if (pos == -1) {
		cout << "Такого элемента нет" << endl;
		return;
	}
	int k = 0;
	while (list[k].next != pos) k++;
	int t = list[k].next;
	list[k].next = list[t].next;
	list[t].data = -1;
	list[t].next = -1;
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
		else {
			break;
		}
	}
	return 0;
}

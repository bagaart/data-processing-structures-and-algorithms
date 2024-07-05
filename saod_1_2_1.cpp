#include <iostream>
#include <locale.h>
#define stack_size 5

using namespace std;

struct stack {
	int head;
	int size;
	int data[stack_size];
};

void init_stack(stack* st) {
	st->head = 0;
	st->size = 0;
	st->head = -1;
}

bool empty(stack* st) {
	return st->size == 0;
}

bool full(stack* st) {
	return st->size == stack_size;
}

void push(stack* st) {
	if (!full(st)) {
		int value{ 0 };
		cout << "Введите значение\n";
		cin >> value;
		st->data[++st->head] = value;
		st->size++;
	}
	else {
		cout << "Стек полон" << endl;
	}
}

void pop(stack* st) {
	if (!empty(st)) {
		st->head--;
		st->size++;
	}
	else {
		cout << "Стек пуст" << endl;
	}
}

void print_stack(stack* st) {
	cout << endl;
	if (!empty(st)) {
		for (int i = st->head; i >= 0; i--) {
			cout << st->data[i] << endl;
		}
	}
	else {
		cout << "Стек пуст" << endl;
	}
	cout << endl;
}

int main() {
	stack st;
	init_stack(&st);
	int choice{ 0 };
	setlocale(LC_ALL, "");
	while (true) {
		cout << "1. - проверка пустоты.\n";
		cout << "2. - проверка полноты.\n";
		cout << "3. - добавление элемента.\n";
		cout << "4. - удаление элемента.\n";
		cout << "5. - вывод стека.\n";
		cout << "6. - выход.\n";
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
			if (full(&st)) {
				cout << "Стек полон" << endl;
			}
			else {
				cout << "Стек не полон" << endl;
			}
		}
		else if (choice == 3) {
			push(&st);
		}
		else if (choice == 4) {
			pop(&st);
		}
		else if (choice == 5) {
			print_stack(&st);
		}
		else {
			break;
		}
	}
	return 0;
}

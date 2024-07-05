#include <iostream>
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
	if (temp != NULL) {
		st->head = temp->next;
		delete temp;
		st->size--;
	}
	else {
		cout << "Стек пуст" << endl;
	}
}

void popi(stack* st) {
	node* temp = st->head;
	if (temp != NULL) {
		st->head = temp->next;
		delete temp;
		st->size--;
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

void pseudo_pop(stack* st, stack* trash) {
	node* temp = st->head;
	if (temp != NULL) {
		st->head = temp->next;
		temp->next = trash->head;
		trash->head = temp;
		st->size--;
		trash->size++;
	}
	else {
		cout << "Основной стек пуст" << endl;
	}
}

void pseudo_push(stack* st, stack* trash) {
	node* temp = trash->head;
	if (temp != NULL) {
		trash->head = temp->next;
		temp->next = st->head;
		st->head = temp;
		st->size++;
		trash->size--;
	}
	else {
		cout << "Вспомогательный стек пуст" << endl;
	}
}

int main() {
	stack st, trash;
	init_stack(&st);
	init_stack(&trash);
	int choice{ 0 };
	setlocale(LC_ALL, "");
	while (true) {
		cout << "1. - проверка пустоты.\n";
		cout << "2. - добавление элемента.\n";
		cout << "3. - удаление элемента.\n";
		cout << "4. - вывод стека.\n";
		cout << "5. - вывод вспомогательного стека.\n";
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
			cout << "0. - ввести вручную" << endl;
			cout << "1. - ввести случайные значения" << endl;
			cout << "2. - взять со стека" << endl;
			cin >> choice;
			if (choice == 0) push(&st);
			else if (choice == 1) random_push(&st);
			else if (choice == 2) pseudo_push(&st, &trash);
			else cout << "Неверный выбор" << endl;
		}
		else if (choice == 3) {
			cout << "0. - реальное удаление" << endl;
			cout << "1. - псевдоудаление" << endl;
			cin >> choice;
			if (choice == 0) pop(&st);
			else if (choice == 1) pseudo_pop(&st, &trash);
			else cout << "Неверный выбор" << endl;
		}
		else if (choice == 4) {
			print_stack(&st);
		}
		else if (choice == 5) {
			print_stack(&trash);
		}
		else {
			break;
		}
	}
	clean(&st);
	clean(&trash);
	return 0;
}

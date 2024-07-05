#include <iostream>
#include <locale.h>

using namespace std;

struct node {
	int data;
	node* next;
};

struct queue {
	node* head;
	int size;
};

node* create_node(){
	node* new_node = new node;
	new_node->next = NULL;
	new_node->data = -1;
	return new_node;
}

void init_queue(queue* que) {
	que->head = NULL;
	que->size = 0;
}

bool empty(queue* que) {
	return que->size == 0;
}

void push(queue* que) {
	node* new_node = create_node();
	if (new_node != NULL) {
		int value{ 0 };
		cout << "Введите значение\n";
		cin >> value;
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
			cout << current->data << endl;
			current = current->next;
		}
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
	int choice{ 0 };
	setlocale(LC_ALL, "");
	while (true) {
		cout << "1. - проверка пустоты.\n";
		cout << "2. - добавление элемента.\n";
		cout << "3. - удаление элемента.\n";
		cout << "4. - вывод очереди.\n";
		cout << "5. - выход.\n";
		cin >> choice;
		if (choice == 1) {
			if (empty(&que)) {
				cout << "Очередь пуста" << endl;
			}
			else {
				cout << "Очередь не пуста" << endl;
			}
		}
		else if (choice == 2) {
			push(&que);
		}
		else if (choice == 3) {
			pop(&que);
		}
		else if (choice == 4) {
			print_queue(&que);
		}
		else {
			break;
		}
	}
	clean(&que);
	return 0;
}

#include <iostream>
#include <locale.h>

#define queue_size 5

using namespace std;

struct queue {
	int head;
	int tail;
	int size;
	int data[queue_size];
};


void init_queue(queue* que) {
	que->head = 0;
	que->tail = -1;
	que->size = 0;
	for (int i = 0; i < queue_size; i++) {
		que->data[i] = -1;
	}
}

bool empty(queue* que) {
	return que->size == 0;
}

bool full(queue* que) {
	return que->size == queue_size;
}

void push(queue* que) {
	if (!full(que)) {
		int value{ 0 };
		cout << "Введите значение\n";
		cin >> value;
		que->data[(++que->tail) % queue_size] = value;
		que->size++;
	}
	else {
		cout << "Очередь полна" << endl;
	}
}

void pop(queue* que) {
	if (!empty(que)) {
		que->data[que->head] = -1;
		que->head = (que->head + 1) % queue_size;
		que->size--;
	}
	else {
		cout << "Очередь пуста" << endl;
	}
}

void print_queue(queue* que) {
	cout << endl;
	if (!empty(que)) {
		int j = que->head;
		for (int i = 0; i < que->size; i++) {
			cout << que->data[j] << endl;
			j = (j + 1) % queue_size;
		}
	}
	else {
		cout << "Очередь пуста" << endl;
	}
	cout << endl;
}

int main() {
	queue que;
	init_queue(&que);
	int choice{ 0 };
	setlocale(LC_ALL, "");
	while (true) {
		cout << "1. - проверка пустоты.\n";
		cout << "2. - проверка полноты.\n";
		cout << "3. - добавление элемента.\n";
		cout << "4. - удаление элемента.\n";
		cout << "5. - вывод очереди.\n";
		cout << "6. - выход.\n";
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
			if (full(&que)) {
				cout << "Очередь полона" << endl;
			}
			else {
				cout << "Очередь не полона" << endl;
			}
		}
		else if (choice == 3) {
			push(&que);
		}
		else if (choice == 4) {
			pop(&que);
		}
		else if (choice == 5) {
			print_queue(&que);
		}
		else {
			break;
		}
	}
	return 0;
}

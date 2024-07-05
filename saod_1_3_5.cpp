#include <iostream>
#include <locale.h>

using namespace std;

struct node {
	int data;
	node* next;
};

struct list {
	node* head;
};


list support_list;

node* create_node() {
	node* new_node = new node;
	if (new_node != NULL) {
		new_node->data = -1;
		new_node->next = NULL;
	}
	return new_node;
}

void init_list(list* li) {
	li->head = NULL;
}

bool empty(list* li) {
	return li->head == NULL;
}

void print_list(list* li) {
	cout << endl;
	if (empty(li)) {
		cout << "Список пуст" << endl;
	}
	node* current = li->head;
	while (current != NULL) {
		cout << current->data << " ";
		current = current->next;
	}
	cout << endl;
}

void finder(list* li) {
	if (empty(li)) {
		cout << "Список пуст" << endl;
		return;
	}
	int value;
	cout << "Введите значение" << endl;
	cin >> value;
	node* current = li->head;
	while (current != NULL) {
		if (current->data == value) {
			cout << "Такой элемент есть" << endl;
			return;
		}
		current = current->next;
	}
	cout << "Такого элемента нет" << endl;
}

void push_before(list* li) {
	node* new_node = create_node();
	if (new_node == NULL) {
		cout << "Добавление не удалось" << endl;
		return;
	}
	cout << "Введите элемент до которго хотите вставить" << endl;
	int epos;
	cin >> epos;
	node* current = li->head;
	if (epos == current->data) {
		cout << "Введите значение" << endl;
		int value;
		cin >> value;
		new_node->data = value;
		new_node->next = li->head;
		li->head = new_node;
		return;
	}
	while (current->next != NULL) {
		if (current->next->data == epos) break;
		current = current->next;
	}
	if (current->next == NULL) {
		cout << "Такого элемента нет" << endl;
		return;
	}
	cout << "Введите значение" << endl;
	int value;
	cin >> value;
	new_node->data = value;
	new_node->next = current->next;
	current->next = new_node;
}

void push_after(list* li) {
	node* new_node = create_node();
	if (new_node == NULL) {
		cout << "Добавление не удалось" << endl;
		return;
	}
	cout << "Введите элемент после которго хотите вставить" << endl;
	int epos;
	cin >> epos;
	node* current = li->head;
	while (current != NULL) {
		if (current->data == epos) break;
		current = current->next;
	}
	if (current == NULL) {
		cout << "Такого элемента нет" << endl;
		return;
	}
	cout << "Введите значение" << endl;
	int value;
	cin >> value;
	new_node->data = value;
	new_node->next = current->next;
	current->next = new_node;
}

void push(list* li) {
	if (empty(li)) {
		node* new_node = create_node();
		if (new_node == NULL) {
			cout << "Добавление не удалось" << endl;
			return;
		}
		int value;
		cout << "Введите значение" << endl;
		cin >> value;
		new_node->data = value;
		li->head = new_node;
		return;
	}
	int choice;
	cout << "1 - вставка до" << endl;
	cout << "2 - вставка после" << endl;
	cout << "3 - вставка в конец" << endl;
	cin >> choice;
	if (choice == 1) {
		push_before(li);
	}
	else if (choice == 2) {
		push_after(li);
	}
	else if (choice == 3) {
		node* new_node = create_node();
		if (new_node == NULL) {
			cout << "Добавление не удалось" << endl;
			return;
		}
		cout << "Введите значение" << endl;
		int value;
		cin >> value;
		node* current = li->head;
		while (current->next != NULL) current = current->next;
		current->next = new_node;
		new_node->data = value;
	}
	else {
		cout << "Некорректный ввод" << endl;
		return;
	}
}

void pop(list* li) {
	if (empty(li)) {
		cout << "Список пустой" << endl;
		return;
	}
	cout << "Введите значение" << endl;
	int value;
	cin >> value;
	node* current = li->head;
	if (value == current->data) {
		node* temp = li->head;
		li->head = temp->next;
		temp->next = (&support_list)->head;
		(&support_list)->head = temp;
		return;
	}
	while (current->next != NULL) {
		if (current->next->data == value) break;
		current = current->next;
	}
	if (current->next == NULL) {
		cout << "Такого элемента нет" << endl;
		return;
	}
	node* temp = current->next;
	current->next = temp->next;
	temp->next = (&support_list)->head;
	(&support_list)->head = temp;
}

void clean(list* li) {
	node* temp;
	while (li->head != NULL) {
		temp = li->head;
		li->head = temp->next;
		delete temp;
	}
}

int main() {
	list li;
	init_list(&li);
	init_list(&support_list);
	setlocale(LC_ALL, "");
	while (true) {
		cout << "1 - вывод списка" << endl;
		cout << "2 - поиск элемента" << endl;
		cout << "3 - добавление" << endl;
		cout << "4 - удаление" << endl;
		cout << "5 - вывод вспомогательного списка" << endl;
		cout << "6 - выход" << endl;
		int choice;
		cin >> choice;
		if (choice == 1) {
			print_list(&li);
		}
		else if (choice == 2) {
			finder(&li);
		}
		else if (choice == 3) {
			push(&li);
		}
		else if (choice == 4) {
			pop(&li);
		}
		else if (choice == 5) {
			print_list(&support_list);
		}
		else {
			break;
		}
	}
	clean(&support_list);
	clean(&li);
	return 0;
}
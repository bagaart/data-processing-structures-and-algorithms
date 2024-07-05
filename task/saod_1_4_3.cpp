#include <locale.h>
#include <iostream>

using namespace std;

typedef struct smallist {
	int data;
	struct smallist* next;
}smalllist;

typedef struct biglist {
	int data;
	struct smallist* first;
	struct biglist* next;
}biglist;

biglist* list = NULL;

void init() {
	list = new biglist;
	list->next = NULL;
	list->first = NULL;
	list->data = 0;
}

bool is_big_empty() {
	return list->next == NULL;
}

bool is_small_empty(biglist* current) {
	return current->first->next == NULL;
}

void print_list() {
	cout << "Список" << endl;
	if (!is_big_empty()) {
		biglist* bigcurrent = list->next;
		while (bigcurrent != NULL) {
			cout << endl << "подсписок " << bigcurrent->data << ": ";
			if (!is_small_empty(bigcurrent)) {
				smallist* smallcurrent = bigcurrent->first->next;
				while (smallcurrent != NULL) {
					cout << smallcurrent->data << " ";
					smallcurrent = smallcurrent->next;
				}

			}
			bigcurrent = bigcurrent->next;
		}
	}
	else {
		cout << "Список пуст" << endl;
	}
	cout << endl;
}

void add_samll_to_big() {
	int value{ 0 }, key{ 0 }, choice{ 0 };
	biglist* bigcurrent = NULL;
	biglist* tmp = new biglist;
	tmp->first = new smallist;

	cout << "1 - добавить до указанного" << endl;
	cout << "2 - добавить после указанного" << endl;
	cin >> choice;

	if (choice == 1) {
		if (!is_big_empty()) {
			biglist* prev = list;
			bigcurrent = list->next;
			cout << "Введите подсписок, перед которым добавить" << endl;
			cin >> key;
			while (bigcurrent != NULL) {
				if (bigcurrent->data == key) break;
				bigcurrent = bigcurrent->next;
				prev = prev->next;
			}
			if (bigcurrent == NULL) {
				cout << "Такого подсписка не найдено" << endl;
				return;
			}
			tmp->next = bigcurrent;
			tmp->first->next = NULL;
			prev->next = tmp;
		}
		else {
			tmp->next = NULL;
			tmp->first->next = NULL;
			list->next = tmp;
		}
	}
	else if (choice == 2) {
		if (!is_big_empty()) {
			bigcurrent = list->next;
			cout << "Введите заголовок, после которого добавить" << endl;
			cin >> key;
			while (bigcurrent != NULL) {
				if (bigcurrent->data == key) break;
				bigcurrent = bigcurrent->next;
			}
			if (bigcurrent == NULL) {
				cout << "Такого подсписка не найдено" << endl;
				return;
			}
			tmp->next = bigcurrent->next;
			tmp->first->next = NULL;
			bigcurrent->next = tmp;
		}
		else {
			tmp->next = NULL;
			tmp->first->next = NULL;
			list->next = tmp;
		}
	}
	else {
		cout << "некорректный ввод" << endl;
		return;
	}
	cout << "Введите значение заголовка для добавления" << endl;
	cin >> value;
	tmp->first->data = value;
	tmp->data = value;
	cout << "Подсписок с заголовком " << value << " добавлен в список" << endl;
}

void add_to_small() {
	if (!is_big_empty()) {
		int bigvalue{ 0 }, data{ 0 }, smallvalue{ 0 };
		biglist* bigcurrent = list->next;
		cout << "Введите заголовок подсписка, куда нужно добавить" << endl;
		cin >> bigvalue;
		while (bigcurrent != NULL) {
			if (bigvalue == bigcurrent->data) break;
			bigcurrent = bigcurrent->next;
		}
		if (bigcurrent == NULL) {
			cout << "Такой заголовк не найден" << endl;
			return;
		}

		smallist* head = bigcurrent->first;
		smalllist* smallcurrent = NULL;
		smallist* tmp = new smallist;
		int choice{ 0 };
		cout << "1 - добавить до указанного" << endl;
		cout << "2 - добавить после указанного" << endl;
		cin >> choice;
		if (choice == 1) {
			if (!is_small_empty(bigcurrent)) {
				smallist* prev = head;
				smallcurrent = head->next;
				cout << "Введите значение, перед которым добавить" << endl;
				cin >> smallvalue;
				while (smallcurrent != NULL) {
					if (smallcurrent->data == smallvalue) break;
					smallcurrent = smallcurrent->next;
					prev = prev->next;
				}
				if (smallcurrent == NULL) {
					cout << "Значение не найдено" << endl;;
					return;
				}
				tmp->next = smallcurrent;
				prev->next = tmp;
			}
			else {
				tmp->next = NULL;
				head->next = tmp;
			}
		}
		else if (choice == 2) {
			if (!is_small_empty(bigcurrent)) {
				cout << "Введите значение, после которого добавить " << endl;;
				cin >> smallvalue;
				smallcurrent = head->next;
				while (smallcurrent != NULL){
					if (smallcurrent->data != smallvalue) break;
					smallcurrent = smallcurrent->next;
				}
				if (smallcurrent == NULL) {
					cout << "Значение не найдено" << endl;
					return;
				}
				tmp->next = smallcurrent->next;
				smallcurrent->next = tmp;
			}
			else {
				tmp->next = NULL;
				head->next = tmp;
			}
		}
		else {
			cout << "некорректный ввод " << endl;
			return;
		}

		cout << "введите значение для добавления" << endl;
		cin >> data;
		tmp->data = data;
		cout << "Элемент добавлен" << endl;
	}
	else {
		cout << "Список пуст, добавть подсписок" << endl;
	}
}

void remove_small_from_big() {
	if (is_big_empty()) {
		cout << "Список пуст" << endl;
		return;
	}

	int value{ 0 };
	cout << "Введите заголовок для удаления подсписка" << endl;
	cin >> value;

	biglist* prev = NULL;
	biglist* bigcurrent = list;
	while (bigcurrent != NULL) {
		if (bigcurrent->data == value) break;
		prev = bigcurrent;
		bigcurrent = bigcurrent->next;
	}
	if (bigcurrent == NULL) {
		cout << "Подсписок с таким заголовком не найден" << endl;
		return;
	}

	smallist* smallcurrent = bigcurrent->first;
	smallist* tmp = NULL;
	while (smallcurrent != NULL) {
		tmp = smallcurrent;
		smallcurrent = smallcurrent->next;
		delete tmp;
	}

	if (prev == NULL) {
		list = bigcurrent->next;
	}
	else {
		prev->next = bigcurrent->next;
	}

	delete bigcurrent;
	cout << "Подсписок удален" << endl;
}

void remove_from_small() {
	if (!is_big_empty()) {
		int value{ 0 };
		biglist* bigcurrent = NULL;
		bigcurrent = list->next;
		cout << "Введите заголовок подсписка, из которого хотите удалить" << endl;
		cin >> value;
		while (bigcurrent != NULL) {
			if (bigcurrent->first->data == value) break;
			bigcurrent = bigcurrent->next;
		}
		if (bigcurrent == NULL) {
			cout << "Значние " << value << " не найдено" << endl;
			return;
		}
		if (!is_small_empty(bigcurrent)) {
			smallist* head = bigcurrent->first;
			smallist* smallcurrent = NULL;
			smallist* smallprev = NULL;
			smallcurrent = head->next;
			smallprev = head;
			cout << "Введите значение для удаления" << endl;
			cin >> value;
			while (smallcurrent != NULL)
			{
				if (smallcurrent->data == value) break;
				smallcurrent = smallcurrent->next;
				smallprev = smallprev->next;
			}
			if (smallcurrent == NULL)
			{
				cout << "Значение " << value << " не найдено" << endl;
				return;
			}
			smallprev->next = smallcurrent->next;
			delete smallcurrent;
			cout << "Значние удалено" << endl;;
		}
		else {
			cout << "Подсписок пуст" << endl;
		}
	}
	else {
		cout << "Список пуст" << endl;
	}
}

void search() {
	if (!is_big_empty()) {
		int value{ 0 };
		cout << "Введите значение для поиска" << endl;
		cin >> value;
		biglist* bigcurrent = list->next;
		while (bigcurrent != NULL) {
			if (!is_small_empty(bigcurrent)) {
				int pos = 1;
				smallist* smallcurrent = bigcurrent->first->next;
				while (smallcurrent != NULL) {
					if (smallcurrent->data == value) break;
					smallcurrent = smallcurrent->next;
					++pos;
				}
				if (smallcurrent != NULL) {
					cout << "Элемент найден в подсписке " << bigcurrent->first->data << " на позиции " << pos << endl;
				}
			}
			else {
				cout << "В подсписке " << bigcurrent->data << " нет элемента или он пуст" << endl;
			}
			bigcurrent = bigcurrent->next;
		}
	}
	else {
		cout << "Список пуст" << endl;
	}
}

void clean() {
	biglist* bigcurrent;
	smallist* smallcurrent;
	while (list != NULL) {
		bigcurrent = list;
		while (bigcurrent->first != NULL) {
			smallcurrent = bigcurrent->first;
			bigcurrent->first = bigcurrent->first->next;
			delete smallcurrent;
		}
		list = bigcurrent->next;
		delete bigcurrent;
	}
}

int main() {
	setlocale(LC_ALL, "");
	init();
	int res = -1;
	while (res != 8) {
		cout << "1 - пустота списка" << endl;
		cout << "2 - состояние списка" << endl;
		cout << "3 - добавить подсписок в список" << endl;
		cout << "4 - добавить элемент в подсписок" << endl;
		cout << "5 - удалить подсписок из списка" << endl;
		cout << "6 - удалить элемент из подсписка" << endl;
		cout << "7 - поиск элемента" << endl;
		cout << "8 - выход" << endl;
		cin >> res;

		if (res == 8) {
			clean();
		}
		else if (res == 1) {
			if (is_big_empty()) {
				cout << "Список пуст" << endl;
			}
			else {
				cout << "Список не пуст" << endl;
			}
		}
		else if (res == 2) {
			print_list();
		}
		else if (res == 3) {
			add_samll_to_big();
		}
		else if (res == 4) {
			add_to_small();
		}
		else if (res == 5) {
			remove_small_from_big();
		}
		else if (res == 6) {
			remove_from_small();
		}
		else if (res == 7) {
			search();
		}
		else {
			cout << "некорректный ввод" << endl;
		}
	}
	return 0;
}

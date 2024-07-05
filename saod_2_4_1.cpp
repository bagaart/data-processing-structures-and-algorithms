#include <iostream>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define KEY_COUNT 10

const string keys[KEY_COUNT] = { "INCLUDE", "DEFINE", "END", "IF", "PRAGMA", "CASE", "ENUM", "SIGNED", "CONST", "START" };
string table[KEY_COUNT];

bool keyFound(const string& key) {
	for (int i = 0; i < KEY_COUNT; i++) {
		if (key == keys[i]) {
			return true;
		}
	}
	return false;
}

int getValue(const string& key) {
	int value = 0;
	for (int i = 0; i < key.length(); i++) {
		value += (int)key[i];
	}
	value %= KEY_COUNT;
	return value;
}

bool push(const string& key) {
	int value = 0;
	if (keyFound(key)) {
		value = getValue(key);
		if (key != table[value]) {
			table[value] = key;
			return true;
		}
		else {
			cout << "Элемент уже был добавлен" << endl;
		}
	}
	else {
		cout << "Неизвестный ключ" << endl;
	}
	return false;
}

void pop(const string& key) {
	int value = getValue(key);
	if (key == table[value]) {
		table[value] = "NULL";
		cout << "Элемент удален" << endl;
	}
	else {
		cout << "элемент не найден" << endl;
	}
}

void showTable() {
	cout << "Состояние хеш-таблицы" << endl;
	for (int i = 0; i < KEY_COUNT; i++) {
		cout << i << " : " << ((table[i] != " ") ? table[i] : "NULL") << endl;
	}
}

int main() {
	setlocale(LC_ALL, "");
	for (int i = 0; i < KEY_COUNT; i++) {
		table[i] = " ";
	}
	int filled = 0;
	while (true) {
		int n;
		cout << "1 - Добавить элемент в таблицу" << endl;
		cout << "2 - Поиск ключа в таблице" << endl;
		cout << "3 - Вывести состояние таблицы" << endl;
		cout << "4 - Удалить элемент из таблицы" << endl;
		cout << "5 - Выход из программы" << endl;
		cin >> n;
		if (n == 1) {
			if (filled < KEY_COUNT) {
				string key;
				cout << "Введите строку-ключ для добавления" << endl;
				cin >> key;
				if (push(key)) {
					filled++;
					cout << "Элемент добавлен" << endl;
				}
			}
			else {
				cout << "Таблица заполнена" << endl;
			}
		}
		else if (n == 2) {
			string key;
			cout << "Введите строку-ключ для поиска" << endl;
			cin >> key;
			int value = getValue(key);
			if (keyFound(key)) {
				cout << "Элемент найден в ячейке со значением " << value << endl;
			}
			else {
				cout << "Элемент не найден" << endl;
			}
		}
		else if (n == 3) {
			showTable();
		}
		else if (n == 4) {
			string key;
			cout << "Введите строку-ключ для поиска" << endl;
			cin >> key;
			pop(key);
		}
		else if (n == 5) {
			return 0;
		}
		else {
			cout << "Некорректная опреация" << endl;
		}
	}
	return 0;
} 
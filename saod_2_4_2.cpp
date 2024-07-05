#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int TABLE_SIZE = 10;
const int KEY_NUMBER = 10;

vector<string> keys = { "Akhmetgaleev", "Valiev", "Gataullin", "Gavrilov", "Shaidullin",
                        "Bagautdinov", "Abeydullov", "Gromov", "Safiullin", "Frantsuzov" };


int getValue(const string& key) {
    int value = 0;
    for (char c : key) {
        value += c;
    }
    return value % TABLE_SIZE;
}
bool keyFound(const string& key, vector<string>& table, int& comparisons) {
    int value = getValue(key);
    int i = 0;
    while (!table[value].empty()) {
        comparisons++;
        if (table[value] == key) {
            return true;
        }
        i++;
        value = (getValue(key) + i) % TABLE_SIZE;
    }
    return false;
}

bool push(vector<string>& table, const string& key, int& comparisons) {
    int value = getValue(key);
    int i = 0;
    while (!table[value].empty()) {
        comparisons++;
        if (table[value] == key) {
            cout << "Элемент уже присутствует в таблице" << endl;
            return false;
        }
        i++;
        value = (getValue(key) + i) % TABLE_SIZE;
    }
    table[value] = key;
    return true;
}

void pop(vector<string>& table, const string& key) {
    int value = getValue(key);
    int i = 0;
    while (!table[value].empty()) {
        if (table[value] == key) {
            table[value].clear();
            cout << "Элемент успешно удален" << endl;
            return;
        }
        i++;
        value = (getValue(key) + i) % TABLE_SIZE;
    }
    cout << "Элемент не найден" << endl;
}

void showTable(const vector<string>& table) {
    cout << "Состояние хеш-таблицы" << endl;
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << i << ") " << (table[i].empty() ? "NULL" : table[i]) << endl;
    }
}

int main() {
    setlocale(LC_ALL, "");
    vector<string> table(TABLE_SIZE);
    int comparisons = 0;
    while (true) {
        int n;
        cout << "1 - Добавить элемент в таблицу" << endl;
        cout << "2 - Поиск ключа в таблице" << endl;
        cout << "3 - Вывести состояние таблицы на экран" << endl;
        cout << "4 - Удалить элемент из таблицы" << endl;
        cout << "0 - Выход из программы" << endl;
        cin >> n;
        if (n == 1){
            string key;
            cout << "Введите строку-ключ для добавления: ";
            cin >> key;
            comparisons = 0;
            if (push(table, key, comparisons)) {
                cout << "Элемент добавлен. Количество сравнений: " << comparisons << endl;
            }
            else {
                cout << "Не удалось добавить элемент" << endl;
            }
        }
        else if (n == 2) {
            string key;
            cout << "Введите строку-ключ для поиска: ";
            cin >> key;
            comparisons = 0;
            if (keyFound(key, table, comparisons)) {
                cout << "Элемент найден. Количество сравнений: " << comparisons << endl;
            }
            else {
                cout << "Элемент не найден. Количество сравнений: " << comparisons << endl;
            }
        }
        else if (n == 3) {
            showTable(table);
        }
        else if (n == 4) {
            string key;
            cout << "Введите строку-ключ для удаления: ";
            cin >> key;
            pop(table, key);
        }
        else if (n == 0) {
            return 0;
        }
        else {
            cout << "Неизвестная операция, повторите попытку" << endl;
        }
    }
}
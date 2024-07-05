#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

#define TABLE_SIZE 10
#define KEY_NUMBER 10

list<string> hashTable[TABLE_SIZE];

const vector<string> keys = { "Akhmetgaleev", "Valiev", "Gataullin", "Gavrilov", "Shaidullin",
                                       "Bagautdinov", "Abeydullov", "Gromov", "Safiullin", "Frantsuzov" };

int getValue(const string& key) {
    int value = 0;
    for (char c : key) {
        value += (int)c;
    }
    return value % TABLE_SIZE;
}

bool push(const string& key) {
    int index = getValue(key);

    for (const auto& element : hashTable[index]) {
        if (element == key) {
            std::cout << "Элемент с таким ключом уже существует\n";
            return false;
        }
    }

    hashTable[index].push_back(key);
    return true;
}

bool keyFound(const string& key, int* comparisons) {
    int index = getValue(key);

    for (const auto& element : hashTable[index]) {
        (*comparisons)++;
        if (element == key) {
            return true;
        }
    }
    return false;
}

void pop(const string& key) {
    int index = getValue(key);

    for (auto it = hashTable[index].begin(); it != hashTable[index].end(); ++it) {
        if (*it == key) {
            hashTable[index].erase(it);
            std::cout << "Элемент успешно удален\n";
            return;
        }
    }
    std::cout << "Элемент не найден\n";
}

void showTable() {
    cout << "Состояние хеш-таблицы\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << i << ") ";
        for (const auto& element : hashTable[i]) {
            cout << element << " ";
        }
        cout << "\n";
    }
}

int main() {
    setlocale(LC_ALL, "");
    while (true) {
        int n;
        cout << "1 - Добавить элемент в таблицу\n";
        cout << "2 - Поиск ключа в таблице\n";
        cout << "3 - Вывести состояние таблицы на экран\n";
        cout << "4 - Удалить элемент из таблицы\n";
        cout << "0 - Выход из программы\n";
        cin >> n;
        switch (n) {
        case 1: {
            string key;
            cout << "Введите строку-ключ для добавления: ";
            cin >> key;
            int comparisons = 0;
            if (push(key)) {
                cout << "Элемент добавлен\n";
            }
            else {
                cout << "Не удалось добавить элемент\n";
            }
            break;
        }
        case 2: {
            string key;
            cout << "Введите строку-ключ для поиска: ";
            cin >> key;
            int comparisons = 0;
            if (keyFound(key, &comparisons)) {
                cout << "Элемент найден. Количество сравнений: " << comparisons << "\n";
            }
            else {
                cout << "Элемент не найден. Количество сравнеий: " << comparisons << "\n";
            }
            break;
        }
        case 3: {
            showTable();
            break;
        }
        case 4: {
            string key;
            cout << "Введите строку-ключ для удаления: ";
            cin >> key;
            pop(key);
            break;
        }
        case 0: {
            return 0;
        }
        default:
            cout << "Неизвестная операция, повторите попытку\n";
            break;
        }
    }
}

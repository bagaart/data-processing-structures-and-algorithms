#include <iostream>
#include <locale.h>
#define SIZE 10
using namespace std;

typedef struct Node {
    int data;
    int iparent;
    struct Node* next_sibl;
} Node;

typedef struct Tree {
    Node* nodes[SIZE];
    int size;
} Tree;

void initTree(Tree* tree, int root_data) {
    tree->size = 0;
    tree->nodes[0] = new Node;
    if (tree->nodes[0] == NULL) {
        cout << "Память не выделилась" << endl;
        exit(1);
    }
    tree->nodes[0]->data = root_data;
    tree->nodes[0]->iparent = -1;
    tree->nodes[0]->next_sibl = NULL;
    tree->size++;
}

void addChild(Tree* tree, int parent_data, int data) {
    int iparent = -1;
    for (int i = 0; i < tree->size; i++) {
        if (tree->nodes[i] != NULL && tree->nodes[i]->data == parent_data) {
            iparent = i;
            break;
        }
    }

    if (iparent == -1) {
        cout << "Вершина " << parent_data << " не найдена" << endl;
        return;
    }

    if (tree->size >= SIZE) {
        cout << "Размер дерева максимален" << endl;
        return;
    }

    Node* new_node = new Node;
    if (new_node == NULL) {
        cout << "Память не выделилась" << endl;
        exit(1);
    }

    new_node->data = data;
    new_node->iparent = iparent;
    new_node->next_sibl = NULL;

    if (tree->nodes[iparent] == NULL) {
        tree->nodes[iparent] = new_node;
    }
    else {
        Node* current = tree->nodes[iparent];
        while (current->next_sibl != NULL) {
            current = current->next_sibl;
        }
        current->next_sibl = new_node;
    }
    tree->nodes[tree->size++] = new_node;
}

void printTree(Tree* tree) {
    if (tree->size == 0) {
        cout << "Дерево пустое" << endl;
        return;
    }
    cout << "Вершины дерева" << endl;
    for (int i = 0; i < tree->size; i++) {
        Node* node = tree->nodes[i];
        if (node != NULL) {
            if (node->iparent == -1) {
                cout << "Вершина " << node->data << " (Корень)" << endl;;
            }
            else {
                cout << "Вершина " << node->data << " (Родитель " << tree->nodes[node->iparent]->data << ")" << endl;
            }
        }
    }
}

int findNode(Tree* tree, int data) {
    for (int i = 0; i < tree->size; i++) {
        Node* node = tree->nodes[i];
        if (node != NULL && node->data == data) {
            return i;
        }
    }
    return -1;
}

void removeNode(Tree* tree, int data) {
    int index = findNode(tree, data);
    if (index != -1) {
        Node* node_to_remove = tree->nodes[index];

        if (node_to_remove->iparent != -1) {
            Node* parent = tree->nodes[node_to_remove->iparent];
            if (parent != NULL) {
                if (parent->next_sibl == node_to_remove) {
                    parent->next_sibl = node_to_remove->next_sibl;
                }
            }
        }

        while (node_to_remove != NULL) {
            Node* next_sibling = node_to_remove->next_sibl;
            delete node_to_remove;
            node_to_remove = next_sibling;
            tree->size--;
        }

        tree->nodes[index] = NULL;
        cout << "Вершина удалена" << endl;
    }
    else {
        cout << "Вершина не найдена" << endl;
    }
}

void clearTree(Tree* tree) {
    for (int i = 0; i < tree->size; i++) {
        delete tree->nodes[i];
    }
    tree->size = 0;
}

int main() {
    setlocale(LC_ALL, "");
    Tree* tree = new Tree;
    tree->size = 0;
    int choice;
    int parent_data, data, search_data, num_elements;
    int search_result;

    do {
        cout << "1 - Добавить вершину" << endl;
        cout << "2 - Удалить вершину" << endl;
        cout << "3 - Найти вершину" << endl;
        cout << "4 - Вывести дерево" << endl;
        cout << "5 - Выйти" << endl;
        cin >> choice;

        if (choice == 1) {
            if (tree->size == 0) {
                cout << "Дерево пустое. Введите значение корня" << endl;
                cin >> parent_data;
                initTree(tree, parent_data);
            }
            else {
                cout << "Введите значение родителя" << endl;;
                cin >> parent_data;
                cout << "Введите значение новой вершины" << endl;
                cin >> data;
                addChild(tree, parent_data, data);
            }
        }
        else if (choice == 2) {
            cout << "Введите значение вершины для удаления" << endl;
            cin >> data;
            removeNode(tree, data);
        }
        else if (choice == 3) {
            cout << "Введите значение вершины для поиска" << endl;
            cin >> search_data;
            search_result = findNode(tree, search_data);
            if (search_result != -1) {
                cout << "Вершина найдена на позиции " << search_result << endl;
            }
            else {
                cout << "Вершина не найдена" << endl;
            }
        }
        else if (choice == 4) {
            printTree(tree);
        }
        else if (choice == 5) {
            clearTree(tree);
            cout << "Выход из программы" << endl;
        }
        else {
            cout << "Некорректный ввод" << endl;
        }
    } while (choice != 5);

    delete tree;
    return 0;
}
#include <iostream>
#include <ctime>
#include <locale.h>

using namespace std;

typedef struct Node {
    int data;
    Node* left;
    Node* right;
} Node;

typedef struct Stack {
    int level;
    Node* node;
    struct Stack* next;
}Strcut;

Node* add(Node* current, int n) {
    if (n == 0) {
        return nullptr;
    }
    else {
        int left = n / 2;
        int right = n - left - 1;
        Node* tmp = new Node;
        tmp->data = rand() % 100;
        tmp->left = add(tmp->left, left);
        tmp->right = add(tmp->right, right);
        return tmp;
    }
}

void strai(Node* node, int level) {
    if (node != nullptr) {
        for (int i = 0; i < level * 5; i++) {
            cout << " ";
        }
        cout << node->data << endl;
        strai(node->left, level + 1);
        strai(node->right, level + 1);
    }
}

void sim(Node* node, int level) {
    if (node != nullptr) {
        sim(node->left, level + 1);
        for (int i = 0; i < level * 5; i++) {
            cout << " ";
        }
        cout << node->data << endl;
        sim(node->right, level + 1);
    }
}

void asim(Node* node, int level) {
    if (node != nullptr) {
        asim(node->right, level + 1);
        for (int i = 0; i < level * 5; i++) {
            cout << " ";
        }
        cout << node->data << endl;
        asim(node->left, level + 1);
    }
}

void sim_cyc(Node* root) {
    if (root == NULL) {
        return;
    }

    Stack* stack = NULL, *newstack = NULL;
    Node* current = root;
    int level{ -1 };
    while (current != NULL || stack != NULL) {
        while (current != NULL) {
            level++;
            newstack = new Stack;
            newstack->node = current;
            newstack->level = level;
            newstack->next = stack;
            stack = newstack;
            current = current->left;
        }
        if (stack != NULL) {
            newstack = stack;
            current = newstack->node;
            level = newstack->level;
            stack = newstack->next;
            for (int i = 0; i < level * 5; i++) cout << " ";
            cout << current->data << endl;
            current = current->right;
            delete newstack;
        }
    }

}

void remove(Node* node) {
    if (node != nullptr) {
        remove(node->left);
        remove(node->right);
        delete node;
    }
}

int main() {
    setlocale(LC_ALL, "");

    srand(time(0));

    int numNodes;
    cout << "Введите количество вершин для построения: ";
    cin >> numNodes;

    Node* root = add(nullptr, numNodes);

    cout << "\nПрямой вывод:\n";
    strai(root, 0);

    cout << "\nСимметричный рекурсивынй вывод:\n";
    sim_cyc(root);

    cout << "\nСимметричный вывод:\n";
    sim(root, 0);

    cout << "\nОбратно-симметричный вывод:\n";
    asim(root, 0);

    remove(root);
    root = nullptr;

    return 0;
}
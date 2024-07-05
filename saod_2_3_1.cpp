#include <iostream>
#include <ctime>

using namespace std;


int* arr = nullptr;
int asize = 0;
int mkey = 0;

struct List {
	int key = -1;
	List* next = nullptr;
	List* tail = nullptr;
} *ls = nullptr, *head = nullptr;

void show(int* ar) {
	for (int i = 0; i < asize; i++) {
		cout << ar[i] << " ";
	}
	cout << endl;
}

int* copy_arr() {
	int* narr = new int[asize];
	for (int i = 0; i < asize; i++) {
		narr[i] = arr[i];
	}
	return narr;
}

void create(int n) {
	asize = 0;
	cout << "Введите размер массива" << endl;
	cin >> asize;
	if (arr != nullptr) delete[] arr;
	arr = new int[asize];
	if (n == 1) {
		for (int i = 0; i < asize; i++)
			arr[i] = i;
		mkey = asize;
	}
	else if (n == 2) {
		mkey = asize - asize / 3;
		for (int i = 0; i < mkey; i++) {
			arr[i] = i;
		}
		for (int i = mkey; i < asize; i++) {
			arr[i] = rand() % mkey;
		}
	}
	int temp, r;
	for (int i = 0; i < asize; i++) {
		r = rand() % asize;
		temp = arr[i];
		arr[i] = arr[r];
		arr[r] = temp;
	}
	cout << "Созданный массив" << endl;
	show(arr);
	cout << endl;
}

void pocketSort() {
	create(1);
	int* copy = copy_arr();
	int temp, n = -1;
	cout << "1 - Использовать второй массив" << endl;
	cout << "2 - Не использовать второй массив" << endl;
	cin >> n;
	if (n == 1) {
		int* sub = new int[asize];
		for (int i = 0; i < asize; i++) {
			sub[copy[i]] = copy[i];
		}
		delete[] copy;
		copy = sub;
	}
	else {
		for (int i = 0; i < asize; i++) {
			while (copy[i] != i) {
				temp = copy[copy[i]];
				copy[copy[i]] = copy[i];
				copy[i] = temp;
			}
		}
	}
	cout << "Отсортированный массив" << endl;
	show(copy);
	delete[] copy;
}

void clean(List* list) {
	if (list->next != nullptr) {
		clean(list->next);
	}
	delete list;
}

int* listToarr(List* list) {
	List* current = list;
	int* mas = new int[asize];
	for (int i = 0; i < asize; i++) {
		mas[i] = current->key;
		current = current->next;
	}
	return mas;
}

List* combine(List* list) {
	List* hd = new List;
	hd->key = list[0].key;
	hd->next = list[0].next;
	hd->tail = list[0].next;
	List* current = hd;
	for (int i = 0; i < mkey - 1; i++) {
		if (list[i].tail != nullptr) {
			current = list[i].tail;
		}
		current->next = new List;
		current = current->next;
		current->key = list[i + 1].key;
		current->next = list[i + 1].next;
		current->tail = list[i + 1].tail;
	}
	return hd;
}

void generalSort() {
	create(2);
	int* copy = copy_arr();
	ls = new List[mkey];
	for (int i = 0; i < asize; i++) {
		if (ls[copy[i]].key == -1) {
			ls[copy[i]].key = copy[i];
		}
		else if (ls[copy[i]].next == nullptr) {
			ls[copy[i]].next = new List;
			ls[copy[i]].tail = ls[copy[i]].next;
			ls[copy[i]].next->key = copy[i];
		}
		else if (ls[copy[i]].tail->next == nullptr) {
			ls[copy[i]].tail->next = new List;
			ls[copy[i]].tail->next->key = copy[i];
			ls[copy[i]].tail = ls[copy[i]].tail->next;
		}
	}

	head = combine(ls);
	delete[] copy;
	copy = listToarr(head);
	clean(head);
	head = nullptr;
	cout << "Отсортированный массив" << endl;
	show(copy);
	delete[] copy;
	delete[] ls;
}

void radixSort() {
	create(2);
	int* copy = copy_arr();
	int k = 0, temp = mkey;
	while (temp != 0) {
		temp = temp / 10;
		k++;
	}

	cout << "\n ЧИСЛО РАЗРЯДОВ: " << k << "\n";
	int x, _max;
	for (int i = 1; i <= k; i++) {
		ls = new List[10];
		for (int j = 0; j < asize; j++) {
			x = copy[j];
			for (int z = 1; z < i; z++)
				x = x / 10;
			x = x % 10;

			if (ls[x].key == -1)
				ls[x].key = copy[j];
			else if (ls[x].next == NULL) {
				ls[x].next = new List;
				ls[x].tail = ls[x].next;
				ls[x].next->key = copy[j];
			}
			else if (ls[x].tail->next == NULL) {
				ls[x].tail->next = new List;
				ls[x].tail->next->key = copy[j];
				ls[x].tail = ls[x].tail->next;
			}
		}
		_max = mkey;
		mkey = 10;
		head = combine(ls);
		mkey = _max;
		copy = listToarr(head);
		clean(head);
		head = NULL;
		delete[] ls;
	}
	cout << "Отсортированный массив" << endl;
	show(copy);
	delete[] copy;
}

int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));
	int n;
	while (true) {
		n = -1;
		cout << "1 - Простейшая карманная" << endl;
		cout << "2 - Обобщенная карманная" << endl;
		cout << "3 - Поразрядная сортировка" << endl;
		cout << "4 - Выход" << endl;
		cin >> n;
		if (n == 1) {
			pocketSort();
		}
		else if (n == 2) {
			generalSort();
		}
		else if (n == 3) {
			radixSort();
		}
		else {
			break;
		}
	}
	delete[] arr;
	return 0;
}
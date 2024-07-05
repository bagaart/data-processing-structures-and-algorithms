#include <iostream>
#include <ctime>
#include <locale.h>

using namespace std;

int array_size = 0;

int* create_array() {
	srand(time(NULL));
	int* array = new int[array_size];
	for (int i = 0; i < array_size; i++) {
		array[i] = -10000 + rand() % 20001;
	}
	return array;
}


void print_array(int* array) {
	for (int i = 0; i < array_size; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

int* copy_array(int* src) {
	int* dst = new int[array_size];
	for (int i = 0; i < array_size; i++) {
		dst[i] = src[i];
	}
	return dst;
}

int comparess = 0;
int changess = 0;

void quick_sort(int left, int right, int* array, int size) {
	int i, j, sred, temp;
	if (left >= right)
		return;

	i = left;
	j = right;
	sred = array[(left + right) / 2];

	do {
		while (comparess++ && array[i] < sred) {
			i++;
		}
		while (comparess++ && array[j] > sred) {
			j--;
		}
		comparess++;
		if (i <= j) {
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			i++;
			j--;
			changess++;
		}
		
	} while (i <= j);
	if (left < j)
		quick_sort(left, j, array, size);
	if (i < right)
		quick_sort(i, right, array, size);

	if (left == 0 && right == (size - 1)) {
		cout << "Количество сравнений - " << comparess << endl;
		cout << "Количество перестановок - " << changess << endl;
		print_array(array);
	}
}


void heapify(int* array, int size, int i, int* compares, int* changes) {
	int large = i;

	int left = 2 * i + 1;
	int right = 2 * i + 2;

	(*compares)++;
	if (left < size && array[left] > array[large]) {
		large = left;
	}
	(*compares)++;
	if (right < size && array[right] > array[large]) {
		large = right;
	}

	if (large != i) {
		int temp = array[i];
		array[i] = array[large];
		array[large] = temp;
		(*changes)++;

		heapify(array, size, large, compares, changes);
	}
}

void heap_sort(int* array) {
	if (array == NULL || array_size == 0) {
		cout << "Массив пуст" << endl;
		return;
	}

	int compares = 0;
	int changes = 0;
	int* copy_ar = copy_array(array);
	for (int i = array_size / 2 - 1; i >= 0; i--) {
		heapify(copy_ar, array_size, i, &compares, &changes);
	}
	for (int i = array_size - 1; i > 0; i--) {
		int tmp = copy_ar[0];
		copy_ar[0] = copy_ar[i];
		copy_ar[i] = tmp;
		changes++;
		heapify(copy_ar, i, 0, &compares, &changes);
	}
	cout << "Количество сравнений - " << compares << endl;
	cout << "Количество перестановок - " << changes << endl;
	print_array(copy_ar);

	delete[] copy_ar;
}

int gaps[] = { 1, 4, 10, 23, 57, 132, 301, 701 };

void shell_sort(int *array, int step){
	if (array == NULL || array_size == 0) {
		cout << "Массив пуст" << endl;
		return;
	}
	int i, j;
	int compares = 0;
	int changes = 0;
	int* copy_ar = copy_array(array);
	for (int m = 0; m < step; m++) {
		int gap = gaps[m];
		while (gap >= 1) {
			for (i = gap; i < array_size; i++) {
				int temp = copy_ar[i];
				changes++;
				for (j = i; j >= gap && copy_ar[j - gap] > temp; j -= gap) {
					copy_ar[j] = copy_ar[j - gap];
					compares++;
					changes++;
				}
				copy_ar[j] = temp;
				changes++;
			}
			gap /= 2;
		}
	}

	cout << "Количество сравнений - " << compares << endl;
	cout << "Количество перестановок - " << changes / 3 << endl;
	print_array(copy_ar);

	delete[] copy_ar;
}


int main() {
	setlocale(LC_ALL, "");
	int choice = -1;
	int* array = NULL;

	while (choice != 7) {
		cout << "1 - Создать массив" << endl;
		cout << "2 - Очистить массив" << endl;
		cout << "3 - Вывести массив" << endl;
		cout << "4 - Сортировка быстрая" << endl;
		cout << "5 - Сортировка кучей" << endl;
		cout << "6 - Сортировка Шелла" << endl;
		cout << "7 - Выход" << endl;

		cin >> choice;
		if (choice == 1) {
			if (array == NULL) {
				cout << "Введите размер массива" << endl;
				cin >> array_size;
				array = create_array();
			}
			else {
				delete[] array;
				array = NULL;
				cout << "Введите размер массива" << endl;
				cin >> array_size;
				array = create_array();
			}
		}
		else if (choice == 2) {
			if (array != NULL) {
				delete[] array;
				array = NULL;
			}
			else {
				cout << "Массив уже пуст" << endl;
			}
		}
		else if (choice == 3) {
			if (array != NULL) {
				print_array(array);
			}
			else {
				cout << "Массив пуст" << endl;
			}
		}
		else if (choice == 4) {
			if (array != NULL) {
				changess = 0;
				comparess = 0;
				int* copy_ar = copy_array(array);
				quick_sort(0, array_size - 1, copy_ar, array_size);
				delete[] copy_ar;
			}
			else {
				cout << "Массив пуст" << endl;
			}
		}
		else if (choice == 5) {
			if (array != NULL) {
				heap_sort(array);
			}
			else {
				cout << "Массив пуст" << endl;
			}
		}
		else if (choice == 6) {
			if (array != NULL) {
				int step;
				cout << "Введите количество шагов" << endl;
				cin >> step;
				shell_sort(array, step);
			}
			else {
				cout << "Массив пуст" << endl;
			}
		}
		else if (choice == 7) {
			delete[] array;
			array = NULL;
			exit(0);
		}
		else {
			cout << "Некорректный ввод" << endl;
		}
	}
	return 0;
}

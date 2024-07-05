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

void selection_sort(int* array) {
	if (array == NULL || array_size == 0) {
		cout << "Массив пуст" << endl;
		return;
	}

	int compares = 0;
	int changes = 0;
	int* copy_ar = copy_array(array);

	for (int i = 0; i < array_size - 1; ++i) {
		int min_index = i;
		for (int j = i + 1; j < array_size; ++j) {
			compares++;
			if (copy_ar[j] < copy_ar[min_index]) {
				min_index = j;
			}
		}
		if (min_index != i) {
			int temp = copy_ar[i];
			copy_ar[i] = copy_ar[min_index];
			copy_ar[min_index] = temp;
			changes++;
		}
	}

	cout << "Количество сравнений - " << compares << endl;
	cout << "Количество перестановок - " << changes << endl;
	print_array(copy_ar);
	delete[] copy_ar;
	copy_ar = NULL;
}

void insert_sort(int* array) {
	if (array == NULL || array_size == 0) {
		cout << "Массив пуст" << endl;
		return;
	}
	int compares = 0;
	int changes = 0;
	int *copy_ar = copy_array(array);

	for (int i = 1; i < array_size; i++) {
		int temp = copy_ar[i];
		changes++;
		int j = i - 1;
		while (compares++ && j >= 0 && temp < copy_ar[j]) {
			copy_ar[j + 1] = copy_ar[j];
			changes++;
			j--;
		}
		copy_ar[j + 1] = temp;
		changes++;
	}
	cout << "Количество сравнений - " << compares << endl;
	cout << "Количество перестановок - " << changes / 3 << endl;
	print_array(copy_ar);
	delete[] copy_ar;
	copy_ar = NULL;
}

void bubble_sort(int* array) {
	if (array == NULL || array_size == 0) {
		cout << "Массив пуст" << endl;
		return;
	}
	int compares = 0;
	int changes = 0;
	int* copy_ar = copy_array(array);

	for (int i = 0; i < array_size - 1; ++i) {
		for (int j = 0; j < array_size - i - 1; ++j) {
			compares++;
			if (copy_ar[j] > copy_ar[j + 1]) {
				int temp = copy_ar[j];
				copy_ar[j] = copy_ar[j + 1];
				copy_ar[j + 1] = temp;
				changes++;
			}
		}
	}
	cout << "Количество сравнений - " << compares << endl;
	cout << "Количество перестановок - " << changes << endl;
	print_array(copy_ar);
	delete[] copy_ar;
	copy_ar = NULL;
}

int main() {
	setlocale(LC_ALL, "");
	int choice = -1;
	int* array = NULL;
	while (choice != 8) {
		cout << "1 - Создать массив" << endl;
		cout << "2 - Очистить массив" << endl;
		cout << "3 - Вывести массив" << endl;
		cout << "4 - Сортировка обменом" << endl;
		cout << "5 - Сортировка вставками" << endl;
		cout << "6 - Сортировка выбором" << endl;
		cout << "7 - Все три" << endl;
		cout << "8 - Выход" << endl;

		cin >> choice;
		if (choice == 1) {
			if (array == NULL) {
				cout << "Введите размер массива" << endl;
				cin >> array_size;
				array = create_array();
			} else{
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
				bubble_sort(array);
			}
			else {
				cout << "Массив пуст" << endl;
			}
		}
		else if (choice == 5) {
			if (array != NULL) {
				insert_sort(array);
			}
			else {
				cout << "Массив пуст" << endl;
			}
		}
		else if (choice == 6) {
			if (array != NULL) {
				selection_sort(array);
			}
			else {
				cout << "Массив пуст" << endl;
			}
		}
		else if (choice == 7) {
			if (array != NULL) {
				cout << "Сортировка обменом" << endl;
				bubble_sort(array);
				cout << "Сортировка вставками" << endl;
				insert_sort(array);
				cout << "Сортировка выбором" << endl;
				selection_sort(array);
			}
			else {
				cout << "Массив пуст" << endl;
			}
		}
		else if (choice == 8) {
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

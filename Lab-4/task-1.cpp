#include <iostream> 
#include <algorithm>
#include <windows.h>
using namespace std;

//Сортировка выбором
void selectionSort(int arr[], int n) {
	int i, j, min_idx;

	// от начала передвигаем границу несортированного подмассива  
	for (i = 0; i < n - 1; i++) {
		// находимв минимальный элемент в неотсортированном подмассиве  
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		// ставим минимальный найденные элемент в первую ячейку неотсортированного подмассива
		swap(arr[min_idx], arr[i]);
	}
}
// Сортировка вставками
void insertionSort(int arr[], int n) {
	int i, key, j;
	for (i = 1; i < n; i++) {
		//запоминаем элемент ключа
		key = arr[i];
		j = i - 1;

		// перемещаем все элементы от начала до ключа на одну позицию вправо
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		//вставляем элемент ключа
		arr[j + 1] = key;
	}
}
//Сортировкка обменами
void bubbleSort(int arr[], int n) {
	int i, j;
	for (i = 0; i < n - 1; i++) {
		// сравниваем каждые пары элементов, и в случае необходимости меняя их местами меняя их 
		// местами в порядке возрастания. В конце будет образовываться отсортированный подмассив
		for (j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}
//Быстрая сортировка
int partition(int arr[], int low, int high) {
	int pivot = arr[high]; // опорный элемент  
	int i = (low - 1); // индекс

	for (int j = low; j <= high - 1; j++) {
		// если текущий элемент меньше чем индекс разбиения
		if (arr[j] < pivot) {
			i++; // увеличиваем индекс меньших элементов
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}


// low --> начало интервала разбиения,
// high --> конец интервала разбиения 
void quickSort(int arr[], int low, int high) {
	if (low < high) {
		// pi --> индекс разбиения
		int pi = partition(arr, low, high);

		// разделяем на два подмассива  
		// до и после индекса разбиения
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}
// Интроспективная сортировка
void InsertionSort(int arr[], int *begin, int *end) {
	// Получаем левый и правый индекс подмассива для сортировки
	int left = begin - arr;
	int right = end - arr;

	for (int i = left + 1; i <= right; i++) {
		int key = arr[i];
		int j = i - 1;

		//сдвигаем все элементы больше ключа на одну позицию вперёд
		while (j >= left && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}
int* Partition(int arr[], int low, int high) {
	int pivot = arr[high];    // опорный элемент 
	int i = (low - 1);  // индекс меньшего элемента

	for (int j = low; j <= high - 1; j++) {
		// если текущий элемент <= опорному
		if (arr[j] <= pivot) {
			// увеличиваем индекс меньшего элемента
			i++;

			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return (arr + i + 1);
}
//выбираем опорный элемент
int *MedianOfThree(int * a, int * b, int * c) {
	if (*a < *b  && *b < *c) return (b);
	if (*a < *c  && *c <= *b)return (c);
	if (*b <= *a && *a < *c) return (a);
	if (*b < *c  && *c <= *a)return (c);
	if (*c <= *a && *a < *b) return (a);
	if (*c <= *b && *b <= *a)return (b);
}
void IntrosortUtil(int arr[], int * begin, int * end, int depthLimit) {
	// считаем количество элементов в разбиении
	int size = end - begin;

	//	если элементов в интервале мало, не делим больше на участки и сортируем вставками
	if (size < 16) {
		InsertionSort(arr, begin, end);
		return;
	}

	// если достигли нулевой глубины, но используем пирамиду
	if (depthLimit == 0) {
		make_heap(begin, end + 1);
		sort_heap(begin, end + 1);
		return;
	}

	// выбираем неподвижный элемент "медианой из трёх"
	int * pivot = MedianOfThree(begin, begin + size / 2, end);

	swap(pivot, end);

	// используем быструю сортировку
	int * partitionPoint = Partition(arr, begin - arr, end - arr);
	IntrosortUtil(arr, begin, partitionPoint - 1, depthLimit - 1);
	IntrosortUtil(arr, partitionPoint + 1, end, depthLimit - 1);
}
void Introsort(int arr[], int *begin, int *end) {
	// предел выполнения быстрой сортировки
	int depthLimit = 2 * log(end - begin);

	// рекурсивно выполняем сортировку
	IntrosortUtil(arr, begin, end, depthLimit);
}
/////////////////////////////////////////////////////////////////////

void mcopy(int arr1[], int arr2[], int n) {
	for (int i = 0; i < n; i++) {
		arr1[i] = arr2[i];
	}
}
void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
/////////////////////////////////////////////////////////////////////
int main() {
	SetConsoleOutputCP(1251);
	int n;
	cout << "Enter size: ";
	cin >> n;
	int* array = new int[n];
	cout << "Enter all elements:\n";
	for (int i = 0; i < n; i++) {
		cin >> array[i];
	}

	int* tempArray = new int[n];
	for (int i = 0; i < n; i++) {
		tempArray[i] = array[i];
	}
	/////////////////////////////////////////////////////////////
	printArray(array, n);
	cout << endl << "Selection sort: " << endl;
	selectionSort(array, n);
	printArray(array, n);

	cout << endl << "Mix elements: " << endl;
	mcopy(array, tempArray, n);
	printArray(array, n);
	cout << "Insertion sort: " << endl;
	insertionSort(array, n);
	printArray(array, n);

	cout << endl << "Mix elements: " << endl;
	mcopy(array, tempArray, n);
	printArray(array, n);
	cout << "Bubble sort: " << endl;
	bubbleSort(array, n);
	printArray(array, n);

	cout << endl << "Mix elements: " << endl;
	mcopy(array, tempArray, n);
	printArray(array, n);
	cout << "Quicksort: " << endl;
	quickSort(array, 0, n - 1);
	printArray(array, n);

	cout << endl << "Mix elements: " << endl;
	mcopy(array, tempArray, n);
	printArray(array, n);
	cout << "Introsort: " << endl;
	Introsort(array, array, array + n - 1);
	printArray(array, n);

	system("pause");
	return(0);
}

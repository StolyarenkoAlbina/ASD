// Разделяй и властвуй
#include <iostream>
using namespace std;

// функция нахождения наибольшего подмассива при слиянии левой и правой части
int* FindMaxCrossingSubArray(int *array, int low, int mid, int high) {
	int LeftSum = INT_MIN;
	int sum = 0;
	int maxLeft;

	// находим сумму элементов левой части
	// запоминая индекс ключевого элемента
	for (int i = mid; i >= low; i--) {
		sum += array[i];
		if (sum > LeftSum) {
			LeftSum = sum;
			maxLeft = i;
		}
	}

	int RighSum = INT_MIN;
	int maxRight = 0;
	sum = 0;

	// повторяем операцию для правой части
	for (int j = mid + 1; j <= high; j++) {
		sum += array[j];
		if (sum > RighSum) {
			RighSum = sum;
			maxRight = j;
		}
	}

	// возвращам оптимальный интервал левой части, оптимальный интервал правой части, и их сумму
	int SomeArray[3];
	SomeArray[0] = maxLeft;
	SomeArray[1] = maxRight;
	SomeArray[2] = LeftSum + RighSum;
	return SomeArray;
}

// функция нахождения максимального под.массива
int* FindMaxSubArray(int *array, int low, int high) {
	// если в под-массиве всего один элемент
	if (high == low) {
		int *Arr4 = new int[3];
		Arr4[0] = low;
		Arr4[1] = high;
		Arr4[2] = array[low];
		return (Arr4);
	}
	// если в массиве больше одного элемента
	else {
		// находим середину этого массива
		int mid = (low + high) / 2;
		// создаём временные массивы для хранения результата последующих вычислений
		int *Arr1 = new int[3];
		int *Arr2 = new int[3];
		int *Arr3 = new int[3];
		// находим наибольшие массивы среди:
		//		1:	слева от центра
		//		2:	справа от центра
		//		3:	смеси левой и правой частей
		Arr1 = FindMaxSubArray(array, low, mid);
		Arr2 = FindMaxSubArray(array, (mid + 1), high);
		Arr3 = FindMaxCrossingSubArray(array, low, mid, high);
		// выбираем случай, который больше и возвращаем его
		if (Arr1[2] >= Arr2[2] && Arr1[2] >= Arr3[2]) return (Arr1);
		else if (Arr2[2] >= Arr1[2] && Arr2[2] >= Arr3[2]) return (Arr2);
		else return (Arr3);
	}

}
int main() {
	// выбираем количество дней
	const int n = 17;
	if (n <= 1) {

		cout << "Error" << endl;
		system("pause");
	}
	// индекс последнего дня
	const int k = n - 1;
	// индекс центрального дня
	int mid = k / 2;
	// массив изменения цен между днями
	int Array[k];
	// массив цен на каждый день
	int ArrayWithCost[n] = { 99,111,100,88,155,112,77,66,81,101,94,166,111,55,44,90,97 };

	// заполняем массив изменения цены (и выводим на экран)
	for (int i = 0; i < k; i++) {
		Array[i] = ArrayWithCost[i + 1] - ArrayWithCost[i];
		cout << Array[i] << " ";
	}
	cout << endl;


	// массив результата:
	//		[0]:	номер дня покупки акций
	//		[1]:	номер дня продажи акций
	//		[2]:	прибыль
	int *Arr6 = new int[3];
	Arr6 = FindMaxSubArray(Array, 0, k);
	cout <<"Day of purchase: "<< Arr6[0] + 1 << endl;
	Arr6 = FindMaxSubArray(Array, 0, k);
	cout <<"Sale day: "<< Arr6[1] + 2 << endl;
	Arr6 = FindMaxSubArray(Array, 0, k);
	cout <<"Earnings: "<< Arr6[2] << endl;

	system("pause");
	return 0;
}

// Диски в коробках
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

double distance(int R1, int R2) {
	return sqrt((R1 + R2)*(R1 + R2) - fabs(R1 - R2)*fabs(R1 - R2));
}

int main() {
	// Вводим количество дисков
	int n;
	cout << "Enter number of disks:";
	cin >> n;

	// Создаём массивы, хранящие радиусы дисков, растояния между ними и набор, хранящий оптимальный вариант
	int *Radius = new int[n];
	double *ArrayWithDistanceBetweenDisks = new double[n - 1];
	double *ArrayWithSaveIndex = new double[n];

	// переменные длины каждой раскладки и длины оптимальной раскладки
	double sum = 0;
	double min = INT_MAX;

	// заполняем массивы
	cout << "Enter size of discs:" ;
	for (int i = 0; i < n; i++) {
		cout << i + 1 << ":";
		cin >> Radius[i];
		cout << endl;
	}

	// сортируем диски в порядке возрастания радиуса
	sort(Radius, Radius + n);
	do {
		// выводим последовательность раскладки
		for (int i = 0; i < n; i++) {
			cout << Radius[i] << " ";
		}
		cout << endl;

		// находим растояния между дисками и сумму растояний
		for (int i = 1; i < n; i++) {
			ArrayWithDistanceBetweenDisks[i - 1] = distance(Radius[i - 1], Radius[i]);
			sum += ArrayWithDistanceBetweenDisks[i - 1];
		}

		// добавляем края и выводим сумму
		sum += Radius[0] + Radius[n - 1];
		cout << sum << endl << endl;

		// если сумма меньше минимальной, то сохраняем раскладку
		if (sum < min) {
			min = sum;
			for (int i = 0; i < n; i++) {
				ArrayWithSaveIndex[i] = Radius[i];
			}
		}

		// обнуляем счётчик суммы
		sum = 0;

		// и итерируемся к следующей раскладке
	} while (next_permutation(Radius, Radius + n));

	// выводим ответ
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << ArrayWithSaveIndex[i] << " ";
	cout << min << endl;

	// очищаем память и завершаем работу программы
	delete[]ArrayWithDistanceBetweenDisks;
	delete[]ArrayWithSaveIndex;
	delete[]Radius;
	system("pause");
	return 0;
}

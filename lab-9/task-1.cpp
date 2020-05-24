#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
using namespace std;

class DHeap
{
private:
	int d;
	int currentSize;
	int size;
	int *array;
public:
	// Формирование 
	DHeap(int capacity, int Kids)
	{
		currentSize = 0;
		d = Kids;
		size = capacity + 1;
		array = new int[capacity + 1];
		for (int i = 0; i < capacity + 1; i++)
			array[i] = -1;
	}

	// Заполнение данным массивом
	DHeap(int* array, int Kids)
	{
		int i = 0;
		while (array[i] != -1)
			i++;
		currentSize = i;
		this->array = array;
		this->d = Kids;
		buildHeap();
	}

	// Проверка на пустоту
	bool isEmpty()
	{
		return currentSize == 0;
	}

	// На полноту
	bool isFull()
	{
		return currentSize == size;
	}

	// Очистка дерева
	void makeEmpty()
	{
		currentSize = 0;
	}

	// Поиск родителя для индекса i
	int parent(int i)
	{
		return (i - 1) / d;
	}

	// Поиск k ребенка для i
	int Child(int i, int k)
	{
		return d * i + k;
	}

	// Вставка элемента 
	void insert(int x)
	{
		if (isFull())
		{
			cout << "Переполненный" << endl;
			return;
		}
		int hole = currentSize;
		currentSize++;
		array[hole] = x;
		percolateUp(hole);
	}

	// Минимальный элемент
	void deleteMin()
	{
		if (isEmpty())
		{
			cout << "Пустой" << endl;
			//return 0;
		}
		Delete(0);
		//return array[0];
	}

	// Удаление элемнта с заданым индексом
	int Delete(int hole)
	{
		if (isEmpty())
		{
			cout << "Пустой" << endl;
			return 0;
		}
		int keyItem = array[hole];
		array[hole] = array[currentSize - 1];
		currentSize--;
		percolateDown(hole);
		return keyItem;
	}


	int Deletemax() {
		int k = currentSize - parent(currentSize);
		int naib = currentSize;
		for (int o = 0; o < k + 1; o++) {
			if (array[naib] < array[currentSize - o])naib = currentSize - o;
		}
		Delete(naib);
		return array[naib];
	}

	// Строим кучу
	void buildHeap()
	{
		for (int i = currentSize - 1; i >= 0; i--)
			percolateDown(i);
	}

	// Погружение
	void percolateDown(int hole)
	{
		int child;
		int tmp = array[hole];
		for (; Child(hole, 1) < currentSize; hole = child)
		{
			child = smallestChild(hole);
			if (array[child] < tmp)
				array[hole] = array[child];
			else
				break;
		}
		array[hole] = tmp;
	}

	// Наименьший ребенок
	int smallestChild(int hole)
	{
		int bestChildYet = Child(hole, 1);
		int k = 2;
		int candidateChild = Child(hole, k);
		while ((k <= d) && (candidateChild < currentSize))
		{
			if (array[candidateChild] < array[bestChildYet])
				bestChildYet = candidateChild;
			k++;
			candidateChild = Child(hole, k);
		}
		return bestChildYet;
	}

	// Всплывание
	void percolateUp(int hole)
	{
		int tmp = array[hole];
		for (; hole > 0 && tmp < array[parent(hole)]; hole = parent(hole))
			array[hole] = array[parent(hole)];
		array[hole] = tmp;
	}

	// Вывод дерева
	void printHeap()
	{
		cout << "\n  Куча = ";
		for (int i = 0; i < currentSize; i++)
			cout << array[i] << "   ";
		cout << endl;
	}

	void printkaknado(const std::string & probel, int n, bool lefts)
	{
		if (n < currentSize)
		{
			cout << probel;

			if (array[n] != -1)
				cout << "|_:" << array[n] << std::endl;
			else
				cout << "|_:-" << endl;
			for (int i = 1; i < this->d; i++) {
				if (lefts)
				{
					printkaknado(probel + "|   ", this->Child(n, i), true);
				}
				else {
					printkaknado(probel + "    ", this->Child(n, i), true);
				}
			}
			if (lefts) {
				printkaknado(probel + "|   ", this->Child(n, d), false);
			}
			else  printkaknado(probel + "    ", this->Child(n, d), false);
		}
	}

};

int main()
{
	setlocale(LC_ALL, "ru");
	cout << "Введите размер массива и количество детей у каждого узла: ";
	int size, num, choice, val;
	cin >> size >> num;
	DHeap kycha(size, num);
	char ch;
	do
	{
		cout << "\nОперации\n";
		cout << "1. Вставка" << endl;
		cout << "2. Удаление" << endl;
		cout << "3. Проверка на полноту" << endl;
		cout << "4. Проверка на пустоту" << endl;
		cout << "5. Очистка " << endl;
		cout << "6. Красивый вывод " << endl;
		cout << "7. Удалеие максимального" << endl;
		cout << "Действие : ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Введите вставляемый элемент : ";
			cin >> val;
			kycha.insert(val);
			break;
		case 2:
			cout << "Введите номер позиции удаляемого элемента : ";
			cin >> val;
			kycha.Delete(val - 1);
			break;
		case 3:
			if (kycha.isFull())
				cout << "Куча заполнена " << endl;
			else
				cout << "Куча не заполнена " << endl;
			break;
		case 4:
			if (kycha.isEmpty())
				cout << "Куча пуста" << endl;
			else
				cout << "Куча не пуста" << endl;
			break;
		case 5:
			kycha.makeEmpty();
			cout << "Куча очищена\n";
			break;
		case 6:kycha.printkaknado("", 0, false); break;
		case 7:kycha.deleteMin(); break;
		default:
			cout << "Ошибка ввода \n ";
			break;
		}
		kycha.printHeap();
		cout << "\nДля продолжения нажмите q \n";
		cin >> ch;
	} while (ch == 'q');
	system("pause");
	return 0;
}

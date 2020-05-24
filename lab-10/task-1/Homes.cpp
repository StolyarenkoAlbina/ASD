#include <iostream>
#include "City.h"

using namespace std;

int main()
{
    int n = 0;
    int rand = 0;
    setlocale(0, "ru");

    cout << "Введите случайное число: ";
    cin >> rand;
    srand(rand);

    cout << "Введите количество домов: ";
    cin >> n;

    City City(n);
    // Генеририруем исходные данные
    City.Rand();
    // Отображаем общую схему расположения домиков
    City.ShowMask();
    // Отображаем данные домиков
    City.ShowHomes();
    // Отображаем результирующую карту
    City.ShowMap();

    // Выводим матрицу смежности графа
    //City.graph->Show();

    // Выводим информацию о пройденном пути
    City.ShowPathLen();

    system("pause");
}

#pragma once

#include "Graph.h"
#define MY_CITYOVERFLOW -1

// размер поля города 
#define CITY_SIZE 100 // 7 - минимум
// Количество домов на одной линии - 100 / (5+1) = ~16
#define HOMES_IN_LINE 16 // 1 - минимум
// Количество домиков всего на поле 16*16 = 256
#define MAX_HOMES 256 // 1 - минимум

// Класс для хранения информации о домиках
class City {
private:
	// Домики
	Home** items = NULL;
	// путь от 0,0 до 100,100
	Path* path = NULL;
	// Количество домиков
	int count = 0;
	// Фактическое количество домиков
	int last = 0;
	// Карта города, необходима для генерации
	bool** city = NULL;

public:
	Graph* graph = NULL;

private:
	// Очистить город (не используется)
	void ClearCity() {
		for (int i = 0; i < HOMES_IN_LINE; i++)
			for (int j = 0; j < HOMES_IN_LINE; j++) {
				this->city[i][j] = false;
			}
	}
public:
	inline
		City(int Count) {
			this->count = Count;
			this->items = new Home * [Count];
			this->city = new bool* [HOMES_IN_LINE];
			for (int i = 0; i < HOMES_IN_LINE; i++) {
				this->city[i] = new bool[HOMES_IN_LINE]{ false };
			}
		}
	inline
		~City() {
			for (int i = 0; i < this->count; i++)
				delete this->items[i];
			delete[] this->items;
			for (int i = 0; i < HOMES_IN_LINE; i++)
				delete[] this->city[i];
			delete[] this->city;
			delete this->path;
		}
	inline
		// (не используется)
		Home* operator[] (int ID) {
			return this->items[ID];
		}

	// Поиск дома по указанным координатам, с учетом размера
	bool FindIn(int x, int y);
	// Проверка, есть ли указанная координата в пути
	bool FindInPath(int x, int y);

	// подробности в Homes.cpp
	void Rand();
	void ShowMask();
	void ShowHomes();
	void ShowMap();
	void ShowPathLen();
};


void City::Rand() {
	int count = 0;
	// В карте города, случайным образом расставляем домики
	while (count < this->count) {
		for (int i = 0; i < HOMES_IN_LINE; i++)
			for (int j = 0; j < HOMES_IN_LINE; j++) {
				// Чем больше городов, тем выше шанс установки домиков подряд
				if (!this->city[i][j] && rand() % MAX_HOMES < this->count) {
					this->city[i][j] = true;
					count++;
				}
				if (count >= this->count)
					break;
			}
	}
	// Создаем город на основании карты
	for (int i = 0; i < HOMES_IN_LINE; i++)
		for (int j = 0; j < HOMES_IN_LINE; j++) {
			if (this->last >= this->count)
				break;
			if (this->city[i][j])
				this->items[this->last++] = new Home(i * CITY_SIZE / HOMES_IN_LINE + 1, j * CITY_SIZE / HOMES_IN_LINE + 1);
		}

	// Создаем граф на основе города
	this->graph = new Graph(CITY_SIZE);
	this->graph->Generate(this->items, this->count);

	// Находим кратчайший путь 
	this->path = this->graph->FindPath();
}

void City::ShowMask() {
	for (int i = 0; i < HOMES_IN_LINE; i++) {
		for (int j = 0; j < HOMES_IN_LINE; j++)
			std::cout << ((this->city[i][j]) ? "[]" : "..");
		std::cout << std::endl;
	}
}

void City::ShowHomes() {
	for (int i = 0; i < this->count; i++)
		std::cout << i + 1 << ". Home[" << i + 1 << "](x:" << this->items[i]->x << ", y:" << this->items[i]->y << ")" << std::endl;
}

void City::ShowMap() {
	for (int i = CITY_SIZE - 1; i > -1; i--) {
	//for (int i = 0; i < CITY_SIZE; i++) {
		for (int j = 0; j < CITY_SIZE; j++)
		{
			std::cout << (FindIn(i, j) ? "#" : FindInPath(i, j) ? "." : " ");
		}
		std::cout << std::endl;
	}
}

bool City::FindIn(int x, int y) {
	for (int i = 0; i < this->count; i++)
		if (this->items[i]->x <= x && this->items[i]->x + this->items[i]->w > x
			&& this->items[i]->y <= y && this->items[i]->y + this->items[i]->h > y)
			return true;
	return false;
}

bool City::FindInPath(int x, int y) {
	if (this->path != NULL) {
		Point* tmp = this->path->Start;
		while (tmp != NULL) {
			if (tmp->x == x && tmp->y == y)
				return true;
			tmp = tmp->Next;
		}
	}
	return false;
}

void City::ShowPathLen() {
	int count = 0;
	if (this->path != NULL) {
		Point* tmp = this->path->Start;
		while (tmp != NULL) {
			std::cout << "(" << CITY_SIZE - tmp->x << "," << CITY_SIZE - tmp->y << ") ";
			count++;
			tmp = tmp->Next;
		}
	}
	std::cout << "Пройденный путь: " << count << ".00 шагов" << std::endl;
}
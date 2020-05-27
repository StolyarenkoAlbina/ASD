#pragma once

#include "Home.h"
#include "Path.h"

// Класс графа для всех расчетов
class Graph
{
private:
	//bool** matrix = NULL;
	int** d = NULL; // Матрица смежности/расстояний
	int** p = NULL; // Откуда пришли
	int count = 0;
	int line = 0;
private:
	// Дом ли точка
	bool isHome(int, Home**, int);
public:
	inline
		Graph(int Points) {
			this->line = Points;
			this->count = Points * Points;
			//this->matrix = new bool* [this->count];
			this->d = new int* [this->count];
			this->p = new int* [this->count];
			for (int i = 0; i < this->count; i++) {
				//this->matrix[i] = new bool[this->count]{false};
				this->d[i] = new int[this->count]{0};
				this->p[i] = new int[this->count]{0};
			}				
		}
	inline
		~Graph() {
			for (int i = 0; i < this->count; i++) {
				//delete[] this->matrix[i];
				delete[] this->d[i];
				delete[] this->p[i];
			}
			//delete[] this->matrix;
			delete[] this->d;
			delete[] this->p;
		}

	// Генерация графа на основании города
	void Generate(Home**, int);
	// Поиск пути в городе
	Path* FindPath();
	// Отобразить матрицу смежности/расстояний
	void Show();
};

void Graph::Generate(Home** Homes, int count) {
	// т.к. у нас граф в виде многосвязной матрицы и идем мы только от 0,0 до 100,100
	// то генерировать матрицу смежности мы можем по следующим формулам
	// что сильно ускорит генерацию
	// i+len	i+len+1
	// i		i+1
	// важно проверять не дом ли точка, т.к. к дому мы идти не можем
	for (int i = 0; i < this->count; i++) {

		//this->matrix[i][i] = true;

		if ((i + 1) % this->line != 0 && !isHome(i + 1, Homes, count)) {
			//this->matrix[i][i + 1] = true;
			this->d[i][i + 1] = 1;
			this->p[i][i + 1] = i;
			if (i + this->line + 1 < this->count && !isHome(i + this->line + 1, Homes, count)) {
				//this->matrix[i][i + this->line + 1] = true;
				this->d[i][i + this->line + 1] = 1;
				this->p[i][i + this->line + 1] = i;
			}
		}

		if (i + this->line < this->count && !isHome(i + this->line, Homes, count)) {
			//this->matrix[i][i + this->line] = true;
			this->d[i][i + this->line] = 1;
			this->p[i][i + this->line] = i;
		}

	}
}

bool Graph::isHome(int id, Home** Homes, int count) {
	// Определяем координату х точки
	int x = id / this->line;
	// Определяем координату у точки
	int y = id - x * this->line;
	for (int i = 0; i < count; i++) {
		Home* tmp = Homes[i];
		if (x >= tmp->x && x < tmp->x + tmp->w &&
				y >= tmp->y && y < tmp->y + tmp->h)
			return true;
	}
	return false;
}

Path* Graph::FindPath() {
	Path* path = new Path();
	bool end = false;
	//Show();
	while (!end) {
		for (int i = 0; i < this->count; i++) {
			//std::cout << "-------------------" << std::endl;
			//Show();
			for (int j = i + 1; j < this->count; j++) {
				end = true;
				int min = (this->d[i][j] == 0) ? 1000000 : this->d[i][j];
				int k1 = 0;

				// т.к. у нас граф в виде многосвязной матрицы и идем мы только от 0,0 до 100,100
				// то генерировать матрицу мы смежности мы можем по следующим формулам
				// что оочень сильно ускорит процесс поиска пути
				// i-1		i
				// i-len-1	i-len
				if (j > 1 && j < this->count) {

					if (this->d[j - 1][j] != 0 && this->d[i][j - 1] != 0 && this->d[i][j - 1] < min) {
						k1 = j - 1;
						min = this->d[i][k1];
						end = false;
					}
					if (j > this->line&& this->d[j - this->line][j] != 0 && this->d[i][j - this->line] != 0 && this->d[i][j - this->line] < min) {
						k1 = j - this->line;
						min = this->d[i][k1];
						end = false;
					}

					if (j > this->line + 1 && this->d[j - this->line - 1][j] != 0 && this->d[i][j - this->line - 1] != 0 && this->d[i][j - this->line - 1] < min) {
						k1 = j - this->line - 1;
						min = this->d[i][k1];
						end = false;
					}
				}

				if (!end) {
					this->d[i][j] = min + 1;
					this->p[i][j] = k1;
				}
			}
		}
	}

	// Генерируем путь на основании итоговой матрицы расстояний
	int max = this->d[0][this->count - 1];
	int id = this->count - 1;
	while (max > 0) {
		int x = id / this->line;
		int y = id - x * this->line;
		path->Add(x, y);
		id = p[0][id];
		max--;
	}
	path->Add(0, 0);
	return path;
}

void Graph::Show() {
	for (int i = 0; i < this->count; i++) {
		for (int j = 0; j < this->count; j++)
			std::cout << this->d[i][j] << " ";
		std::cout << "|" << std::endl;
	}
}
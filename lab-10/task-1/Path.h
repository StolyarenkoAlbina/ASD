#pragma once

struct Point {
public:
	int x = 0;
	int y = 0;
	Point* Next = NULL;
public:
	inline
		Point(int X, int Y) {
			this->x = X;
			this->y = Y;
		}
};

// Последовательный путь
struct Path {
public:
	// сСартовая точка
	Point* Start = NULL;
	// Псоледняя точка
	Point* Last = NULL;
public:
	Path() {};
	inline
		void Add(int X, int Y) {
			Point* tmp = new Point(X, Y);
			if (Start == NULL) {
				Start = tmp;
				Last = tmp;
			}
			else {
				Last->Next = tmp;
				Last = tmp;
			}
		}
};


#pragma once

struct Home {
public:
	int x = 0; // Положение по х
	int y = 0; // Положение по y
	int w = 5; // Ширина
	int h = 5; // Высота
public:
	Home() {};
	Home(int X, int Y) {
		this->x = X;
		this->y = Y;
	}
	Home(int X, int Y, int W, int H) {
		this->x = X;
		this->y = Y;
		this->w = W;
		this->h = H;
	}
};
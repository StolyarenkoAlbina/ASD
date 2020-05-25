#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

const char F1[7] = "g1.txt";
const char F2[7] = "g2.txt";
const char F3[7] = "g3.txt";

void RandEnter(int N) {
	ofstream f;
	f.open(F1, ios::out);
	for (int i = 0; i < N; i++) {
		int j = rand() % N + 1;
		f << j << " ";
	}
	f.close();
}

void Ascending(int N) {
	ofstream f;
	f.open(F1, ios::out);
	for (int i = 0; i < N; i++) {
		f << i + 1 << " ";
	}
	f.close();
}

void Descending(int N) {
	ofstream f;
	f.open(F1, ios::out);
	for (int i = 0; i < N; i++) {
		int j = N - i;
		f << j << " ";
	}
	f.close();
}


int fibonachi(int n) {
	if (n == 0) {
		return 0;
	}
	if (n == 1 || n == 2) {
		return 1;
	}
	return fibonachi(n - 1) + fibonachi(n - 2);
}

void initial_distribution(int q, int y, int pust) {
	ifstream f1;
	ofstream f2;
	ofstream f3;
	f1.open(F1, ios::in);
	f2.open(F2, ios::out);
	f3.open(F3, ios::out);
	if (pust != 0) {
		for (int i = 0; i < pust; i++) {
			f2 << "-1" << " " << "-2" << " ";
		}
	}
	int c;
	f1 >> c;
	f2 << c << " " << "-2";
	for (int i = 0; i < (y - pust) - 1; i++) {
		int a;
		f1 >> a;
		f2 << " " << a << " " << "-2";
	}
	int c1;
	f1 >> c1;
	f3 << c1 << " " << "-2";;
	for (int i = 0; i < q - 1; i++) {
		int a;
		f1 >> a;
		f3 << " " << a << " " << "-2";
	}
	f2.close();
	f3.close();
	f1.close();
	ofstream f11;
	f11.open(F1, ios::out);
	f1.close();
}

void sort() {
	ifstream f1;
	f1.open(F1, ios::in);
	ifstream f2;
	f2.open(F2, ios::in);
	ifstream f3;
	f3.open(F3, ios::in);
	if (f1.peek() == EOF && f2.peek() == EOF) {
		f1.close();
		f2.close();
		ofstream f11(F1, ios::out);
		while (f3.eof() != true) {
			int a;
			f3 >> a;
			if (a == -2) {

			}
			else {
				if (f3.eof() != true) {
					f11 << a << " ";
				}
			}
		}
		f11.close();
		f3.close();
		ofstream f33;
		f33.open(F3, ios::out);
		f33.close();
		return;
	}
	if (f1.peek() == EOF && f3.peek() == EOF) {
		f1.close();
		f3.close();
		ofstream f11(F1, ios::out);
		while (f2.eof() != true) {
			int a;
			f2 >> a;
			if (a == -2) {

			}
			else {
				if (f2.eof() != true) {
					f11 << a << " ";
				}
			}
		}
		f2.close();
		f11.close();
		ofstream f22;
		f22.open(F2, ios::out);
		f22.close();
		return;
	}
	if (f2.peek() == EOF && f3.peek() == EOF) {
		f3.close();
		f2.close();
		ofstream f22;
		f22.open(F2, ios::out);
		while (f1.eof() != true) {
			int a;
			f1 >> a;
			if (a == -2) {

			}
			else {
				if (f1.eof() != true) {
					f22 << a << " ";
				}
			}
		}
		f22.close();
		f1.close();
		ofstream f11;
		f11.open(F1, ios::out);
		f11.close();
		return;
	}
	if (f1.peek() != EOF && f2.peek() != EOF) {
		f3.close();
		ofstream f33;
		f33.open(F3, ios::out);
		int size = 0;
		f1.seekg(0, ios::end);
		size = (int)f1.tellg();
		int size1 = 0;
		f2.seekg(0, ios::end);
		size1 = (int)f2.tellg();
		if (size > size1) {
			f1.close();
			f1.open(F1, ios::in);
			f2.close();
			f2.open(F2, ios::in);
			int a;
			int b;
			f1 >> a;
			f2 >> b;
			while (f1.eof() != true) {
				if (a == -2 && b == -2) {
					if (f2.eof() == true) {
						f33 << "-2";
						break;
					}
					else {
						f2 >> b;
						f33 << "-2" << " ";
						f1 >> a;
					}
				}
				else {
					if (a == -2 || b == -2) {
						if (a == -2) {
							f33 << b << " ";
							f2 >> b;
						}
						else {
							f33 << a << " ";
							f1 >> a;
						}
					}
					else {
						if (a > b) {
							f33 << b << " ";
							f2 >> b;
						}
						else {
							if (a < b) {
								f33 << a << " ";
								f1 >> a;
							}
							else {
								f33 << a << " " << b << " ";
								f1 >> a;
								f2 >> b;
							}
						}
					}
				}
			}
			f33.close();
			f2.close();
			ofstream f22;
			f22.open(F2, ios::out);
			if (f1.eof() != true) {
				int c;
				f1 >> c;
				f22 << c;
				while (f1.eof() != true) {
					int a;
					f1 >> a;
					f22 << " " << a;
				}
			}
			f1.close();
			f22.close();
			ofstream f11;
			f11.open(F1, ios::out);
			f11.close();
			return sort();
		}
		else {
			f1.close();
			f1.open(F1, ios::in);
			f2.close();
			f2.open(F2, ios::in);
			int a;
			int b;
			f1 >> a;
			f2 >> b;
			while (f2.eof() != true) {
				if (a == -2 && b == -2) {
					if (f1.eof() == true) {
						f33 << "-2";
						break;
					}
					else {
						f2 >> b;
						f33 << "-2" << " ";
						f1 >> a;
					}
				}
				else {
					if (a == -2 || b == -2) {
						if (a == -2) {
							f33 << b << " ";
							f2 >> b;
						}
						else {
							f33 << a << " ";
							f1 >> a;
						}
					}
					else {
						if (a > b) {
							f33 << b << " ";
							f2 >> b;
						}
						else {
							if (a < b) {
								f33 << a << " ";
								f1 >> a;
							}
							else {
								f33 << a << " " << b << " ";
								f1 >> a;
								f2 >> b;
							}
						}
					}
				}
			}
			f33.close();
			f1.close();
			ofstream f11;
			f11.open(F1, ios::out);
			if (f2.eof() != true) {
				int c;
				f2 >> c;
				f11 << c;
				while (f2.eof() != true) {
					int a;
					f2 >> a;
					f11 << " " << a;
				}
			}
			f2.close();
			f11.close();
			ofstream f22;
			f22.open(F2, ios::out);
			f22.close();
			return sort();
		}
	}
	if (f1.peek() != EOF && f3.peek() != EOF) {
		f2.close();
		ofstream f22;
		f22.open(F2, ios::out);
		int size = 0;
		f1.seekg(0, ios::end);
		size = (int)f1.tellg();
		int size1 = 0;
		f3.seekg(0, ios::end);
		size1 = (int)f3.tellg();
		if (size > size1) {
			f1.close();
			f1.open(F1, ios::in);
			f3.close();
			f3.open(F3, ios::in);
			int a;
			int b;
			f1 >> a;
			f3 >> b;
			while (f1.eof() != true) {
				if (a == -2 && b == -2) {
					if (f3.eof() == true) {
						f22 << "-2";
						break;
					}
					else {
						f3 >> b;
						f22 << "-2" << " ";
						f1 >> a;
					}
				}
				else {
					if (a == -2 || b == -2) {
						if (a == -2) {
							f22 << b << " ";
							f3 >> b;
						}
						else {
							f22 << a << " ";
							f1 >> a;
						}
					}
					else {
						if (a > b) {
							f22 << b << " ";
							f3 >> b;
						}
						else {
							if (a < b) {
								f22 << a << " ";
								f1 >> a;
							}
							else {
								f22 << a << " " << b << " ";
								f1 >> a;
								f3 >> b;
							}
						}
					}
				}
			}
			f22.close();
			f3.close();
			ofstream f33;
			f33.open(F3, ios::out);
			if (f1.eof() != true) {
				int c;
				f1 >> c;
				f33 << c;
				while (f1.eof() != true) {
					int a;
					f1 >> a;
					f33 << " " << a;
				}
			}
			f1.close();
			f33.close();
			ofstream f11;
			f11.open(F1, ios::out);
			f11.close();
			return sort();
		}
		else {
			f1.close();
			f1.open(F1, ios::in);
			f3.close();
			f3.open(F3, ios::in);
			int a;
			int b;
			f1 >> a;
			f3 >> b;
			while (f3.eof() != true) {
				if (a == -2 && b == -2) {
					if (f1.eof() == true) {
						f22 << "-2";
						break;
					}
					else {
						f3 >> b;
						f22 << "-2" << " ";
						f1 >> a;
					}
				}
				else {
					if (a == -2 || b == -2) {
						if (a == -2) {
							f22 << b << " ";
							f3 >> b;
						}
						else {
							f22 << a << " ";
							f1 >> a;
						}
					}
					else {
						if (a > b) {
							f22 << b << " ";
							f3 >> b;
						}
						else {
							if (a < b) {
								f22 << a << " ";
								f1 >> a;
							}
							else {
								f22 << a << " " << b << " ";
								f1 >> a;
								f3 >> b;
							}
						}
					}
				}
			}
			f22.close();
			f1.close();
			ofstream f11;
			f11.open(F1, ios::out);
			if (f3.eof() != true) {
				int c;
				f3 >> c;
				f11 << c;
				while (f3.eof() != true) {
					int a;
					f3 >> a;
					f11 << " " << a;
				}
			}
			f3.close();
			f11.close();
			ofstream f33;
			f33.open(F3, ios::out);
			f33.close();
			return sort();
		}
	}
	if (f2.peek() != EOF && f3.peek() != EOF) {
		f1.close();
		ofstream f11;
		f11.open(F1, ios::out);
		int size = 0;
		f2.seekg(0, ios::end);
		size = (int)f2.tellg();
		int size1 = 0;
		f3.seekg(0, ios::end);
		size1 = (int)f3.tellg();
		if (size > size1) {
			f2.close();
			f2.open(F2, ios::in);
			f3.close();
			f3.open(F3, ios::in);
			int a;
			int b;
			f2 >> a;
			f3 >> b;
			while (f2.eof() != true) {
				if (a == -2 && b == -2) {
					if (f3.eof() == true) {
						f11 << "-2";
						break;
					}
					else {
						f3 >> b;
						f11 << "-2" << " ";
						f2 >> a;
					}
				}
				else {
					if (a == -2 || b == -2) {
						if (a == -2) {
							f11 << b << " ";
							f3 >> b;
						}
						else {
							f11 << a << " ";
							f2 >> a;
						}
					}
					else {
						if (a > b && a != -1) {
							f11 << b << " ";
							f3 >> b;
						}
						else {
							if (a < b && a != -1) {
								f11 << a << " ";
								f2 >> a;
								if (f2.eof() == true) {
									f11 << b << " " << "-2";
								}
							}
							else {
								if (a == -1) {
									f2 >> a;
								}
								else {
									f11 << a << " " << b << " ";
									f2 >> a;
									f3 >> b;
								}
							}
						}
					}
				}
			}
			f11.close();
			f3.close();
			ofstream f33;
			f33.open(F3, ios::out);
			if (f2.eof() != true) {
				int c;
				f2 >> c;
				f33 << c;
				while (f2.eof() != true) {
					int a;
					f2 >> a;
					f33 << " " << a;
				}
			}
			f2.close();
			f33.close();
			ofstream f22;
			f22.open(F2, ios::out);
			f22.close();
			return sort();
		}
		else {
			f2.close();
			f2.open(F2, ios::in);
			f3.close();
			f3.open(F3, ios::in);
			int a;
			int b;
			f2 >> a;
			f3 >> b;
			while (f3.eof() != true) {
				if (a == -2 && b == -2) {
					if (f2.eof() == true) {
						f11 << "-2";
						break;
					}
					else {
						f3 >> b;
						f11 << "-2" << " ";
						f2 >> a;
					}
				}
				else {
					if (a == -2 || b == -2) {
						if (a == -2) {
							f11 << b << " ";
							f3 >> b;
						}
						else {
							f11 << a << " ";
							f2 >> a;
						}
					}
					else {
						if (a > b) {
							f11 << b << " ";
							f3 >> b;
						}
						else {
							if (a < b) {
								f11 << a << " ";
								f2 >> a;
							}
							else {
								f11 << a << " " << b << " ";
								f2 >> a;
								f3 >> b;
							}
						}
					}
				}
			}
			f11.close();
			f2.close();
			ofstream f22;
			f22.open(F2, ios::out);
			if (f3.eof() != true) {
				int c;
				f3 >> c;
				f22 << c;
				while (f3.eof() != true) {
					int a;
					f3 >> a;
					f22 << " " << a;
				}
			}
			f3.close();
			f22.close();
			ofstream f33;
			f33.open(F3, ios::out);
			f33.close();
			return sort();
		}
	}
}

int main() {
	setlocale(0, "");
	int N;
	cout << "Введите размер массива: " << endl;
	cin >> N;
	int K;
	cout << "Заполнение массива: 1.По возрастанию 2.По убыванию 3.Рандом" << endl;
	cin >> K;
	if (K == 1) {
		Ascending(N);
	}
	if (K == 2) {
		Descending(N);
	}
	if (K == 3) {
		RandEnter(N);
	}
	int j, q, y;
	for (int i = 0; i < 100000; i++) {
		q = fibonachi(i);
		y = fibonachi(i + 1);
		j = q + y;
		if (j >= N) {
			break;
		}
	}
	int pyst = j - N;
	double start_time = clock();
	initial_distribution(q, y, pyst);
	sort();
	double end_time = clock();
	double search_time = end_time - start_time;
	double time = search_time;
	cout <<"Время работы в  миллисекундах: " << time << endl;
	system("pause");
	return 0;
}

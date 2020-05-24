#pragma once
#define MY_DEQUEOWERFLOW -1

class Deque
{
	int* arr = 0;
	int count = 0;
	int id = 0;
public:
	inline
		Deque(int Count) {
		this->count = Count;
		arr = new int[this->count]{ 0 };
	}
	inline
		~Deque() { delete[] arr; }

	inline
		int Count() { return this->id; }

	int Pop_first();
	int Pop_last();
	int Push_first(int);
	int Push_last(int);

	void Resize(int);
};

int Deque::Pop_first()
{
	if (this->id > 0) {
		int res = this->arr[0];
		for (int i = 1; i < this->id; i++)
			this->arr[i - 1] = this->arr[i];
		this->arr[--this->id] = 0;
		return res;
	}
	else return 0;
}
int Deque::Pop_last()
{
	return (this->id > 0)
		? this->arr[--this->id]
		: 0;
}

int Deque::Push_first(int Value)
{
	if (this->id < this->count) {
		for (int i = this->id; i > 0; i--)
			this->arr[i] = this->arr[i - 1];
		this->arr[0] = Value;
		this->id++;
		return 0;
	}
	else return MY_DEQUEOWERFLOW;
}
int Deque::Push_last(int Value)
{
	if (this->id < this->count) {
		this->arr[this->id++] = Value;
		return 0;
	}
	else return MY_DEQUEOWERFLOW;
}

void Deque::Resize(int NewSize) {
	int* arr = new int[NewSize] {0};
	int min = (this->count < NewSize) ? this->count : NewSize;
	for (int i = 0; i < min && i < this->id; i++)
		arr[i] = this->arr[i];
	this->count = min;
	delete[] this->arr;
	this->arr = arr;
}

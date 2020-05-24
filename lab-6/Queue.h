#pragma once
#define MY_QUEUEOWERFLOW -1

class Queue
{
	int* arr = 0;
	int count = 0;
	int id = 0;
public:
	inline
		Queue(int Count) {
		this->count = Count;
		arr = new int[this->count]{0};
	}
	inline
		~Queue() { delete[] arr; }

	inline
		int Count() { return this->id; }

	int Pop();
	int Push(int);

	void Resize(int);
};

int Queue::Pop()
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

int Queue::Push(int Value)
{
	if (this->id < this->count) {
		this->arr[this->id++] = Value;
		return 0;
	}
	else return MY_QUEUEOWERFLOW;
}

void Queue::Resize(int NewSize) {
	int* arr = new int[NewSize] {0};
	int min = (this->count < NewSize) ? this->count : NewSize;
	for (int i = 0; i < min && i < this->id; i++)
		arr[i] = this->arr[i];
	this->count = min;
	delete[] this->arr;
	this->arr = arr;
}
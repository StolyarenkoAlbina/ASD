#pragma once
#define MY_STACKOWERFLOW -1

class Stack
{
	int* arr = 0;
	int count = 0;
	int id = 0;
public:
	inline 
		Stack(int Count) {
		this->count = Count;
		arr = new int[this->count];
	}
	inline 
		~Stack() { delete[] arr; }

	inline
		int Count() { return this->id; }

	int Pop();
	int Push(int);

	void Resize(int);
};

int Stack::Pop()
{
	return (this->id > 0) 
		? this->arr[--this->id] 
		: 0;
}

int Stack::Push(int Value)
{
	if (this->id < this->count) {
		this->arr[this->id++] = Value;
		return 0;
	} else return MY_STACKOWERFLOW;
}

void Stack::Resize(int NewSize) {
	int* arr = new int[NewSize] {0};
	int min = (this->count < NewSize) ? this->count : NewSize;
	for (int i = 0; i < min && i < this->id; i++)
		arr[i] = this->arr[i];
	this->count = min;
	delete[] this->arr;
	this->arr = arr;
}

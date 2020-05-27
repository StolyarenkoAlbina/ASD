#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
using namespace std;

class List {
public:
	int value;
	List* next;

	List(int temp) { next = NULL; value = temp; }
	int getValue() { return value; }
	void setNext(List *x) { next = x; }
	List* getNext() { return next; }
};

const int SIZE = 243; // 9*9 + 9*9 + 9*9

class hashTable {
private:
	List* data[SIZE];
public:
	hashTable() {
		for (int i = 0; i < SIZE; i++)
			data[i] = NULL;
	}
	int hash(int num, int size) {
		int len = 0;
		int t = num;
		while (t) {
			t /= 10;
			len++;
		}
		int ndx = 0;
		for (int i = len - 1; i >= 0; i--) {
			ndx += ((10 + num) % 10) * ((10 + num) % 10);
			num /= 10;
		}
		while (ndx >= SIZE) ndx -= SIZE;
		return ndx;
	}
	void insert(int key, int val) {
		if (data[key] == NULL)
			data[key] = new List(val);
		else {
			List* temp = data[key];

			while (temp->getNext() != NULL)
				temp = temp->getNext();

			List* newEntry = new List(val);
			temp->setNext(newEntry);
		}
	}
	void printTable() {
		for (int i = 0; i < SIZE; i++) {
			List* temp = data[i];
			cout << i << ": ";
			while (temp != NULL) {
				cout << temp->getValue() << " ";
				temp = temp->getNext();
			}
			cout << endl;
		}
	}
	void find(int key) {
		bool f = false;
		for (int i = 0; i < SIZE; i++) {
			List* temp = data[i];
			while (temp != NULL) {
				if (temp->value == key) f = true;
				temp = temp->getNext();
			}
		}
		if (f) cout << "Exist; ";
		else cout << "Not exist;";
		cout << endl;
	}
};

const int sizearr = 30;

int main() {
	hashTable theChain;
	int arr[sizearr];
	bool run = true;
	int t;
	int temp;
	int arrHash;
	while (run) {
		cout << endl;
		cout << "1: insert" << endl;
		cout << "2: search" << endl;
		cout << "3: print" << endl;
		cout << "4: exit" << endl;
		cout << "Enter do: ";
		cin >> t;

		switch (t) {
		case 1:
			cout << "Enter key: ";
			cin >> temp;
			arrHash = theChain.hash(temp, SIZE);
			theChain.insert(arrHash, temp);
			break;
		case 2:
			cout << "Enter key: ";
			cin >> temp;
			theChain.find(temp);
			break;
		case 3:
			theChain.printTable();
			break;
		case 4:
			run = false;
			break;
		default:
			cout << " Unknown command" << endl;
			break;
		}
	}

	system("pause");
	return 0;
}

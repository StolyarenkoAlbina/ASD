#pragma once

// символы ля отрисовки графа согласно заданию
#define uno "| "
#define dos "|-"
#define tre "|_"

// прямой (левый)
#define TYPE_DIRECT 0
// обратный
#define TYPE_REVERSE 1
// симметричный
#define TYPE_SYMMETRIC 2

// узел делерва
struct Node
{
public:
	int value = 0;
	Node* Left = NULL;
	Node* Right = NULL;
	Node* Parent = NULL;
public:
	inline
		Node(int val) {
			this->value = val;
		}
};

// бинарное дерево целиком
class BinaryTree {
public:
	// корень
	Node* Start = NULL;
	// уровень последнего найденного элемента
	int last_level = 0;
	int count = 0;
public:
	// прямой вывод дерева на экран
	void DirectShow(Node*, int, bool);
	// обратный вывод дерева на экран
	void ReverseShow(Node*, int, bool);
	// симметрический вывод дерева на экран
	void SymmetricShow(Node*, int, bool);
	// прямой поиск
	Node* DirectFind(Node*, int, int);
	// обратный поиск
	Node* ReverseFind(Node*, int, int);
	// симметричный поиск
	Node* SymmetricFind(Node*, int, int);
	// удалить все вершины дерева после указанной, включая указанную
	void Trim(Node*);
	// удалить вершину дерева
	void Del(Node*, bool);
	// определение глубины
	int Depth(Node*);
	// определение высоты
	int Height(Node*);
public:
	inline
		~BinaryTree() {
			if(this->Start != NULL)
				Trim(this->Start);
		}
	// добавить узел в дерево
	void Add(int);
	// поиск
	Node* Find(int, int);
	// удалить вершину дерева
	void Del(int, bool);
	// отобразить дерево
	void Show(int);
	// определение глубины
	int Depth(int Value);
	// определение высоты
	int Height(int Value);
	int Level(int Value);
};


void BinaryTree::Add(int Value) {
	if (this->Start != NULL) {
		Node* tmp = this->Start;
		while (true) {
			if (Value < tmp->value) {
				if (tmp->Left == NULL) {
					tmp->Left = new Node(Value);
					tmp->Left->Parent = tmp;
					break;
				} else
					tmp = tmp->Left;
			}
			else {
				if (tmp->Right == NULL) {
					tmp->Right = new Node(Value);
					tmp->Right->Parent = tmp;
					break;
				} else
					tmp = tmp->Right;
			}
		}
	} else
		this->Start = new Node(Value);
	this->count++;
}

void BinaryTree::DirectShow(Node* Node, int lvl, bool isL = false) {
	// обход текущего узла
	for (int i = 0; i < lvl - 1; i++)
		std::cout << ((i) ? uno : "  ");
	// сначала обходим левую сторону
	if (Node->Left != NULL) {
		std::cout << ((lvl - 1) ? uno : "  ");
		std::cout << dos << "L:" << Node->Left->value << std::endl;
		DirectShow(Node->Left, lvl + 1, true);
	}
	else
		std::cout << ((isL) ? uno : "  ") << dos << "L:" << "-" << std::endl;

	for (int i = 0; i < lvl - 1; i++)
		std::cout << ((i) ? uno : "  ");
	// после обходим правую
	if (Node->Right != NULL) {
		std::cout << ((lvl - 1) ? uno : "  ");
		std::cout << tre << "R:" << Node->Right->value << std::endl;
		DirectShow(Node->Right, lvl + 1);
	}
	else
		std::cout << ((isL) ? uno : "  ") << tre << "R:" << "-" << std::endl;
}
void BinaryTree::ReverseShow(Node* Node, int lvl, bool isL = false) {
	for (int i = 0; i < lvl - 1; i++)
		std::cout << ((i) ? uno : "  ");
	// обходим выводим правую сторону
	if (Node->Right != NULL) {
		std::cout << ((lvl - 1) ? uno : "  ");
		std::cout << tre << "R:" << Node->Right->value << std::endl;
		ReverseShow(Node->Right, lvl + 1);
	}
	else
		std::cout << ((isL) ? uno : "  ") << tre << "R:" << "-" << std::endl;
	
	for (int i = 0; i < lvl - 1; i++)
		std::cout << ((i) ? uno : "  ");
	// обходим выводим левую
	if (Node->Left != NULL) {
		std::cout << ((lvl - 1) ? uno : "  ");
		std::cout << dos << "L:" << Node->Left->value << std::endl;
		ReverseShow(Node->Left, lvl + 1, true);
	}
	else
		std::cout << ((isL) ? uno : "  ") << dos << "L:" << "-" << std::endl;
	// обход текущего узла
}
void BinaryTree::SymmetricShow(Node* Node, int lvl, bool isL = false) {
	for (int i = 0; i < lvl - 1; i++)
		std::cout << ((i) ? uno : "  ");
	// сначала обходим левую сторону
	if (Node->Left != NULL) {
		std::cout << ((lvl - 1) ? uno : "  ");
		std::cout << dos << "L:" << Node->Left->value << std::endl;
		SymmetricShow(Node->Left, lvl + 1, true);
	}
	else
		std::cout << ((isL) ? uno : "  ") << dos << "L:" << "-" << std::endl;
	// обход текущего узла
	for (int i = 0; i < lvl - 1; i++)
		std::cout << ((i) ? uno : "  ");
	// после обходим правую
	if (Node->Right != NULL) {
		std::cout << ((lvl - 1) ? uno : "  ");
		std::cout << tre << "R:" << Node->Right->value << std::endl;
		SymmetricShow(Node->Right, lvl + 1);
	}
	else
		std::cout << ((isL) ? uno : "  ") << tre << "R:" << "-" << std::endl;
}

void BinaryTree::Show(int type = TYPE_SYMMETRIC) {
	if (this->Start != NULL) {
		std::cout << tre << " " << this->Start->value << std::endl;
		switch (type) {
		case 0:
			return DirectShow(this->Start, 1, false);
		case 1:
			return ReverseShow(this->Start, 1, false);
		case 2:
			return SymmetricShow(this->Start, 1, false);
		}
	}
}

Node* BinaryTree::Find(int Value, int type = TYPE_DIRECT) {
	if (this->Start != NULL) {
		switch (type) {
			case 0:
				return DirectFind(this->Start, Value, 1);
			case 1:
				return ReverseFind(this->Start, Value, 1);
			case 2:
				return SymmetricFind(this->Start, Value, 1);
		}
	}
	return NULL;
}

Node* BinaryTree::DirectFind(Node* node, int Value, int lvl) {
	Node* res = NULL;
	// просматриваем текущий узел
	if (node->value == Value) {
		this->last_level = lvl;
		return node;
	}
	// просматриваем правое поддерево
	if(node->Left != NULL)
		res = DirectFind(node->Left, Value, lvl + 1);
	// просматриваем левое поддерево
	if (res == NULL && node->Right != NULL)
		res = DirectFind(node->Right, Value, lvl + 1);
	return res;
}
Node* BinaryTree::ReverseFind(Node* node, int Value, int lvl) {
	Node* res = NULL;
	// просматриваем левое поддерево
	if (node->Left != NULL)
		res = DirectFind(node->Left, Value, lvl + 1);
	// просматриваем правое поддерево
	if (res == NULL && node->Right != NULL)
		res = DirectFind(node->Right, Value, lvl + 1);
	// просматриваем текущий узел
	if (res == NULL && node->value == Value) {
		this->last_level = lvl;
		return node;
	}
	return res;
}
Node* BinaryTree::SymmetricFind(Node* node, int Value, int lvl) {
	Node* res = NULL;
	// просматриваем левое поддерево
	if (node->Left != NULL)
		res = DirectFind(node->Left, Value, lvl + 1);
	// просматриваем текущий узел
	if (res == NULL && node->value == Value) {
		this->last_level = lvl;
		return node;
	}
	// просматриваем правое поддерево
	if (res == NULL && node->Right != NULL)
		res = DirectFind(node->Right, Value, lvl + 1);
	return res;
}

void BinaryTree::Trim(Node* node) {
	if (node->Left != NULL)
		Trim(node->Left);
	if (node->Right != NULL)
		Trim(node->Right);
	delete node;
}

void BinaryTree::Del(int Value, bool isLeft = true) {
	Del(Find(Value), isLeft);
}
void BinaryTree::Del(Node* tmp, bool isLeft = true) {
	if (tmp != NULL) {
		// проверяем главный ли узел
		if (tmp != this->Start) {
			// смотрим с какой ветки мы пришли, с правой или с левой
			bool parent_is_left = (tmp->Parent != NULL && tmp->Parent->Left == tmp);
			// если у узла есть оа поддерева
			if (tmp->Left != NULL && tmp->Right != NULL) {
				Node* node = NULL;
				Node* del = NULL;
				if (tmp->Right->value > tmp->Left->value) {
					node = (isLeft) ? tmp->Right : tmp->Left;
					del = (isLeft) ? tmp->Left : tmp->Right;
				}
				else {
					node = (isLeft) ? tmp->Left : tmp->Right;
					del = (isLeft) ? tmp->Right : tmp->Left;
				}
				// если мы пришли с левой ветки, то записываем в нее новые данные
				if (parent_is_left) {
					tmp->Parent->Left = node;
					if (node != NULL)
						node->Parent = tmp->Parent;
				}
				else {
					tmp->Parent->Right = node;
					if (node != NULL)
						node->Parent = tmp->Right;
				}
				Trim(del);
			}
			// если есть только левая сторона
			else if (tmp->Left != NULL) {
				if (parent_is_left) {
					tmp->Parent->Left = tmp->Left;
					if (tmp->Left != NULL)
						tmp->Left->Parent = tmp->Parent;
				}
				else {
					tmp->Parent->Right = tmp->Left;
					if (tmp->Left != NULL)
						tmp->Left->Parent = tmp->Right;
				}
			}
			// если есть только левая сторона
			else if (tmp->Right != NULL) {
				if (parent_is_left) {
					tmp->Parent->Left = tmp->Right;
					if (tmp->Right != NULL)
						tmp->Right->Parent = tmp->Parent;
				}
				else {
					tmp->Parent->Right = tmp->Right;
					if (tmp->Right != NULL)
						tmp->Right->Parent = tmp->Parent;
				}
			}
			else  if (parent_is_left) {
				tmp->Parent->Left = NULL;
			}
			else {
				if(tmp->Parent != NULL)
					tmp->Parent->Right = NULL;
			}

		}
		// то же самое но для главного узла
		else {
			if (tmp->Left != NULL && tmp->Right != NULL) {
				Node* node = NULL;
				Node* del = NULL;

				if (tmp->Right->value > tmp->Left->value) {
					node = (isLeft) ? tmp->Right : tmp->Left;
					del = (isLeft) ? tmp->Left : tmp->Right;
				}
				else {
					node = (isLeft) ? tmp->Left : tmp->Right;
					del = (isLeft) ? tmp->Right : tmp->Left;
				}

				this->Start = node;
				if (node != NULL)
					node->Parent = NULL;
				Trim(del);
			}
			else if (tmp->Left != NULL) {
				this->Start = tmp->Left;
				if (tmp->Left != NULL)
					tmp->Left->Parent = NULL;
			}
			else if (tmp->Right != NULL) {
				this->Start = tmp->Right;
				if (tmp->Right != NULL)
					tmp->Right->Parent = NULL;
			}
			else {
				this->Start = NULL;
			}
		}
		delete tmp;
		this->count--;
	}
}

int BinaryTree::Depth(Node* node)
{
	return (node->Parent == NULL) ? 0 : Depth(node->Parent) + 1;
}
int BinaryTree::Depth(int Value) {
	return Depth(Find(Value));
}

int BinaryTree::Height(Node* node)
{
	if (node == NULL)
		return 0;
	int left, right;
	if (node->Left != NULL) {
		left = Height(node->Left);
	}
	else
		left = -1;
	if (node->Right != NULL) {
		right = Height(node->Right);
	}
	else
		right = -1;
	int max = (left > right) ? left : right;
	return max + 1;

}
int BinaryTree::Height(int Value) {
	return Height(Find(Value));
}

int BinaryTree::Level(int Value) {
	Find(Value);
	return this->last_level;
}
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include "Node.h"

// класс для упращения поиска "средних" узлов
// динамические int по сути
struct Arr {
public:
    Node* node = NULL;
    Arr* Next = NULL;
    int count = 1;
public:
    Arr(){}
    inline
        Arr(Node* Value) {
            this->node = Value;
        }
    inline
        ~Arr() {
            Clear();
        }
    void Clear() {
        Arr* tmp = this->Next;
        while (tmp != NULL) {
            Arr* del = tmp;
            tmp = this->Next;
            delete del;
        }
        this->count = 0;
    }
    void Add(Node* node) {
        Arr* tmp = this->Next;
        while(tmp != NULL) {}
        this->Next = new Arr(node);
        count++;
    }
    int Get(int ID) {
        if (ID > this->count) {
            throw 0;
        }
        Arr* res = this;
        for (int i = 0; i < ID; i++)
            res = res->Next;
        return res->node->value;
    }
    int* toArray() {
        int* arr = new int[this->count];
        for (int i = 0; i < this->count; i++)
            arr[i] = this->Get(i);
        return arr;
    }

    Node* GetNode(int Value) {
        Arr* res = this;
        for (int i = 1; i < this->count; i++)
            res = res->Next;
        return res->node;
    }
};


int main()
{
    setlocale(0, "ru-ru");

    BinaryTree* tree = new BinaryTree();
    int len = 9;
    // массив для заполнения дерева
    int* arr = new int[len] {10, 7, 8, 12, 6, 14, 11, 3, 4};

    for (int i = 0; i < len; i++)
        tree->Add(arr[i]);

    // выводим дерево прямым способом
    tree->Show(TYPE_DIRECT);

    std::cout << "------------------\n";

    Node* min = NULL;
    int max = 0;
    // поиск элемента с максимальной разницей между 
    // высотой левого и правого поддеревьев
    for (int i = 1; i < len; i++) {
        int l = 0;
        int r = 0;
        Node* tmp = tree->Find(arr[i]);
        l = tree->Height(tmp->Left);
        r = tree->Height(tmp->Right);
        if (abs(l - r) > max) {
            max = abs(l - r);
            min = tmp;
        }
    }

    Arr* tree1 = new Arr();
    tree1->node=min;
    // поиск элементов с такой же разницей между
    // высотой левого и правого поддеревьев
    for (int i = 1; i < len; i++) {
        int l = 0;
        int r = 0;
        Node* tmp = tree->Find(arr[i]);
        if (tmp != min) {
            l = tree->Height(tmp->Left);
            r = tree->Height(tmp->Right);
            if (abs(l - r) == max) {
                tree1->Add(tmp);
            }
        }
    }

    std::cout << "Максимальная разница между левый и правым поддеревьями: " << max << std::endl;
    std::cout << "Было найдено поддеревьев: " << tree1->count << std::endl;

    // перегоняем класс в массив int и сортируем
    int* arr2 = tree1->toArray();
    std::sort(arr2, arr2 + 1);

    // находим средний индекс
    max = arr2[tree1->count / 2];

    // удаляем узел
    tree->Del(tree1->GetNode(max), false);

    std::cout << "Была удалена вершина со средним значением из найденых: " << max << std::endl;

    std::cout << "------------------\n";
    tree->Show(TYPE_DIRECT);

    system("pause");
}


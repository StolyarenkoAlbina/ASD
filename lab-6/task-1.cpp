#include <iostream>
#include <windows.h>
#include <string>

#include "Stack.h"
#include "Queue.h"
#include "Deque.h"

using namespace std;

struct Student {
public:
    wstring Name;
    int Bilet = -1;
    int Quest = -1;
    bool OK = false;
    bool InQueue = false;
public:
    Student(wstring name) {
        this->Name = name;
    }
};

void ImitationOne() {
    Student* Students = new Student[5]{
        Student(wstring(L"Иванов")),
        Student(wstring(L"Сидоров")),
        Student(wstring(L"Кириллова")),
        Student(wstring(L"Михаденок")),
        Student(wstring(L"Кирилленко"))
    };

    Queue Queue(3);
    Deque Bilets(5);
    Stack Quests(5);

    for (int i = 0; i < 5; Bilets.Push_last(++i));
    for (int i = 0; i < 5; Quests.Push(++i));

    int ID = 0;
    int OK = 0;
    cout << "Преподаватель принимает пересдачу...\n";
    while (OK < 5)
    {  
        if (ID >= 5) ID = 0;

        if (!Students[ID].OK) {

            Sleep(rand() % 2000 + 1000);

            if (!Students[ID].InQueue && Queue.Push(ID) != MY_QUEUEOWERFLOW) {

                Students[ID].Bilet = (rand() % 2 == 0)
                    ? Bilets.Pop_first()
                    : Bilets.Pop_last();
                Students[ID].Quest = Quests.Pop();
                Students[ID].InQueue = true;

                cout << "Приходит ";
                wcout << Students[ID].Name.c_str();
                cout<< " берет билет №" << Students[ID].Bilet << " и задание №" << Students[ID].Quest << endl;

            }

            Sleep(rand() % 2000 + 1000);

            if (Queue.Count() > 0) {
                if (rand() % 30 < 20) {
                    int id = Queue.Pop();
                    Students[id].InQueue = false;
                    wcout << Students[id].Name.c_str();
                    cout << " идет отвечать и ";
                    if (rand() % 6 < 4) {
                        cout << "здает" << endl;
                        Students[id].OK = true;
                        OK++;
                        Bilets.Push_last(Students[id].Bilet);
                        Quests.Push(Students[id].Quest);
                    }
                    else {
                        cout << "не здает" << endl;
                        Queue.Push(id);
                        Students[id].InQueue = true;
                    }
                }
            }
            else
                cout << "Студентов пришедших на пересдачу нет\n";
        }
        ID++;
    }

    cout << "Все студенты сдали зачет\n";
}

int main()
{
    setlocale(0, "ru");
    int rand = 0; // 18641
    cout << "Введите случайное число: ";
    cin >> rand;

    srand(rand);

    ImitationOne();

    system("pause");

    return 0;
}

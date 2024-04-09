#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <string>
#include <iomanip>
using namespace std;

ifstream in("input.txt"); // входной файл
ofstream out("output.txt"); // выходной файл

struct Date{ // дата рождения
    int Year;
    int Month;
    int Day;
};

bool operator > (Date d1, Date d2){ // перегрузка для сравнения дат
    if (d1.Year > d2.Year) return true;
    else if (d1.Year == d2.Year){
        if (d1.Month > d2.Month) return true;
        else if (d1.Month == d2.Month && d1.Day > d2.Day) return true;
    }
    return false;
}

struct Person{ // информация о сотруднике
    string Name; // фамилия
    string Position; // должность
    Date DateOfBirth; // дата рождения
    int Experience; // стаж
    int Wage; // заработная плата
};

vector<Person> input(){ // парсинг входного файла
    vector<Person> people;
    while (in.peek() != EOF){
        Person p;
        string s, position;
        in >> p.Name;
        in >> s; in >> s;
        while (s.find("|") == string::npos){
            position += s + " ";
            in >> s;
        }
        p.Position = position;
        in >> s;
        p.DateOfBirth.Day = stoi(s.substr(0, 2));
        p.DateOfBirth.Month = stoi(s.substr(3, 2));
        p.DateOfBirth.Year = stoi(s.substr(6, 4));
        in >> s; in >> p.Experience;
        in >> s; in >> p.Wage;
        people.push_back(p);
    }
    return people;
}

void printDate(Date d){ // вывод даты
    out << setfill('0') << setw(2) << d.Day << "/" << setfill('0') << setw(2) << d.Month << "/" << d.Year;
}

void output(vector<Person> people){ // вывод таблицы с информацией о сотрудниках
    for (Person p : people){
        out << setfill(' ') << setw(11) << p.Name << " | " << setw(25) << p.Position << " |  ";
        printDate(p.DateOfBirth);
        out << "  | " << setfill(' ') << setw(2) << p.Experience << "  | " << p.Wage << endl;
    }
}

// 1. По зарплате, быстрая сортировка

void quicksort(vector<Person> &people, int l, int r){
    int i = l, j = r; // левый и правый края массива
    Person m = people[rand() % (r - l + 1) + l]; // опорный элемент выбирается случайным образом
    while (i <= j){
        while (people[i].Wage < m.Wage) i++; // идём слева направо, пока не встретим элемент, который больше или равен опорному
        while (people[j].Wage > m.Wage) j--; // идём справа налево, пока не встретим элемент, который меньше или равен опорному
        if (i <= j){ // если i > j, то все элементы слева от опорного меньше, справа - больше, чем опорный элемент, и цикл нужно прервать
            swap(people[i], people[j]);
            i++; j--; // чтобы повторно не рассматривать те элементы, которые поменяли местами
        }
    }
    if (j > l) quicksort(people, l, j); // сортируем левый подмассив
    if (i < r) quicksort(people, i, r); // сортируем правый подмассив
}

void task1(){
    vector<Person> people = input();
    quicksort(people, 0, people.size() - 1);
    output(people);
}

// 2. Сначала по году рождения, потом по стажу работы, сортировка расчёской

void hairbrush(vector<Person> &people){
    const double f = 1.247; // фактор уменьшения
    int N = people.size();
    int gap = N / f; // расстояние между сравниваемыми элементами
    if (gap < 1) gap = 1; // если N = 2
    while (gap >= 1){
        for (int j = 0; j < N - gap; ++j){ // рассматриваем все элементы, находящиеся на расстоянии gap друг от друга
            int Year1 = people[j].DateOfBirth.Year, Year2 = people[j + gap].DateOfBirth.Year, Exp1 = people[j].Experience, Exp2 = people[j + gap].Experience;
            if (Year1 > Year2 || (Year1 == Year2 && Exp1 > Exp2)){
                swap(people[j], people[j + gap]); // если элемент слева больше, чем элемент справа, то меняем их местами
            }
        }
        gap /= f;
    }
}

void task2(){
    vector<Person> people = input();
    hairbrush(people);
    output(people);
}

// 3. По дате рождения, сортировка перемешиванием

void cocktailsort(vector<Person> &people){
    int begin = -1, end = people.size() - 1; // начало и конец рассматриваемого подотрезка
    while (true){
        bool flag = false; // флаг, показывающий, был ли обмен
        ++begin;
        for (int j = begin; j < end; ++j){ // идём слева направо, меняя местами соседние элементы, если левый больше правого
            if (people[j].DateOfBirth > people[j + 1].DateOfBirth){
                swap(people[j], people[j + 1]); flag = true;
            }
        }
        if (flag == false) break; // если обменов не было, вектор уже отсортирован
        flag = false; --end;
        for (int j = end; j >= begin; --j){ // идём в обратную сторону, заменяя элементы по тому же принципу
            if (people[j].DateOfBirth > people[j + 1].DateOfBirth){
                swap(people[j], people[j + 1]);
            }
        }
       // минимум и максимум встали на свои места, их больше не учитываем (за счёт ++begin и --end) 
    }
}

void task3(){
    vector<Person> people = input();
    cocktailsort(people);
    output(people);
}

int main(){
    SetConsoleCP(1251); // установка кодировки win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодировки win-cp 1251 в поток вывода
    int task; cout << "Задание: "; cin >> task;
    switch(task){
        case 1: task1();
        case 2: task2();
        case 3: task3();
    }
    return 0;
}
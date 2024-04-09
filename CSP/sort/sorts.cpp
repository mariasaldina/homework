#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <string>
#include <iomanip>
using namespace std;

ifstream in("input.txt"); // ������� ����
ofstream out("output.txt"); // �������� ����

struct Date{ // ���� ��������
    int Year;
    int Month;
    int Day;
};

bool operator > (Date d1, Date d2){ // ���������� ��� ��������� ���
    if (d1.Year > d2.Year) return true;
    else if (d1.Year == d2.Year){
        if (d1.Month > d2.Month) return true;
        else if (d1.Month == d2.Month && d1.Day > d2.Day) return true;
    }
    return false;
}

struct Person{ // ���������� � ����������
    string Name; // �������
    string Position; // ���������
    Date DateOfBirth; // ���� ��������
    int Experience; // ����
    int Wage; // ���������� �����
};

vector<Person> input(){ // ������� �������� �����
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

void printDate(Date d){ // ����� ����
    out << setfill('0') << setw(2) << d.Day << "/" << setfill('0') << setw(2) << d.Month << "/" << d.Year;
}

void output(vector<Person> people){ // ����� ������� � ����������� � �����������
    for (Person p : people){
        out << setfill(' ') << setw(11) << p.Name << " | " << setw(25) << p.Position << " |  ";
        printDate(p.DateOfBirth);
        out << "  | " << setfill(' ') << setw(2) << p.Experience << "  | " << p.Wage << endl;
    }
}

// 1. �� ��������, ������� ����������

void quicksort(vector<Person> &people, int l, int r){
    int i = l, j = r; // ����� � ������ ���� �������
    Person m = people[rand() % (r - l + 1) + l]; // ������� ������� ���������� ��������� �������
    while (i <= j){
        while (people[i].Wage < m.Wage) i++; // ��� ����� �������, ���� �� �������� �������, ������� ������ ��� ����� ��������
        while (people[j].Wage > m.Wage) j--; // ��� ������ ������, ���� �� �������� �������, ������� ������ ��� ����� ��������
        if (i <= j){ // ���� i > j, �� ��� �������� ����� �� �������� ������, ������ - ������, ��� ������� �������, � ���� ����� ��������
            swap(people[i], people[j]);
            i++; j--; // ����� �������� �� ������������� �� ��������, ������� �������� �������
        }
    }
    if (j > l) quicksort(people, l, j); // ��������� ����� ���������
    if (i < r) quicksort(people, i, r); // ��������� ������ ���������
}

void task1(){
    vector<Person> people = input();
    quicksort(people, 0, people.size() - 1);
    output(people);
}

// 2. ������� �� ���� ��������, ����� �� ����� ������, ���������� ���������

void hairbrush(vector<Person> &people){
    const double f = 1.247; // ������ ����������
    int N = people.size();
    int gap = N / f; // ���������� ����� ������������� ����������
    if (gap < 1) gap = 1; // ���� N = 2
    while (gap >= 1){
        for (int j = 0; j < N - gap; ++j){ // ������������� ��� ��������, ����������� �� ���������� gap ���� �� �����
            int Year1 = people[j].DateOfBirth.Year, Year2 = people[j + gap].DateOfBirth.Year, Exp1 = people[j].Experience, Exp2 = people[j + gap].Experience;
            if (Year1 > Year2 || (Year1 == Year2 && Exp1 > Exp2)){
                swap(people[j], people[j + gap]); // ���� ������� ����� ������, ��� ������� ������, �� ������ �� �������
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

// 3. �� ���� ��������, ���������� ��������������

void cocktailsort(vector<Person> &people){
    int begin = -1, end = people.size() - 1; // ������ � ����� ���������������� ����������
    while (true){
        bool flag = false; // ����, ������������, ��� �� �����
        ++begin;
        for (int j = begin; j < end; ++j){ // ��� ����� �������, ����� ������� �������� ��������, ���� ����� ������ �������
            if (people[j].DateOfBirth > people[j + 1].DateOfBirth){
                swap(people[j], people[j + 1]); flag = true;
            }
        }
        if (flag == false) break; // ���� ������� �� ����, ������ ��� ������������
        flag = false; --end;
        for (int j = end; j >= begin; --j){ // ��� � �������� �������, ������� �������� �� ���� �� ��������
            if (people[j].DateOfBirth > people[j + 1].DateOfBirth){
                swap(people[j], people[j + 1]);
            }
        }
       // ������� � �������� ������ �� ���� �����, �� ������ �� ��������� (�� ���� ++begin � --end) 
    }
}

void task3(){
    vector<Person> people = input();
    cocktailsort(people);
    output(people);
}

int main(){
    SetConsoleCP(1251); // ��������� ��������� win-cp 1251 � ����� �����
    SetConsoleOutputCP(1251); // ��������� ��������� win-cp 1251 � ����� ������
    int task; cout << "�������: "; cin >> task;
    switch(task){
        case 1: task1();
        case 2: task2();
        case 3: task3();
    }
    return 0;
}
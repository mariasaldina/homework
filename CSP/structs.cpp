#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

struct queue{ // �������
    int inf; // ��������
    queue *next; // ���������� �� ��������� �������
};

void push_queue(queue *&h, queue *&t, int x){ // ���������� �������� � ����� �������
    queue *r = new queue; // ����� ������� �������
    r->inf = x;
    r->next = nullptr;
    if (!h && !t){ // ���� ������� �����
        h = t = r; // ���� ����� ������� - � ������, � ����� ������������
    }
    else{
        t->next = r; // ������ ����� ��������� �� ����� �������
        t = r; // ����� ������� - ��� �����
    }
}

void print_queue(queue *&h){ // ����� �������
    queue *r = h;
    while (r != nullptr) {
        cout << r->inf << " ";
        r = r->next;
    }
}

// 1. ������� ������� �� ����� �����. ��������� ����������� ����� ������� ���, ����� �� ������ ����� ��� ������ ������������ �������.
void task1(){
    int n, x, max = 0;
    cout << "������� ����� ��������� � �������: "; cin >> n;
    queue *h = nullptr, *t = nullptr, *max_p, *prev = nullptr, *prev_max = nullptr;
    for (int i = 0; i < n; ++i){ // ��������� �������, ����������� ���� ������������ �������
        cin >> x;
        push_queue(h, t, x);
        if (x > max){
            max = x;
            max_p = t;
            prev_max = prev;
        }
        prev = t;
    }
    if (h->inf != max){ // ���� ������ �������� ��� �� ��������� �� ������ �����
        t->next = h; // ����� ������ ������ � �������
        h = max_p; // ������ - ��� ������ ��������
        t = prev_max; // ����� ����� - ��� �������, �������������� ���������
        t->next = nullptr;
    }
    print_queue(h);
}

// 2. ������� �������, ���������� ����� �����. ����� ���� �����, ������ ������������� �����, �������� ��������� ������ �������.
void task2(){
    int n, x, max = 0, ch;
    cout << "������� ����� ��������� � �������: "; cin >> n;
    queue *h = nullptr, *t = nullptr;
    for (int i = 0; i < n; ++i){ // ��������� �������, ����������� ���� ������������ � ��������� ������ ��������
        cin >> x;
        push_queue(h, t, x);
        if (x > max) max = x;
        if (x % 2 == 0) ch = x;
    }
    queue *r = h;
    while (r != nullptr){ // ���������� �� ������� �� ������ � ������
        if (r->inf == max){ // ���� ��������� ������������ �������
            queue *p = new queue; // ������� ����� ������� �������
            p->inf = ch;
            p->next = r->next; // ��������� ��� �� ��������� �� ���������� ���������
            r->next = p; // � � ����� ����������
            r = p->next; // ��������� � ���������� ��������
        }
        else r = r->next;
    }
    print_queue(h);
}

struct stack{ // ����
    int inf;
    stack *next;
};

void push_stack(stack *&h, int x){ // ���������� �������� � ����� �����
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

int pop_stack(stack *&h){ // �������� �������� �� �����
    int i = h->inf; // ��������� �������� ������
    stack *r = h; // ��������� ��������� �� ������ 
    h = h->next; // ��������� ������ �� ��������� �������
    delete r; // ������� ��������� �� ������
    return i; // ���������� �������� ��������
}

void print_stack(stack *h){ // ����� �����
    stack *r = h;
    while (r){
        cout << r->inf << " ";
        r = r->next;
    }
}

void reverse(stack *&h){ // ������ ��������� ����� � �������� �������
    stack *h1 = nullptr; // ����� ����
    while (h){
        push_stack(h1, pop_stack(h)); // ������� �������� �� ������� ����� � ���������� � �����
    }
    h = h1; // ��������� ��������� �� ����� ������
}

vector<bool> prime_numbers(int max){ // ����� ������� ����� ������� ����������
    vector<bool> a(max + 1);
    a[1] = 0; a[2] = 1;
    for (int i = 3; i <= max; ++i)
        a[i] = i % 2;
    for (int i = 3; i * i <= max; i += 2){
        if (a[i]) for (int j = i * i; j <= max; j += 2 * i) a[j] = 0;
    }
    return a;
}

// 3. ������� ����, ���������� ����� �����. ����� ���� ������� ����� �������� ����� �����.
// ������� ���������� � ���������� ������ ��������� � �������� ���������� �����.
void task3(){
    int n, x, insert, max = 0;
    cout << "������� ����� ��������� � �����: "; cin >> n;
    cout << "������� �����, ������� ����� ��������: "; cin >> insert;
    stack *h = nullptr;
    for (int i = 0; i < n; ++i){ // ��������� ����, ���� ������������ �������
        cin >> x;
        push_stack(h, x);
        if (max < x) max = x;
    }
    vector<bool> prime = prime_numbers(max); // ���� ������� �����
    reverse(h); // ������ ������� �� ��������
    stack *r = h;
    while (r){ // ��������� �����
        if (prime[r->inf]){
            stack *t = new stack;
            t->inf = insert;
            t->next = r->next;
            r->next = t;
            r = t->next;
        }
        else r = r->next;
    }
    print_stack(h);
}

// 4. ������� ����, ���������� ����� ����� �� 0 �� 20. � ����� ���� ������� ������� �����������,
// ����� ���������� �����. ������� ���������� ����� � ����� ����� ������ ��������� � ��������������.
void task4(){
    int n, x;
    cout << "������� ����� ��������� � �����: "; cin >> n;
    stack *h = nullptr, *h1 = nullptr;
    for (int i = 0; i < n; ++i){ // ��������� ����
        cin >> x;
        while (x > 20 || x < 0){ // ��������� ������ �� ������������
            cout << "����� �� ������ ��������� 20\n";
            cin >> x;
        }
        push_stack(h, x);
        if (x / 10 == 0) push_stack(h1, x); // ����������� ����� ����� � ����� ����
    }
    reverse(h); // ������ ������� � �������� ����� �� ��������
    stack *r = h;
    while (r){
        if (r->inf / 10 != 0) push_stack(h1, r->inf); // ��������� � ����� ���� ���������� �����
        r = r->next;
    }
    print_stack(h1);
}

int main(){
    SetConsoleCP(1251); // ��������� ��������� win-cp 1251 � ����� �����
    SetConsoleOutputCP(1251); // ��������� ��������� win-cp 1251 � ����� ������
    int task; cout << "�������: "; cin >> task;
    switch(task){
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
    }
    return 0;
}
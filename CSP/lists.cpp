#include <iostream>
#include <vector>
#include <Windows.h>
#include <time.h>

using namespace std;

struct list{
    int inf;
    list *next;
    list *prev;
};

void push_list(list *&h, list *&t, int x){
    list *r = new list;
    r->inf = x;
    r->next = nullptr;
    if (!h && !t){
        r->prev = nullptr;
        h = r;
    }
    else{
        r->prev = t;
        t->next = r;
    }
    t = r;
}

void create_list(int &n, list *&h, list *&t, int &max){
    cout << "Введите количество элементов в списке: ";
    cin >> n;
    int x;
    for (int i = 0; i < n; ++i){
        cin >> x;
        if (x > max) max = x;
        push_list(h, t, x);
    }
}

void remove_list(list *&h, list *&t, list *&r){
    if (r == h && r == t){
        h = t = nullptr;
    }
    else if (r == h){
        h = h->next;
        h->prev = nullptr;
    }
    else if (r == t){
        t = t->prev;
        t->next = nullptr;
    }
    else{
        r->next->prev = r->prev;
        r->prev->next = r->next;
    }
    delete r;
}

void print_list(list *h){
    list *r = h;
    while (r){
        cout << r->inf << " ";
        r = r->next;
    }
}

void task1(){
    int n, max = 0;
    list *h = nullptr, *t = nullptr;
    create_list(n, h, t, max);
    list *r = h;
    while (r){
        if (r->inf == max){
            remove_list(h, t, r);
            break;
        }
        r = r->next;
    }
    r = t;
    while (r){
        if (r->inf == max){
            remove_list(h, t, r);
            break;
        }
        r = r->prev;
    }
    print_list(h);
}

void insert_after(list *&h, list *&t, list *&r, int x){
    if (r == t){
        push_list(h, t, x);
    }
    else{
        list *p = new list;
        p->inf = x;
        r->next->prev = p;
        p->next = r->next;
        p->prev = r;
        r->next = p;
    }
}

void task2(){
    int n, max = 0, value, i = 0;
    list *h = nullptr, *t = nullptr;
    create_list(n, h, t, max);
    list *r = h;
    while (r && i < n){
        list *r_next = r->next;
        if (r->inf % 2 != 0){
            value = r->inf;
            remove_list(h, t, r);
            insert_after(h, t, t, value);
        }
        r = r_next;
        i++;
    }
    print_list(h);
}

void swap_list(list *&i, list *&j, list *&h, list *&t, list *&r, list *&l){
    list *i_prev = i->prev, *i_next = i->next;
    if (i->next == j){
        if (i != h) i->prev->next = j;
        j->prev = i->prev;
        if (j != t) j->next->prev = i;
        i->next = j->next;
        j->next = i;
        i->prev = j;
    }
    else{
        if (i != t) i->next->prev = j;
        if (i != h) i->prev->next = j;
        if (j != t) j->next->prev = i;
        if (j != h) j->prev->next = i;
        i->next = j->next;
        i->prev = j->prev;
        j->next = i_next;
        j->prev = i_prev;
    }
    if (i == h) h = j;
    if (j == t) t = i;
    if (i == l) l = j;
    if (j == r) r = i;
}

bool no_more(list* i, list* j){
    if (j->next != i && (!j->next || j->next->next != i)) return true;
    return false;
}

void quick_sort(list *&l, list *&r, list *&h, list *&t){
    list *i = l, *j = r;
    int mid = (l->inf + r->inf) / 2;
    while (j && i && no_more(i, j)){
        while (i && i->inf < mid) i = i->next;
        while (j && j->inf > mid) j = j->prev;
        cout << i->inf << " " << j->inf << endl;
        if (no_more(i, j)){
            swap_list(i, j, h, t, r, l);
            swap(i, j);
            j = j->prev;
            i = i->next;
            print_list(h);
            cout << endl;
        }
    }
    if (i && j && l != j && j->next != l){
        quick_sort(l, j, h, t);
    }
    if (i && j && r != i && i->prev != r){
        quick_sort(i, r, h, t);
    }
    
}

void create_list_3(int &n, list *&h, list *&t){
    cout << "Введите количество элементов в списке: ";
    cin >> n;
    int x;
    for (int i = 0; i < n; ++i){
        cin >> x;
        push_list(h, t, x);
    }
}

void task3(){
    int n;
    list *h = nullptr, *t = nullptr;
    vector<list*> address;
    create_list_3(n, h, t);
    quick_sort(h, t, h, t);
    print_list(h);
}

int main(){
    SetConsoleCP(1251); // установка кодировки win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодировки win-cp 1251 в поток вывода
    int task; cout << "Задание: "; cin >> task;
    switch(task){
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
    }
    return 0;
}
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

struct queue{ // очередь
    int inf; // значение
    queue *next; // указаетель на следующий элемент
};

void push_queue(queue *&h, queue *&t, int x){ // добавление элемента в конец очереди
    queue *r = new queue; // новый элемент очереди
    r->inf = x;
    r->next = nullptr;
    if (!h && !t){ // если очередь пуста
        h = t = r; // этот новый элемент - и голова, и хвост одновременно
    }
    else{
        t->next = r; // бывший хвост ссылается на новый элемент
        t = r; // новый элемент - это хвост
    }
}

void print_queue(queue *&h){ // вывод очереди
    queue *r = h;
    while (r != nullptr) {
        cout << r->inf << " ";
        r = r->next;
    }
}

// 1. Создать очередь из целых чисел. Выполнить циклический сдвиг очереди так, чтобы на первом месте был первый максимальный элемент.
void task1(){
    int n, x, max = 0;
    cout << "Введите число элементов в очереди: "; cin >> n;
    queue *h = nullptr, *t = nullptr, *max_p, *prev = nullptr, *prev_max = nullptr;
    for (int i = 0; i < n; ++i){ // заполняем очередь, параллельно ищем максимальный элемент
        cin >> x;
        push_queue(h, t, x);
        if (x > max){
            max = x;
            max_p = t;
            prev_max = prev;
        }
        prev = t;
    }
    if (h->inf != max){ // если первый максимум ещё не находится на первом месте
        t->next = h; // хвост теперь связан с головой
        h = max_p; // голова - это первый максимум
        t = prev_max; // новый хвост - это элемент, предшествующий максимуму
        t->next = nullptr;
    }
    print_queue(h);
}

// 2. Создать очередь, содержащую целые числа. После всех чисел, равных максимальному числу, вставить последний четный элемент.
void task2(){
    int n, x, max = 0, ch;
    cout << "Введите число элементов в очереди: "; cin >> n;
    queue *h = nullptr, *t = nullptr;
    for (int i = 0; i < n; ++i){ // заполняем очередь, параллельно ищем максимальный и последний чётный элементы
        cin >> x;
        push_queue(h, t, x);
        if (x > max) max = x;
        if (x % 2 == 0) ch = x;
    }
    queue *r = h;
    while (r != nullptr){ // проходимся по очереди от головы к хвосту
        if (r->inf == max){ // если встретили максимальный элемент
            queue *p = new queue; // создаем новый элемент очереди
            p->inf = ch;
            p->next = r->next; // связываем его со следующим за максимумом элементом
            r->next = p; // и с самим максимумом
            r = p->next; // переходим к следующему элементу
        }
        else r = r->next;
    }
    print_queue(h);
}

struct stack{ // стек
    int inf;
    stack *next;
};

void push_stack(stack *&h, int x){ // добавление элемента в конец стека
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

int pop_stack(stack *&h){ // удаление элемента из стека
    int i = h->inf; // сохраняем значение головы
    stack *r = h; // сохраняем указатель на голову 
    h = h->next; // переносим голову на следующий элемент
    delete r; // удаляем указатель на голову
    return i; // возвращаем удалённое значение
}

void print_stack(stack *h){ // вывод стека
    stack *r = h;
    while (r){
        cout << r->inf << " ";
        r = r->next;
    }
}

void reverse(stack *&h){ // запись элементов стека в обратном порядке
    stack *h1 = nullptr; // новый стек
    while (h){
        push_stack(h1, pop_stack(h)); // удаляем элементы из старого стека и записываем в новый
    }
    h = h1; // сохраняем указатель на новую голову
}

vector<bool> prime_numbers(int max){ // поиск простых чисел решетом Эратосфена
    vector<bool> a(max + 1);
    a[1] = 0; a[2] = 1;
    for (int i = 3; i <= max; ++i)
        a[i] = i % 2;
    for (int i = 3; i * i <= max; i += 2){
        if (a[i]) for (int j = i * i; j <= max; j += 2 * i) a[j] = 0;
    }
    return a;
}

// 3. Создать стек, содержащий целые числа. После всех простых чисел вставить новое число.
// Порядок следования в результате должен совпадать с порядком следования ввода.
void task3(){
    int n, x, insert, max = 0;
    cout << "Введите число элементов в стеке: "; cin >> n;
    cout << "Введите число, которое нужно вставить: "; cin >> insert;
    stack *h = nullptr;
    for (int i = 0; i < n; ++i){ // заполняем стек, ищем максимальный элемент
        cin >> x;
        push_stack(h, x);
        if (max < x) max = x;
    }
    vector<bool> prime = prime_numbers(max); // ищем простые числа
    reverse(h); // меняем порядок на обратный
    stack *r = h;
    while (r){ // вставляем число
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

// 4. Создать стек, содержащий целые числа от 0 до 20. В новый стек вывести сначала однозначные,
// потом двузначные числа. Порядок следования чисел в новом стеке должен совпадать с первоначальным.
void task4(){
    int n, x;
    cout << "Введите число элементов в стеке: "; cin >> n;
    stack *h = nullptr, *h1 = nullptr;
    for (int i = 0; i < n; ++i){ // заполняем стек
        cin >> x;
        while (x > 20 || x < 0){ // проверяем данные на корректность
            cout << "Числа не должны превышать 20\n";
            cin >> x;
        }
        push_stack(h, x);
        if (x / 10 == 0) push_stack(h1, x); // однозначные числа кладём в новый стек
    }
    reverse(h); // меняем порядок в исходном стеке на обратный
    stack *r = h;
    while (r){
        if (r->inf / 10 != 0) push_stack(h1, r->inf); // добавляем в новый стек двузначные числа
        r = r->next;
    }
    print_stack(h1);
}

int main(){
    SetConsoleCP(1251); // установка кодировки win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодировки win-cp 1251 в поток вывода
    int task; cout << "Задание: "; cin >> task;
    switch(task){
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
    }
    return 0;
}
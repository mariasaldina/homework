#include <iostream>
#include <vector>
#include <Windows.h>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

template <typename T>
struct queue{ // очередь
    T inf;
    queue *next;
};

template <typename T>
void push_queue(queue<T> *&h, queue<T> *&t, T x){ // добавление элемента в конец очереди
    queue<T> *r = new queue<T>;
    r->inf = x;
    r->next = nullptr;
    if (!h && !t){
        h = t = r;
    }
    else{
        t->next = r;
        t = r;
    }
}

template <typename T>
T pop_queue(queue<T> *&h, queue<T> *&t){ // удаление элемента из начала очереди
    int x = h->inf;
    queue<T> *p = h;
    h = h->next;
    if (!h) t = nullptr;
    delete p;
    return x;
}

template <typename T>
struct stack{ // стек
    T inf;
    stack *next;
};

template <typename T>
void push_stack(stack<T> *&h, T x){ // добавление элемента в стек
    stack<T> *r = new stack<T>;
    r->inf = x;
    r->next = h;
    h = r;
}

template <typename T>
T pop_stack(stack<T> *&h){ // удаление элемента из стека
    stack<T> *r = h;
    int x = h->inf;
    h = h->next;
    delete r;
    return x;
}

template <typename T>
void bfs(map<T, vector<T>> gr, map<T, bool> &used, int n, T x){ // обход графа в ширину
    used[x] = 1; // помечаем первую вершину как посещённую
    cout << x << " ";
    queue<T> *h = nullptr, *t = nullptr; // создаём очередь
    push_queue(h, t, x); // помещаем вершину в очередь
    while (h){ // пока очередь не пуста
        x = pop_queue(h, t); // удаляем голову из очереди
        for (int i = 0; i < gr[x].size(); ++i){ // проходимся по списку смежных с текущей вершин
            if (!used[gr[x][i]]){ // если эту вершину ещё не посетили
                T y = gr[x][i];
                used[y] = 1; // помечаем её как посещённую
                push_queue(h, t, y); // и добавляем в очередь
                cout << y << " ";
            }
        }
    }
}

template <typename T>
void dfs(map<T, vector<T>> gr, map<T, bool> &used, int n, T x){ // обход графа в глубину
    stack<T> *h = nullptr; // создаём стек
    push_stack(h, x); // добавляем в него первую вершину
    used[x] = 1; // помечаем её как посещённую
    cout << x << " ";
    bool flag = 0; T y;
    while (h){ // пока стек не пуст
        x = h->inf; // рассматриваем голову стека
        for (int i = 0; i < gr[x].size(); ++i){ 
            if (!used[gr[x][i]]){ // если находим непосещённую вершину, прерываем цикл
                y = gr[x][i];
                flag = 1;
                break;
            }
        }
        if (flag){ // если нашли вершину
            push_stack(h, y); // добавляем её в стек (чтобы затем вернуться и начать с неё)
            used[y] = 1; // помечаем её как посещённую
            cout << y << " ";
        }
        else pop_stack(h); // иначе удаляем голову стека
        flag = 0;
    }
}

template <typename T>
map<T, vector<T>> create_graph(int &n, T){ // считываем граф
    cout << "Введите количество вершин: ";
    cin >> n;
    T x, y;
    int m; 
    map<T, vector<T>> graph;
    cout << "Введите вершины в соответствии с форматом: <вершина> <число_связанных_вершин> <вершина_1> <вершина_2> ... <вершина_n>\n";
    for (int i = 0; i < n; ++i){
        cin >> x >> m;
        vector<T> a(m);
        for (int j = 0; j < m; ++j){
            cin >> y;
            a[j] = y;
        }
        graph[x] = a;
    }
    return graph;
}

template <typename T>
void task(T c){
    int n; T x;
    map<T, vector<T>> gr = create_graph(n, c);
    map<T, bool> used;
    for (auto it = gr.begin(); it != gr.end(); ++it) used[it->first] = 0;
    cout << "Введите вершину, с которой начинается обход в ширину: ";
    cin >> x;
    bfs(gr, used, n, x);
    for (auto it = used.begin(); it != used.end(); ++it) it->second = 0;
    cout << endl;
    cout << "Введите вершину, с которой начинается обход в глубину: ";
    cin >> x;
    dfs(gr, used, n, x);
}

int main(){
    SetConsoleCP(1251); // установка кодировки win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодировки win-cp 1251 в поток вывода
    string type;
    cout << "Выберите тип вершин графа (введите integer/char): ";
    cin >> type;
    if (type == "integer") task(0);
    else task('a');
    return 0;
}
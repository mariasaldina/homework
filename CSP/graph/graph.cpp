#include <iostream>
#include <vector>
#include <Windows.h>
#include <algorithm>
#include <string>

using namespace std;

struct queue{ // очередь
    int inf;
    queue *next;
};

void push_queue(queue *&h, queue *&t, int x){ // добавление элемента в конец очереди
    queue *r = new queue;
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

int pop_queue(queue *&h, queue *&t){ // удаление элемента из начала очереди
    int x = h->inf;
    queue *p = h;
    h = h->next;
    if (!h) t = nullptr;
    delete p;
    return x;
}

struct stack{ // стек
    int inf;
    stack *next;
};

void push_stack(stack *&h, int x){ // добавление элемента в стек
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

int pop_stack(stack *&h){ // удаление элемента из стека
    stack *r = h;
    int x = h->inf;
    h = h->next;
    delete r;
    return x;
}

void bfs(vector<vector<int>> gr, vector<bool> &used, int n, int x){ // обход графа в ширину
    used[x] = 1; // помечаем первую вершину как посещённую
    cout << x << " ";
    queue *h = nullptr, *t = nullptr; // создаём очередь
    push_queue(h, t, x); // помещаем вершину в очередь
    while (h){ // пока очередь не пуста
        x = pop_queue(h, t); // удаляем голову из очереди
        for (int i = 0; i < gr[x].size(); ++i){ // проходимся по списку смежных с текущей вершин
            if (!used[gr[x][i]]){ // если эту вершину ещё не посетили
                int y = gr[x][i];
                used[y] = 1; // помечаем её как посещённую
                push_queue(h, t, y); // и добавляем в очередь
                cout << y << " ";
            }
        }
    }
    auto not_used = find(used.begin() + 1, used.end(), 0); // если остались непосещённые вершины
    if (not_used != used.end()) bfs(gr, used, n, *not_used);
}

void dfs(vector<vector<int>> gr, vector<bool> &used, int n, int x){ // обход графа в глубину
    stack *h = nullptr; // создаём стек
    push_stack(h, x); // добавляем в него первую вершину
    used[x] = 1; // помечаем её как посещённую
    cout << x << " ";
    bool flag = 0; int y;
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
    auto not_used = find(used.begin() + 1, used.end(), 0); // если остались непосещённые вершины
    if (not_used != used.end()) dfs(gr, used, n, *not_used);
}

vector<vector<int>> create_graph(int &n){ // считывем граф
    cout << "Enter the number of vertices: ";
    int x, y; cin >> n; n++;
    string s;
    vector<vector<int>> graph(n);
    cout << "Enter the graph according to this format: <vertice> : <v_1> <v_2> ... <v_n> ;\n";
    for (int i = 1; i < n; ++i){
        vector<int> a;
        cin >> x >> s;
        while (s != ";"){
            cin >> s;
            if (isdigit(s[0])){
                y = stoi(s);
                a.push_back(y);
            }
        }
        graph[x] = a;
    }
    return graph;
}

void task(){
    int n, x;
    vector<vector<int>> gr = create_graph(n);
    vector<bool> used(n, 0);
    cout << "Enter the vertice to start with: ";
    cin >> x;
    bfs(gr, used, n, x);
    for (int i = 0; i < n; ++i) used[i] = 0;
    cout << endl;
    cout << "Enter the vertice to start with: ";
    cin >> x;
    dfs(gr, used, n, x);
}

int main(){
    task();
    return 0;
}
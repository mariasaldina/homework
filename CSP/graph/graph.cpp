#include <iostream>
#include <vector>
#include <Windows.h>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

template <typename T>
struct queue{ // �������
    T inf;
    queue *next;
};

template <typename T>
void push_queue(queue<T> *&h, queue<T> *&t, T x){ // ���������� �������� � ����� �������
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
T pop_queue(queue<T> *&h, queue<T> *&t){ // �������� �������� �� ������ �������
    int x = h->inf;
    queue<T> *p = h;
    h = h->next;
    if (!h) t = nullptr;
    delete p;
    return x;
}

template <typename T>
struct stack{ // ����
    T inf;
    stack *next;
};

template <typename T>
void push_stack(stack<T> *&h, T x){ // ���������� �������� � ����
    stack<T> *r = new stack<T>;
    r->inf = x;
    r->next = h;
    h = r;
}

template <typename T>
T pop_stack(stack<T> *&h){ // �������� �������� �� �����
    stack<T> *r = h;
    int x = h->inf;
    h = h->next;
    delete r;
    return x;
}

template <typename T>
void bfs(map<T, vector<T>> gr, map<T, bool> &used, int n, T x){ // ����� ����� � ������
    used[x] = 1; // �������� ������ ������� ��� ����������
    cout << x << " ";
    queue<T> *h = nullptr, *t = nullptr; // ������ �������
    push_queue(h, t, x); // �������� ������� � �������
    while (h){ // ���� ������� �� �����
        x = pop_queue(h, t); // ������� ������ �� �������
        for (int i = 0; i < gr[x].size(); ++i){ // ���������� �� ������ ������� � ������� ������
            if (!used[gr[x][i]]){ // ���� ��� ������� ��� �� ��������
                T y = gr[x][i];
                used[y] = 1; // �������� � ��� ����������
                push_queue(h, t, y); // � ��������� � �������
                cout << y << " ";
            }
        }
    }
}

template <typename T>
void dfs(map<T, vector<T>> gr, map<T, bool> &used, int n, T x){ // ����� ����� � �������
    stack<T> *h = nullptr; // ������ ����
    push_stack(h, x); // ��������� � ���� ������ �������
    used[x] = 1; // �������� � ��� ����������
    cout << x << " ";
    bool flag = 0; T y;
    while (h){ // ���� ���� �� ����
        x = h->inf; // ������������� ������ �����
        for (int i = 0; i < gr[x].size(); ++i){ 
            if (!used[gr[x][i]]){ // ���� ������� ������������ �������, ��������� ����
                y = gr[x][i];
                flag = 1;
                break;
            }
        }
        if (flag){ // ���� ����� �������
            push_stack(h, y); // ��������� � � ���� (����� ����� ��������� � ������ � ��)
            used[y] = 1; // �������� � ��� ����������
            cout << y << " ";
        }
        else pop_stack(h); // ����� ������� ������ �����
        flag = 0;
    }
}

template <typename T>
map<T, vector<T>> create_graph(int &n, T){ // ��������� ����
    cout << "������� ���������� ������: ";
    cin >> n;
    T x, y;
    int m; 
    map<T, vector<T>> graph;
    cout << "������� ������� � ������������ � ��������: <�������> <�����_���������_������> <�������_1> <�������_2> ... <�������_n>\n";
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
    cout << "������� �������, � ������� ���������� ����� � ������: ";
    cin >> x;
    bfs(gr, used, n, x);
    for (auto it = used.begin(); it != used.end(); ++it) it->second = 0;
    cout << endl;
    cout << "������� �������, � ������� ���������� ����� � �������: ";
    cin >> x;
    dfs(gr, used, n, x);
}

int main(){
    SetConsoleCP(1251); // ��������� ��������� win-cp 1251 � ����� �����
    SetConsoleOutputCP(1251); // ��������� ��������� win-cp 1251 � ����� ������
    string type;
    cout << "�������� ��� ������ ����� (������� integer/char): ";
    cin >> type;
    if (type == "integer") task(0);
    else task('a');
    return 0;
}
#include <iostream>
#include <vector>
#include <Windows.h>
#include <algorithm>
#include <string>

using namespace std;

struct queue{ // �������
    int inf;
    queue *next;
};

void push_queue(queue *&h, queue *&t, int x){ // ���������� �������� � ����� �������
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

int pop_queue(queue *&h, queue *&t){ // �������� �������� �� ������ �������
    int x = h->inf;
    queue *p = h;
    h = h->next;
    if (!h) t = nullptr;
    delete p;
    return x;
}

struct stack{ // ����
    int inf;
    stack *next;
};

void push_stack(stack *&h, int x){ // ���������� �������� � ����
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

int pop_stack(stack *&h){ // �������� �������� �� �����
    stack *r = h;
    int x = h->inf;
    h = h->next;
    delete r;
    return x;
}

void bfs(vector<vector<int>> gr, vector<bool> &used, int n, int x){ // ����� ����� � ������
    used[x] = 1; // �������� ������ ������� ��� ����������
    cout << x << " ";
    queue *h = nullptr, *t = nullptr; // ������ �������
    push_queue(h, t, x); // �������� ������� � �������
    while (h){ // ���� ������� �� �����
        x = pop_queue(h, t); // ������� ������ �� �������
        for (int i = 0; i < gr[x].size(); ++i){ // ���������� �� ������ ������� � ������� ������
            if (!used[gr[x][i]]){ // ���� ��� ������� ��� �� ��������
                int y = gr[x][i];
                used[y] = 1; // �������� � ��� ����������
                push_queue(h, t, y); // � ��������� � �������
                cout << y << " ";
            }
        }
    }
    auto not_used = find(used.begin() + 1, used.end(), 0); // ���� �������� ������������ �������
    if (not_used != used.end()) bfs(gr, used, n, *not_used);
}

void dfs(vector<vector<int>> gr, vector<bool> &used, int n, int x){ // ����� ����� � �������
    stack *h = nullptr; // ������ ����
    push_stack(h, x); // ��������� � ���� ������ �������
    used[x] = 1; // �������� � ��� ����������
    cout << x << " ";
    bool flag = 0; int y;
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
    auto not_used = find(used.begin() + 1, used.end(), 0); // ���� �������� ������������ �������
    if (not_used != used.end()) dfs(gr, used, n, *not_used);
}

vector<vector<int>> create_graph(int &n){ // �������� ����
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
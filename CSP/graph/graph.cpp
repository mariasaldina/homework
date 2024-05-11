#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <Windows.h>
using namespace std;

template <typename T>
map<T, bool> bfs(map<T, vector<T>> gr, T x){ // ����� ����� � ������
    map<T, bool> used;
    for (auto it = gr.begin(); it != gr.end(); ++it){
        used[it->first] = 0;
    }
    used[x] = 1; // �������� ������ ������� ��� ����������
    queue<T> h; // ������ �������
    h.push(x); // �������� ������� � �������
    while (h.size()){ // ���� ������� �� �����
        x = h.front(); // ��������� �������� ������
        h.pop(); // ������� ������ �� �������
        for (int i = 0; i < gr[x].size(); ++i){ // ���������� �� ������ ������� � ������� ������
            if (!used[gr[x][i]]){ // ���� ��� ������� ��� �� ��������
                T y = gr[x][i];
                used[y] = 1; // �������� � ��� ����������
                h.push(y); // � ��������� � �������
            }
        }
    }
    return used;
}

// ����� ����� � �������. � ������ vertices ������� ���������� � ��� �������, � ������� �� �������� �� ��� ��� ������
template <typename T>
void dfs1(map<T, vector<T>> gr, vector<T> &vertices, map<T, bool> &used, T x){
    stack<T> h; // ������ ����
    h.push(x); // ��������� � ���� ������ �������
    used[x] = 1; // �������� � ��� ����������
    bool flag = 0; T y;
    while (h.size()){ // ���� ���� �� ����
        x = h.top(); // ������������� ������ �����
        for (int i = 0; i < gr[x].size(); ++i){ 
            if (!used[gr[x][i]]){ // ���� ������ ������������ ������� ����� �������
                y = gr[x][i];
                flag = 1;
                break;
            }
        }
        if (flag){ // ���� ����� ������������ �������
            h.push(y); // ��������� � � ���� (����� ����� ��������� � ������ � ��)
            used[y] = 1; // �������� � ��� ����������
        }
        else{
            vertices.push_back(h.top()); // ������� �� �������
            h.pop(); // � ������� ������ �����
        }
        flag = 0;
    }
}

// ����� ����� � �������. ���������� ������ ������ ����������
template <typename T>
vector<T> dfs2(map<T, bool> &used, map<T, vector<T>> gr, T x){
    stack<T> h; // ������ ����
    h.push(x); // ��������� � ���� ������ �������
    used[x] = 1; // �������� � ��� ����������
    bool flag = 0; T y;
    vector<T> component; // ������ ������ ����������
    component.push_back(x);
    while (h.size()){ // ���� ���� �� ����
        x = h.top(); // ������������� ������ �����
        for (int i = 0; i < gr[x].size(); ++i){ 
            if (!used[gr[x][i]]){ // ���� ������ ������������ ������� ����� �������
                y = gr[x][i];
                flag = 1;
                break;
            }
        }
        if (flag){ // ���� ����� ������������ �������
            h.push(y); // ��������� � � ���� (����� ����� ��������� � ������ � ��)
            used[y] = 1; // �������� � ��� ����������
            component.push_back(y);
        }
        else h.pop(); // ����� ������� ������ �����
        flag = 0;
    }
    return component;
}

// �������� ������ ����

vector<pair<int, int>> parce_int(ifstream &in){ // ���� ������� - �����
    string str;
    vector<pair<int, int>> pairs;
    pair<int, int> new_pair;
    while (in.peek() != EOF){
        getline(in, str);
        size_t space = str.find("-");
        new_pair.first = stoi(str.substr(0, space));
        new_pair.second = stoi(str.substr(space + 1, str.length() - space));
        pairs.push_back(new_pair);
    }
    return pairs;
}

vector<pair<char, char>> parce_char(ifstream &in){ // ���� ������� - �������
    string str;
    vector<pair<char, char>> pairs;
    pair<char, char> new_pair;
    while (in.peek() != EOF){
        getline(in, str);
        new_pair.first = str.front();
        new_pair.second = str.back();
        pairs.push_back(new_pair);
    }
    return pairs;
}

vector<pair<string, string>> parce_string(ifstream &in){ // ���� ������� - ������
    string str;
    vector<pair<string, string>> pairs;
    pair<string, string> new_pair;
    while (in.peek() != EOF){
        getline(in, str);
        size_t space = str.find("-");
        new_pair.first = str.substr(0, space);
        new_pair.second = str.substr(space + 1, str.length() - space);
        pairs.push_back(new_pair);
    }
    return pairs;
}

template <typename T>
void print_graph(map<T, vector<T>> graph){ // ����� ����� � ���� ������ ���������
    for (auto it = graph.begin(); it != graph.end(); ++it, cout << endl){
        T vertice = it->first;
        cout << vertice << ": ";
        for (int i = 0; i < graph[vertice].size(); ++i){
            cout << graph[vertice][i] << " ";
        }
    }
}

template <typename T>
map<T, vector<T>> create_graph(vector<pair<T, T>> pairs, bool flag){ // �������� ����� �� ������ ����
    map<T, vector<T>> graph;
    T x, y;
    for (int i = 0; i < pairs.size(); ++i){
        x = pairs[i].first;
        y = pairs[i].second;
        graph[x].push_back(y);
        if (!flag) graph[y].push_back(x); // ���� ���� �����������������
        else{
            if (graph.find(y) == graph.end()) graph[y] = {}; // ���� ���������������
        }
    }
    for (auto it = graph.begin(); it != graph.end(); ++it){
        sort(it->second.begin(), it->second.end()); // ��������� ������ ��� ������ �������
        it->second.erase(unique(it->second.begin(), it->second.end()), it->second.end()); // ������� ���������
    }
    return graph;
}

template <typename T>
void insert_edge(map<T, vector<T>> &graph, T v1, T v2){ // ������� ����� � ����������������� �����
    if (find(graph[v1].begin(), graph[v1].end(), v2) == graph[v1].end()){
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
}

// ��� ����������������� ����.
// 1. ������� ���������� ������, ������� � ������.
// 2. �������� � ���� �����, ����������� ������� A � B.

void task_1_2(int task){
    ifstream in("graph12.txt");
    map<int, vector<int>> graph = create_graph(parce_int(in), 0);
    if (task == 1){
        cout << "������� �������: ";
        int vertice; cin >> vertice;
        cout << "���������� ������� ������: " << graph[vertice].size();
    }
    else{
        cout << "������� �������, ����� �������� ����� �������� �����: ";
        int v1, v2; cin >> v1 >> v2;
        insert_edge(graph, v1, v2);
    }
    cout << "\n����:\n";
    print_graph(graph);
}

template <typename T>
map<T, int> in_vertices(map<T, vector<T>> graph){ // ���������� ��������� ������ (� ��������������� �����)
    map<T, int> result;
    for (auto it = graph.begin(); it != graph.end(); ++it){
        for (int i = 0; i < it->second.size(); ++i){
            result[it->second[i]]++;
        }
    }
    return result;
}

// ��� ��������������� ����.
// 1. ���������� ����������� ������ ������ �������.
// 2. ������� ��� �������, ������������ �� ������.

void task_3_4(int task){
    ifstream in("graph34.txt");
    map<int, vector<int>> graph = create_graph(parce_int(in), 1);
    if (task == 3){
        cout << "����������� ������ ������:\n";
        for (auto it = graph.begin(); it != graph.end(); ++it){
            cout << it->first << ": " << it->second.size() << ";\n";
        }
        map<int, int> in_v = in_vertices(graph);
        cout << "����������� ������ ������:\n";
        for (auto it = in_v.begin(); it != in_v.end(); ++it){
            cout << it->first << ": " << it->second << ";\n";
        }
    }
    else{
        cout << "������� �������: ";
        int start; cin >> start;
        map<int, bool> accessable_vertices = bfs(graph, start); // � ������� ������ � ������ �������� ������ ���������� ������
        cout << "������������ �������: ";
        int count = 0;
        for (auto it = accessable_vertices.begin(); it != accessable_vertices.end(); ++it){ // ������� ������������
            if (!it->second){
                cout << it->first << " ";
                count++;
            }
        }
        if (!count) cout << "�� ���";
    }
    cout << "\n����:\n";
    print_graph(graph);
}

template <typename T>
map<T, vector<T>> invert_graph(map<T, vector<T>> G){ // ����������� ��������������� ����
    map<T, vector<T>> H;
    for (auto it = G.begin(); it != G.end(); ++it){
        for (int i = 0; i < it->second.size(); ++i){
            H[it->second[i]].push_back(it->first);
        }
    }
    return H;
}

// 5. ��� ��������������� ����. ����� ��� ������ ������� ���������� �����.
// (������������ �������� ��������)

void task_5(){
    ifstream in("graph5.txt");
    map<int, vector<int>> G = create_graph(parce_int(in), 1); // �������� ����
    map<int, vector<int>> H = invert_graph(G); // ���������������
    vector<int> vertices; // ������ ������ � ��� �������, � ������� �� �������� �� ��� ��� ������ ���������������� ����� � �������
    map<int, bool> used; // ������ ���������� ������
    for (auto it = H.begin(); it != H.end(); ++it){
        used[it->first] = 0;
    }
    for (auto it = H.begin(); it != H.end(); ++it){ // ����� � ������� ���������������� �����
        if (!used[it->first]) dfs1(H, vertices, used, it->first);
    }
    vector<vector<int>> components; // ������ ���������
    for (auto it = H.begin(); it != H.end(); ++it){
        used[it->first] = 0;
    }
    for (int i = vertices.size() - 1; i > -1; --i){ // ����� � ������� ��������� ����� � �������, �������� ������� ������ � vertices
        if (!used[vertices[i]]){
            vector<int> component = dfs2(used, G, vertices[i]);
            if (component.size() > 1) components.push_back(component);
        }
    }
    for (int i = 0; i < components.size(); ++i, cout << endl){
        for (int j = 0; j < components[i].size(); ++j) cout << components[i][j] << " ";
    }
}

int main(){
    SetConsoleCP(1251); // ��������� ��������� win-cp 1251 � ����� �����
    SetConsoleOutputCP(1251); // ��������� ��������� win-cp 1251 � ����� ������
    int task; cout << "�������: "; cin >> task;
    while (task != -1){
        switch(task){
            case 1: task_1_2(task); break;
            case 2: task_1_2(task); break;
            case 3: task_3_4(task); break;
            case 4: task_3_4(task); break;
            case 5: task_5(); break;
        }
        cout << "��������� �������: (����� ��������, ������� -1) ";
        cin >> task;
    }
    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <Windows.h>
using namespace std;

// ��������� ������ ����

vector<pair<int, int>> parse_int(ifstream &in){ // ���� ������� - �����
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

vector<pair<char, char>> parse_char(ifstream &in){ // ���� ������� - �������
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

vector<pair<string, string>> parse_string(ifstream &in){ // ���� ������� - ������
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
void insert_edge(map<T, vector<T>> &graph, T v1, T v2){ // ������� ����� � ����������������� �����
    if (find(graph[v1].begin(), graph[v1].end(), v2) == graph[v1].end()){
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
}

template <typename T>
void erase_edge(map<T, vector<T>> &graph, T v1, T v2){ // �������� ����� � ����������������� �����
    graph[v1].erase(find(graph[v1].begin(), graph[v1].end(), v2));
    graph[v2].erase(find(graph[v2].begin(), graph[v2].end(), v1));
}

template <typename T>
void find_Eulerian_path(map<T, vector<T>> graph){ // ���������� �������� ���� / �����
    bool flag1 = false, flag2 = false;
    T v1, v2;
    for (auto it = graph.begin(); it != graph.end(); ++it){ // ���������, ���� �� ������� � �������� ��������
        if (it->second.size() % 2){
            if (!flag1){
                v1 = it->first;
                flag1 = true;
            }
            else if (!flag2){
                v2 = it->first;
                flag2 = true;
            }
            else{ // ���� ����� ������ ������ ����, �� �������� ���� �� ����������
                cout << "������� ���� �� ����������";
                return;
            }
        }
    }
    if (flag1) insert_edge(graph, v1, v2); // ���� ���� ��� ������� �������� �������, ��������� ����� ���� �����
    stack<T> s;
    s.push(v1);
    vector<T> path; // ������� ����
    while (s.size()){ // ���� ���� ��������
        T cur = s.top();
        if (graph[cur].size()){ // ���� ������� ������� ������� �� �������
            s.push(graph[cur][0]); // ��������� � � ����
            erase_edge(graph, cur, graph[cur][0]); // ������� ����� ����� ���������
        }
        else{ // ����� ��������� ������� � ����
            path.push_back(cur);
            s.pop(); // � ������� �� �����
        }
    }
    if (flag1){ // ���� ���� ������� � �������� ��������
        vector<T> result;
        for (int i = 0; i < path.size(); ++i){ // "�������" �� ��������������� ������� �������������� �����
            if (path[i] == v1 && path[i + 1] == v2 || path[i] == v2 && path[i] == v1){
                copy(path.begin() + i + 1, path.end(), back_inserter(result));
                copy(path.begin(), path.begin() + i, back_inserter(result));
                break;
            }
        }
        path = result;
        cout << "������� ���� �� ����������.\n������� ����: ";
    }
    else cout << "������� ����: ";
    for (int i = 0; i < path.size(); ++i){
        cout << path[i];
        if (i != path.size() - 1) cout << "->";
    }
}

// 1. ��� ����������������� ����. ������� ������� ���� ��� ������� ����, ���� �� ����������.
void task1(){
    ifstream in("Eulerian_cycle.txt");
    map<int, vector<int>> graph = create_graph(parse_int(in), 0);
    find_Eulerian_path(graph);
    cout << "\n����:\n";
    print_graph(graph);
}

// ����� ����� � �������. � ������ vertices ������� ���������� � ��� �������, � ������� �� �������� �� ��� ��� ������
template <typename T>
void dfs(map<T, vector<T>> graph, vector<T> &vertices, map<T, bool> &used, T x){
    used[x] = 1; // �������� ������� ��� ����������
    for (int i = 0; i < graph[x].size(); ++i){
        if (!used[graph[x][i]]) dfs(graph, vertices, used, graph[x][i]);
    }
    vertices.push_back(x);
}

template <typename T>
void topological_sort(map<T, vector<T>> graph){ // �������������� ����������
    map<T, bool> used; // ���������� �������
    for (auto it = graph.begin(); it != graph.end(); ++it)
        used[it->first] = 0;
    vector<T> vertices; // ������� � ������� ������
    for (auto it = graph.begin(); it != graph.end(); ++it){ // ����� � �������
        if (!used[it->first]) dfs(graph, vertices, used, it->first);
    }
    reverse(vertices.begin(), vertices.end()); // �������������� ������ � �������� �������
    cout << "����� �������������� ����������: ";
    for (int i = 0; i < vertices.size(); ++i) cout << vertices[i] << " ";
}

// �������� �� ������� ������
template <typename T>
void find_cycles(map<T, vector<T>> graph, map<T, bool> &used, map<T, T> &pr, T x, bool flag, bool &ans){
    used[x] = 1; // �������� ������� ��� ����������
    for (int i = 0; i < graph[x].size(); ++i){
        if (ans) break; // ���� ��� ����� ���� � �����, ��������� �����
        if (flag && pr.find(graph[x][i]) != pr.end() && pr[graph[x][i]] == x) continue; // ��� ������������������ �����
        if (!used[graph[x][i]]){ // ���� ��� �� �������� ��� �������
            pr[graph[x][i]] = x; // � - � ������
            find_cycles(graph, used, pr, graph[x][i], flag, ans);
        }
        else{ // ���� ����� ��������� � ��� ���������� �������, ������, ���� ����
            ans = 1;
            break;
        }
    }
    used[x] = 0;
}

// �������� ����� ������� �������������� ����������
template <typename T>
void condition(map<T, vector<T>> graph){
    map<T, bool> used; // ���������� �������
    for (auto it = graph.begin(); it != graph.end(); ++it)
        used[it->first] = 0;
    map<T, T> pr; // ������
    bool ans = 0; // ���� ��� ��� ������
    for (auto it = graph.begin(); it != graph.end(); ++it){ // ����� � �������
        if (!used[it->first]) find_cycles(graph, used, pr, it->first, 0, ans);
    }
    if (ans) cout << "�������������� ���������� ��������� ����������, ���� �������� ����\n";
    else topological_sort(graph);
}

void task2(){
    ifstream in("Topological_sort.txt");
    map<int, vector<int>> graph = create_graph(parse_int(in), 1);
    cout << "���� ����� 1:\n";
    print_graph(graph);
    condition(graph);
    cout << "\n";
    in.close();
    in.open("graph5.txt");
    graph = create_graph(parse_int(in), 1);
    cout << "\n���� ����� 2:\n";
    print_graph(graph);
    condition(graph);
}

int main(){
    SetConsoleCP(1251); // ��������� ��������� win-cp 1251 � ����� �����
    SetConsoleOutputCP(1251); // ��������� ��������� win-cp 1251 � ����� ������
    int task; cout << "�������: "; cin >> task;
    while (task != 0){
        switch(task){
            case 1: task1(); break;
            case 2: task2(); break;
        }
        cout << "��������� �������: (������� 0, ����� ��������) ";
        cin >> task;
    }
    return 0;
}
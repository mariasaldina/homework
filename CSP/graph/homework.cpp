#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <Windows.h>
using namespace std;

// Считываем вектор рёбер

vector<pair<int, int>> parse_int(ifstream &in){ // если вершины - числа
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

vector<pair<char, char>> parse_char(ifstream &in){ // если вершины - символы
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

vector<pair<string, string>> parse_string(ifstream &in){ // если вершины - строки
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
map<T, vector<T>> create_graph(vector<pair<T, T>> pairs, bool flag){ // создание графа из списка рёбер
    map<T, vector<T>> graph;
    T x, y;
    for (int i = 0; i < pairs.size(); ++i){
        x = pairs[i].first;
        y = pairs[i].second;
        graph[x].push_back(y);
        if (!flag) graph[y].push_back(x); // если граф неориентированный
        else{
            if (graph.find(y) == graph.end()) graph[y] = {}; // если ориентированный
        }
    }
    for (auto it = graph.begin(); it != graph.end(); ++it){
        sort(it->second.begin(), it->second.end()); // сортируем списки для каждой вершины
        it->second.erase(unique(it->second.begin(), it->second.end()), it->second.end()); // удаляем дубликаты
    }
    return graph;
}

template <typename T>
void print_graph(map<T, vector<T>> graph){ // вывод графа в виде списка смежности
    for (auto it = graph.begin(); it != graph.end(); ++it, cout << endl){
        T vertice = it->first;
        cout << vertice << ": ";
        for (int i = 0; i < graph[vertice].size(); ++i){
            cout << graph[vertice][i] << " ";
        }
    }
}

template <typename T>
void insert_edge(map<T, vector<T>> &graph, T v1, T v2){ // вставка ребра в неориентированном графе
    if (find(graph[v1].begin(), graph[v1].end(), v2) == graph[v1].end()){
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
}

template <typename T>
void erase_edge(map<T, vector<T>> &graph, T v1, T v2){ // удаление ребра в неориентированном графе
    graph[v1].erase(find(graph[v1].begin(), graph[v1].end(), v2));
    graph[v2].erase(find(graph[v2].begin(), graph[v2].end(), v1));
}

template <typename T>
void find_Eulerian_path(map<T, vector<T>> graph){ // нахождение Эйлерова пути / цикла
    bool flag1 = false, flag2 = false;
    T v1, v2;
    for (auto it = graph.begin(); it != graph.end(); ++it){ // проверяем, есть ли вершины с нечётной степенью
        if (it->second.size() % 2){
            if (!flag1){
                v1 = it->first;
                flag1 = true;
            }
            else if (!flag2){
                v2 = it->first;
                flag2 = true;
            }
            else{ // если таких вершин больше двух, то Эйлерова пути не существует
                cout << "Эйлеров путь не существует";
                return;
            }
        }
    }
    if (flag1) insert_edge(graph, v1, v2); // если есть две вершины нечётной степени, вставляем между ними ребро
    stack<T> s;
    s.push(v1);
    vector<T> path; // Эйлеров путь
    while (s.size()){ // пока стек непустой
        T cur = s.top();
        if (graph[cur].size()){ // если степень текущей вершины не нулевая
            s.push(graph[cur][0]); // добавляем её в стек
            erase_edge(graph, cur, graph[cur][0]); // удаляем ребро между вершинами
        }
        else{ // иначе добавляем вершину в путь
            path.push_back(cur);
            s.pop(); // и удаляем из стека
        }
    }
    if (flag1){ // если есть вершины с нечётной степенью
        vector<T> result;
        for (int i = 0; i < path.size(); ++i){ // "удаляем" из результирующего вектора несуществующее ребро
            if (path[i] == v1 && path[i + 1] == v2 || path[i] == v2 && path[i] == v1){
                copy(path.begin() + i + 1, path.end(), back_inserter(result));
                copy(path.begin(), path.begin() + i, back_inserter(result));
                break;
            }
        }
        path = result;
        cout << "Эйлеров цикл не существует.\nЭйлеров путь: ";
    }
    else cout << "Эйлеров цикл: ";
    for (int i = 0; i < path.size(); ++i){
        cout << path[i];
        if (i != path.size() - 1) cout << "->";
    }
}

// 1. Дан неориентированный граф. Вывести Эйлеров путь или Эйлеров цикл, если он существует.
void task1(){
    ifstream in("Eulerian_cycle.txt");
    map<int, vector<int>> graph = create_graph(parse_int(in), 0);
    find_Eulerian_path(graph);
    cout << "\nГраф:\n";
    print_graph(graph);
}

// Обход графа в глубину. В списке vertices вершины содержатся в том порядке, в котором мы выходили из них при обходе
template <typename T>
void dfs(map<T, vector<T>> graph, vector<T> &vertices, map<T, bool> &used, T x){
    used[x] = 1; // помечаем вершину как посещённую
    for (int i = 0; i < graph[x].size(); ++i){
        if (!used[graph[x][i]]) dfs(graph, vertices, used, graph[x][i]);
    }
    vertices.push_back(x);
}

template <typename T>
void topological_sort(map<T, vector<T>> graph){ // топологическая сортировка
    map<T, bool> used; // посещённые вершины
    for (auto it = graph.begin(); it != graph.end(); ++it)
        used[it->first] = 0;
    vector<T> vertices; // вершины в порядке выхода
    for (auto it = graph.begin(); it != graph.end(); ++it){ // обход в глубину
        if (!used[it->first]) dfs(graph, vertices, used, it->first);
    }
    reverse(vertices.begin(), vertices.end()); // перезаписываем вектор в обратном порядке
    cout << "После топологической сортировки: ";
    for (int i = 0; i < vertices.size(); ++i) cout << vertices[i] << " ";
}

// Проверка на наличие циклов
template <typename T>
void find_cycles(map<T, vector<T>> graph, map<T, bool> &used, map<T, T> &pr, T x, bool flag, bool &ans){
    used[x] = 1; // отмечаем вершину как посещённую
    for (int i = 0; i < graph[x].size(); ++i){
        if (ans) break; // если уже нашли цикл в графе, прерываем обход
        if (flag && pr.find(graph[x][i]) != pr.end() && pr[graph[x][i]] == x) continue; // для неориентированного графа
        if (!used[graph[x][i]]){ // если ещё не посетили эту вершину
            pr[graph[x][i]] = x; // х - её предок
            find_cycles(graph, used, pr, graph[x][i], flag, ans);
        }
        else{ // если можем вернуться в уже посещённую вершину, значит, есть цикл
            ans = 1;
            break;
        }
    }
    used[x] = 0;
}

// Проверка перед вызовом топологической сортировки
template <typename T>
void condition(map<T, vector<T>> graph){
    map<T, bool> used; // посещённые вершины
    for (auto it = graph.begin(); it != graph.end(); ++it)
        used[it->first] = 0;
    map<T, T> pr; // предки
    bool ans = 0; // есть или нет циклов
    for (auto it = graph.begin(); it != graph.end(); ++it){ // обход в глубину
        if (!used[it->first]) find_cycles(graph, used, pr, it->first, 0, ans);
    }
    if (ans) cout << "Топологическую сортировку выполнить невозможно, граф содержит цикл\n";
    else topological_sort(graph);
}

void task2(){
    ifstream in("Topological_sort.txt");
    map<int, vector<int>> graph = create_graph(parse_int(in), 1);
    cout << "Граф номер 1:\n";
    print_graph(graph);
    condition(graph);
    cout << "\n";
    in.close();
    in.open("graph5.txt");
    graph = create_graph(parse_int(in), 1);
    cout << "\nГраф номер 2:\n";
    print_graph(graph);
    condition(graph);
}

int main(){
    SetConsoleCP(1251); // установка кодировки win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодировки win-cp 1251 в поток вывода
    int task; cout << "Задание: "; cin >> task;
    while (task != 0){
        switch(task){
            case 1: task1(); break;
            case 2: task2(); break;
        }
        cout << "Следующее задание: (введите 0, чтобы прервать) ";
        cin >> task;
    }
    return 0;
}
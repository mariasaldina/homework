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
map<T, bool> bfs(map<T, vector<T>> gr, T x){ // обход графа в ширину
    map<T, bool> used;
    for (auto it = gr.begin(); it != gr.end(); ++it){
        used[it->first] = 0;
    }
    used[x] = 1; // помечаем первую вершину как посещённую
    queue<T> h; // создаём очередь
    h.push(x); // помещаем вершину в очередь
    while (h.size()){ // пока очередь не пуста
        x = h.front(); // сохраняем значение головы
        h.pop(); // удаляем голову из очереди
        for (int i = 0; i < gr[x].size(); ++i){ // проходимся по списку смежных с текущей вершин
            if (!used[gr[x][i]]){ // если эту вершину ещё не посетили
                T y = gr[x][i];
                used[y] = 1; // помечаем её как посещённую
                h.push(y); // и добавляем в очередь
            }
        }
    }
    return used;
}

// Обход графа в глубину. В списке vertices вершины содержатся в том порядке, в котором мы выходили из них при обходе
template <typename T>
void dfs1(map<T, vector<T>> gr, vector<T> &vertices, map<T, bool> &used, T x){
    stack<T> h; // создаём стек
    h.push(x); // добавляем в него первую вершину
    used[x] = 1; // помечаем её как посещённую
    bool flag = 0; T y;
    while (h.size()){ // пока стек не пуст
        x = h.top(); // рассматриваем голову стека
        for (int i = 0; i < gr[x].size(); ++i){ 
            if (!used[gr[x][i]]){ // ищем первую непосещённую вершину среди смежных
                y = gr[x][i];
                flag = 1;
                break;
            }
        }
        if (flag){ // если нашли непосещённую вершину
            h.push(y); // добавляем её в стек (чтобы затем вернуться и начать с неё)
            used[y] = 1; // помечаем её как посещённую
        }
        else{
            vertices.push_back(h.top()); // выходим из вершины
            h.pop(); // и удаляем голову стека
        }
        flag = 0;
    }
}

// Обход графа в глубину. Возвращает список вершин компоненты
template <typename T>
vector<T> dfs2(map<T, bool> &used, map<T, vector<T>> gr, T x){
    stack<T> h; // создаём стек
    h.push(x); // добавляем в него первую вершину
    used[x] = 1; // помечаем её как посещённую
    bool flag = 0; T y;
    vector<T> component; // список вершин компоненты
    component.push_back(x);
    while (h.size()){ // пока стек не пуст
        x = h.top(); // рассматриваем голову стека
        for (int i = 0; i < gr[x].size(); ++i){ 
            if (!used[gr[x][i]]){ // ищем первую непосещённую вершину среди смежных
                y = gr[x][i];
                flag = 1;
                break;
            }
        }
        if (flag){ // если нашли непосещённую вершину
            h.push(y); // добавляем её в стек (чтобы затем вернуться и начать с неё)
            used[y] = 1; // помечаем её как посещённую
            component.push_back(y);
        }
        else h.pop(); // иначе удаляем голову стека
        flag = 0;
    }
    return component;
}

// Получаем вектор рёбер

vector<pair<int, int>> parce_int(ifstream &in){ // если вершины - числа
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

vector<pair<char, char>> parce_char(ifstream &in){ // если вершины - символы
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

vector<pair<string, string>> parce_string(ifstream &in){ // если вершины - строки
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
void insert_edge(map<T, vector<T>> &graph, T v1, T v2){ // вставка ребра в неориентированном графе
    if (find(graph[v1].begin(), graph[v1].end(), v2) == graph[v1].end()){
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
}

// Дан неориентированный граф.
// 1. Вывести количество вершин, смежных с данной.
// 2. Вставить в граф ребро, соединяющее вершины A и B.

void task_1_2(int task){
    ifstream in("graph12.txt");
    map<int, vector<int>> graph = create_graph(parce_int(in), 0);
    if (task == 1){
        cout << "Введите вершину: ";
        int vertice; cin >> vertice;
        cout << "Количество смежных вершин: " << graph[vertice].size();
    }
    else{
        cout << "Введите вершины, между которыми нужно вставить ребро: ";
        int v1, v2; cin >> v1 >> v2;
        insert_edge(graph, v1, v2);
    }
    cout << "\nГраф:\n";
    print_graph(graph);
}

template <typename T>
map<T, int> in_vertices(map<T, vector<T>> graph){ // количество заходящих вершин (в ориентированном графе)
    map<T, int> result;
    for (auto it = graph.begin(); it != graph.end(); ++it){
        for (int i = 0; i < it->second.size(); ++i){
            result[it->second[i]]++;
        }
    }
    return result;
}

// Дан ориентированный граф.
// 1. Подсчитать полустепень исхода каждой вершины.
// 2. Вывести все вершины, недостижимые из данной.

void task_3_4(int task){
    ifstream in("graph34.txt");
    map<int, vector<int>> graph = create_graph(parce_int(in), 1);
    if (task == 3){
        cout << "Полустепень исхода вершин:\n";
        for (auto it = graph.begin(); it != graph.end(); ++it){
            cout << it->first << ": " << it->second.size() << ";\n";
        }
        map<int, int> in_v = in_vertices(graph);
        cout << "Полустепень захода вершин:\n";
        for (auto it = in_v.begin(); it != in_v.end(); ++it){
            cout << it->first << ": " << it->second << ";\n";
        }
    }
    else{
        cout << "Введите вершину: ";
        int start; cin >> start;
        map<int, bool> accessable_vertices = bfs(graph, start); // с помощью обхода в ширину получаем список посещённых вершин
        cout << "Недостижимые вершины: ";
        int count = 0;
        for (auto it = accessable_vertices.begin(); it != accessable_vertices.end(); ++it){ // выводим непосещённые
            if (!it->second){
                cout << it->first << " ";
                count++;
            }
        }
        if (!count) cout << "их нет";
    }
    cout << "\nГраф:\n";
    print_graph(graph);
}

template <typename T>
map<T, vector<T>> invert_graph(map<T, vector<T>> G){ // инвертируем ориентированный граф
    map<T, vector<T>> H;
    for (auto it = G.begin(); it != G.end(); ++it){
        for (int i = 0; i < it->second.size(); ++i){
            H[it->second[i]].push_back(it->first);
        }
    }
    return H;
}

// 5. Дан ориентированный граф. Найти все сильно связные компоненты графа.
// (используется алгоритм Косарайю)

void task_5(){
    ifstream in("graph5.txt");
    map<int, vector<int>> G = create_graph(parce_int(in), 1); // исходный граф
    map<int, vector<int>> H = invert_graph(G); // инвертированный
    vector<int> vertices; // список вершин в том порядке, в котором мы выходили из них при обходе инвертированного графа в глубину
    map<int, bool> used; // список посещённых вершин
    for (auto it = H.begin(); it != H.end(); ++it){
        used[it->first] = 0;
    }
    for (auto it = H.begin(); it != H.end(); ++it){ // обход в глубину инвертированного графа
        if (!used[it->first]) dfs1(H, vertices, used, it->first);
    }
    vector<vector<int>> components; // список компонент
    for (auto it = H.begin(); it != H.end(); ++it){
        used[it->first] = 0;
    }
    for (int i = vertices.size() - 1; i > -1; --i){ // обход в глубину исходного графа в порядке, обратном порядку вершин в vertices
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
    SetConsoleCP(1251); // установка кодировки win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодировки win-cp 1251 в поток вывода
    int task; cout << "Задание: "; cin >> task;
    while (task != -1){
        switch(task){
            case 1: task_1_2(task); break;
            case 2: task_1_2(task); break;
            case 3: task_3_4(task); break;
            case 4: task_3_4(task); break;
            case 5: task_5(); break;
        }
        cout << "Следующее задание: (чтобы прервать, введите -1) ";
        cin >> task;
    }
    return 0;
}
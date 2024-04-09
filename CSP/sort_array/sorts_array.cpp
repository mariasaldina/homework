#include <iostream>
#include <fstream> // файловые потоки
#include <sstream> // строковые потоки
#include <cmath>
#include <vector>
#include <Windows.h>

using namespace std;

ifstream in("in_array.txt"); // входной файл
ofstream out("out_array.txt"); // выходной файл

vector<vector<int>> input(){ // считываем массив
    vector<vector<int>> table;
    string s;
    while (in.peek() != EOF){ // считываем, пока не дойдём до конца файла
        getline(in, s);
        istringstream str(s);
        vector<int> a; int x;
        while (str.peek() != EOF){ // считываем по одному числу из строкового потока
            str >> x;
            a.push_back(x);
        }
        table.push_back(a); // добавляем строку в массив
    }
    in.close();
    return table;
}

void print(vector<vector<int>> a, int n, int m){ // выводим массив
    for (int i = 0; i < n; ++i, out << endl)
        for(int j = 0; j < m; ++j)
            out << a[i][j] << " ";
    out << endl;
}

void heapfy(vector<vector<int>> &a, int i, int n, int k){ // строим пирамиду
    int max = i;
    while (true){
        int ch = 2 * i + 1; // индекс ребёнка
        if (ch < n && a[ch][k] > a[max][k]) max = ch; 
        ++ch;
        if (ch < n && a[ch][k] > a[max][k]) max = ch;
        if (i == max) break; 
        else {
            swap(a[max][k], a[i][k]); // ставим максимальный элемент на место родителя
            i = max; // на следующей итерации смотрим детей ребёнка
        }
    }
}

void heapsort(vector<vector<int>> &a, int n, int m){ // пирамидальная сортировка
    for (int k = 0; k < m; ++k){ // строим пирамиду
        for (int i = n / 2; i >= 0; --i){
            heapfy(a, i, n, k);
        }
        for (int i = n - 1; i > 0; --i){
            swap(a[0][k], a[i][k]); // меняем местами вершину и последний элемент в пирамиде 
            // (последний элемент больше не рассматриваем, он на своём месте)
            heapfy(a, 0, i, k); // снова строим пирамиду
        }
    }
}

// 5. Столбцы по возрастанию с помощью пирамидальной сортировки
void task1(vector<vector<int>> &array){
    heapsort(array, array.size(), array[0].size());
    print(array, array.size(), array[0].size());
}

void shells_sort(vector<vector<int>> &a, int n, int m){ // сортировка Шелла
    for (int k = 0; k < n; ++k){
        int power = log(m) / log(3); // максимальная степень тройки
        int step = pow(3, power) - 1; // шаг
        while (power >= 0){
            for (int i = 0; i < m - step; ++i){ // идём с шагом
                int j = i;
                while (j >= 0 && ((a[k][j] > a[k][j + step]) == (k % 2))){
                    swap(a[k][j], a[k][j + step]);
                    j -= step;
                }
            }
            --power; // уменьшаем степень
            step = pow(3, power) - 1; // пересчитываем шаг
            if (step < 1) step = 1; // в конце проходимся с шагом 1
        }
    }
}

// 7. Чётные строки по возрастанию, нечётные по убыванию с помощью сортировки Шелла с шагом 3^i - 1.
void task2(vector<vector<int>> &array){
    shells_sort(array, array.size(), array[0].size());
    print(array, array.size(), array[0].size());
}

void choice_sort(vector<vector<int>> &a, int n){ // сортировка выбором
    for (int k = 0; k < n; ++k){
        for (int i = 0; i < n - k; ++i){ // диагонали под главной
            int max = 0, max_ind;
            for (int j = i; j < n - k; ++j){ // находим максимум от i-го до (n - 1)-го элемента
                if (a[j][j + k] >= max){
                    max = a[j][j + k];
                    max_ind = j;
                }
            }
            swap(a[i][i + k], a[max_ind][max_ind + k]); // меняем местами максимум и текущий элемент
        }
        for (int i = 0; i < n - k; ++i){ // диагонали над главной
            int max = 0, max_ind;
            for (int j = i; j < n - k; ++j){ // находим максимум от i-го до (n - 1)-го элемента
                if (a[j + k][j] >= max){
                    max = a[j + k][j];
                    max_ind = j;
                }
            }
            swap(a[i + k][i], a[max_ind + k][max_ind]); // меняем местами максимум и текущий элемент
        }
    }
}

// 14. Диагонали, параллельные главной, по убыванию с помощью сортировки выбором.
void task3(vector<vector<int>> &array){
    choice_sort(array, array.size());
    print(array, array.size(), array[0].size());
}

int main(){
    SetConsoleCP(1251); // установка кодировки win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодировки win-cp 1251 в поток вывода
    int task; cout << "Задание: "; cin >> task;
    vector<vector<int>> array = input();
    print(array, array.size(), array[0].size());
    switch(task){
        case 1: task1(array); break;
        case 2: task2(array); break;
        case 3: task3(array); break;
    }
    return 0;
}
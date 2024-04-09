#include <iostream>
#include <fstream> // �������� ������
#include <sstream> // ��������� ������
#include <cmath>
#include <vector>
#include <Windows.h>

using namespace std;

ifstream in("in_array.txt"); // ������� ����
ofstream out("out_array.txt"); // �������� ����

vector<vector<int>> input(){ // ��������� ������
    vector<vector<int>> table;
    string s;
    while (in.peek() != EOF){ // ���������, ���� �� ����� �� ����� �����
        getline(in, s);
        istringstream str(s);
        vector<int> a; int x;
        while (str.peek() != EOF){ // ��������� �� ������ ����� �� ���������� ������
            str >> x;
            a.push_back(x);
        }
        table.push_back(a); // ��������� ������ � ������
    }
    in.close();
    return table;
}

void print(vector<vector<int>> a, int n, int m){ // ������� ������
    for (int i = 0; i < n; ++i, out << endl)
        for(int j = 0; j < m; ++j)
            out << a[i][j] << " ";
    out << endl;
}

void heapfy(vector<vector<int>> &a, int i, int n, int k){ // ������ ��������
    int max = i;
    while (true){
        int ch = 2 * i + 1; // ������ ������
        if (ch < n && a[ch][k] > a[max][k]) max = ch; 
        ++ch;
        if (ch < n && a[ch][k] > a[max][k]) max = ch;
        if (i == max) break; 
        else {
            swap(a[max][k], a[i][k]); // ������ ������������ ������� �� ����� ��������
            i = max; // �� ��������� �������� ������� ����� ������
        }
    }
}

void heapsort(vector<vector<int>> &a, int n, int m){ // ������������� ����������
    for (int k = 0; k < m; ++k){ // ������ ��������
        for (int i = n / 2; i >= 0; --i){
            heapfy(a, i, n, k);
        }
        for (int i = n - 1; i > 0; --i){
            swap(a[0][k], a[i][k]); // ������ ������� ������� � ��������� ������� � �������� 
            // (��������� ������� ������ �� �������������, �� �� ���� �����)
            heapfy(a, 0, i, k); // ����� ������ ��������
        }
    }
}

// 5. ������� �� ����������� � ������� ������������� ����������
void task1(vector<vector<int>> &array){
    heapsort(array, array.size(), array[0].size());
    print(array, array.size(), array[0].size());
}

void shells_sort(vector<vector<int>> &a, int n, int m){ // ���������� �����
    for (int k = 0; k < n; ++k){
        int power = log(m) / log(3); // ������������ ������� ������
        int step = pow(3, power) - 1; // ���
        while (power >= 0){
            for (int i = 0; i < m - step; ++i){ // ��� � �����
                int j = i;
                while (j >= 0 && ((a[k][j] > a[k][j + step]) == (k % 2))){
                    swap(a[k][j], a[k][j + step]);
                    j -= step;
                }
            }
            --power; // ��������� �������
            step = pow(3, power) - 1; // ������������� ���
            if (step < 1) step = 1; // � ����� ���������� � ����� 1
        }
    }
}

// 7. ׸���� ������ �� �����������, �������� �� �������� � ������� ���������� ����� � ����� 3^i - 1.
void task2(vector<vector<int>> &array){
    shells_sort(array, array.size(), array[0].size());
    print(array, array.size(), array[0].size());
}

void choice_sort(vector<vector<int>> &a, int n){ // ���������� �������
    for (int k = 0; k < n; ++k){
        for (int i = 0; i < n - k; ++i){ // ��������� ��� �������
            int max = 0, max_ind;
            for (int j = i; j < n - k; ++j){ // ������� �������� �� i-�� �� (n - 1)-�� ��������
                if (a[j][j + k] >= max){
                    max = a[j][j + k];
                    max_ind = j;
                }
            }
            swap(a[i][i + k], a[max_ind][max_ind + k]); // ������ ������� �������� � ������� �������
        }
        for (int i = 0; i < n - k; ++i){ // ��������� ��� �������
            int max = 0, max_ind;
            for (int j = i; j < n - k; ++j){ // ������� �������� �� i-�� �� (n - 1)-�� ��������
                if (a[j + k][j] >= max){
                    max = a[j + k][j];
                    max_ind = j;
                }
            }
            swap(a[i + k][i], a[max_ind + k][max_ind]); // ������ ������� �������� � ������� �������
        }
    }
}

// 14. ���������, ������������ �������, �� �������� � ������� ���������� �������.
void task3(vector<vector<int>> &array){
    choice_sort(array, array.size());
    print(array, array.size(), array[0].size());
}

int main(){
    SetConsoleCP(1251); // ��������� ��������� win-cp 1251 � ����� �����
    SetConsoleOutputCP(1251); // ��������� ��������� win-cp 1251 � ����� ������
    int task; cout << "�������: "; cin >> task;
    vector<vector<int>> array = input();
    print(array, array.size(), array[0].size());
    switch(task){
        case 1: task1(array); break;
        case 2: task2(array); break;
        case 3: task3(array); break;
    }
    return 0;
}
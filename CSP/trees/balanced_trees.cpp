#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

template<typename T>
struct tree{ // �������� ���������������� ������
    T inf;
    tree *left;
    tree *right;
};

template<typename T>
tree<T> *node(T x){ // ������ ����� ����
    tree<T> *r = new tree<T>;
    r->inf = x;
    r->left = r->right = nullptr;
    return r;
}

template<typename T>
void create_tree(tree<T> *&tr, int n){ // ������ ������
    T x;
    if (n > 0){
        cin >> x;
        tr = node(x);
        int nl = n / 2;
        int nr = n - nl - 1;
        create_tree(tr->left, nl); // ���������� ��������� ����� �����
        create_tree(tr->right, nr); // ���������� ��������� ������ �����
    }
}

template<typename T>
void print_leaves(tree<T> *tr){ // ����� �������
    if (tr){
        if (!tr->left && !tr->right) cout << tr->inf << " ";
        print_leaves(tr->left);
        print_leaves(tr->right);
    }
}

template<typename T>
void print_tree(tree<T> *tr, int k){ // ����� ����� ������
    queue<tree<T>*> cur, next; // ������� �������� ������ (��������) � ���������� (����)
    tree<T> *r = tr;
    cur.push(r);
    int j = 0;
    while (cur.size()){
        if (j == 0){
            for (int i = 0; i < (int)pow(2.0, k) - 1; ++i)
                cout << " ";
        }
        tree<T> *buf = cur.front();
        cur.pop(); ++j;
        if (buf){ // ������� ������ ������� � ����� � ����� � ������� ���������� ������
            cout << buf->inf;
            next.push(buf->left);
            next.push(buf->right);
            for (int i = 0; i < (int)pow(2.0, k + 1) - 1; ++i)
                cout << " ";
        }
        if (!buf){
            for (int i = 0; i < (int)pow(2.0, k + 1); ++i)
                cout << " ";
        }
        if (cur.empty()){
            cout << endl;
            swap(cur, next); // ��������� � ���������� ������
            j = 0; --k;
        }
    }
}

// 10 4 5 3 7 8 6 9 1 2 0
// 1. ���� ������. ������� ��� ������
void task1(){
    int n; cout << "Enter the number of nodes: "; cin >> n;
    tree<int> *tr = nullptr;
    cout << "Enter the values: ";
    create_tree(tr, n);
    cout << "Leaves: ";
    print_leaves(tr);
    int k = (int)(log((float)n) / log(2.0));
    cout << "\nThe tree is: \n";
    print_tree(tr, k);
}

template<typename T>
void print_level(tree<T> *tr, int k, int level){ // ����� �������
    queue<tree<T>*> cur, next; // ������� �������� ������ (��������) � ���������� (����)
    tree<T> *r = tr;
    cur.push(r);
    while (cur.size() && k != level){
        if (cur.front()){ // ����� ����� �������� ���� � ������� ���������� ������
            next.push(cur.front()->left);
            next.push(cur.front()->right);
        }
        cur.pop();
        if (cur.empty()){
            swap(cur, next); // ��������� � ���������� ������
            k--;
        }
    }
    while (cur.size()){ // ������� �������
        if (cur.front()) cout << cur.front()->inf << " ";
        cur.pop();
    }
}

// 2. ���� ������. ������� ���� k-�� ������
void task2(){
    int n, level; cout << "Enter the number of nodes: "; cin >> n;
    tree<int> *tr = nullptr;
    cout << "Enter the values: ";
    create_tree(tr, n);
    cout << "Enter the level to print: "; cin >> level;
    int k = (int)(log((float)n) / log(2.0));
    cout << "The level: ";
    print_level(tr, k, k - level + 1);
    cout << "\nThe tree is: \n";
    print_tree(tr, k);
}

int main(){
    int task; cout << "Choose the task: "; cin >> task;
    switch (task){
        case 1: task1(); break;
        case 2: task2(); break;
    }
    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
struct tree{ // ��������� ������
    T inf;
    tree *left;
    tree *right;
    tree *parent;
};

template<typename T>
tree<T> *node(T x){ // ������ ����� ����
    tree<T> *r = new tree<T>;
    r->inf = x;
    r->left = r->right = nullptr;
    r->parent = nullptr;
    return r;
}

template<typename T>
void insert(tree<T> *&tr, T x){ // ��������� ����� ����
    tree<T> *r = node(x);
    if (!tr) tr = r; // ���� � ������ ��� ��� ���������
    else{
        tree<T> *y = tr;
        while (y){ // ���� ����� ��� ������ ��������
            if (r->inf > y->inf){ // ���� ����� ������� ������ ��������
                if (y->right){ // � ������ ��� ������
                    y = y->right; // ���� ������ � ������ ���������
                }
                else{ // ����� ��������� ������� ������
                    y->right = r;
                    r->parent = y;
                    break;
                }
            }
            else if (r->inf < y->inf){ // ���� ����� ������� ������ ��������
                if (y->left){ // � ����� ��� ������
                    y = y->left; // ���� ������ � ����� ���������
                }
                else{ // ����� ��������� ������� �����
                    y->left = r;
                    r->parent = y;
                    break;
                }
            }
            else break; // ���� ��������� ������ ������ �������, ��������� ����
        }
    }
}

template<typename T>
tree<T> *find(tree<T> *&tr, T x, vector<tree<T>*> &path){ // ����� ���� �� ����� �� �������� �� ��������
    if (!tr || tr->inf == x)
        return tr; // ���� ����� ������� ��� ����� �� ����� ������
    else{
        if (tr->inf > x){
            if (tr->left) path.push_back(tr->left); // ���� ������� �������� ������ ��������, ���� � ����� ���������
            return find(tr->left, x, path);
        }
        else{
            if (tr->right) path.push_back(tr->right); // ����� ���� � ������ ���������
            return find(tr->right, x, path);
        }
    }
}

template<typename T>
tree<T> *Min(tree<T> *&tr){ // ����� ������������� �������� 
    if (!tr->left) return tr;
    else return Min(tr->left);
}

template<typename T>
tree<T> *Max(tree<T> *&tr){ // ����� ������������ ��������
    if (!tr->right) return tr;
    else return Max(tr->right);
}

template<typename T>
tree<T> *Next(tree<T> *x){ // ����� ���������� �������� ��� ������������ ������
    if (x == Max(x)) return nullptr; // ���� ������� ��� �������� ������ ������, �� ��������� �� ��� - nullptr
    if (x->right) return Min(x->right); // �����, ���� ���� ������ �����, ������� ������� ����� ������� � ������ ���������
    tree<T> *y = x->parent; // ����� ������������ �����
    while (x && x == y->right){ // ���� �� ����� �� nullptr ��� ���� ������� ���� �� ���� ����� ������� ������ �������� (�.�. ����� �� ����� ���������)
        x = y;
        y = x->parent;
    }
    return y;
}

template<typename T>
tree<T> *Prev(tree<T> *x){ // ����� ����������� �������� ��� ������������ ������
    if (x == Min(x)) return nullptr; // ���� ������� ��� �������� ������ �����, �� ���������� - nullptr
    if (x->left) return Max(x->left); // �����, ���� ���� ����� �����, ������� ������� ������ ������� � ���� ���������
    tree<T> *y = x->parent; // ����� ������������ �����
    while (x && x == y->left){ // ���� �� ����� �� nullptr ��� ���� ������� ���� �� ���� ������ ������� ������ �������� (�.�. ����� �� ����� ���������)
        x = y;
        y = x->parent;
    }
    return y;
}

template<typename T>
void erase(tree<T> *&tr, tree<T> *v){ // �������� ����
    tree<T> *p = v->parent; // �������� ���������� ����
    if (!p && !v->left && !v->right){ // ������������ ������� ������
        tr = nullptr;
        delete v;
    }
    else if (!v->left && !v->right){ // ���� 
        if (v == p->left) // ���� �� �������� ����� ������� ��������
            p->left = nullptr;
        else // ���� �� �������� ������ ������� ��������
            p->right =  nullptr;
        delete v;
    }
    else if (!v->left || !v->right){ // ���� ���� ������ 1 ������
        if (!p) { // ���� ������� ������
            if (v->left){
                tr = v->left;
                tr->parent = nullptr;
            }
            else {
                tr = v->right;
                tr->parent = nullptr;
            }
            delete v;
        }
        else{ // ���� ������� �� ������
            if (v->left){ // ���� ���� ����� ������
                if (v == p->left) // ���� ��������� ������� ��� �������� - ����� ������
                    p->left = v->left;
                else
                    p->right = v->left;
                v->left->parent = p;
            }
            else{ // ����������, ���� ���� ������ ������
                if (v == p->left)
                    p->left = v->right;
                else
                    p->right = v->right;
                v->right->parent = p; 
            }
        }
    }
    else{ // ���� ���� ��� ������
        tree<T> *succ = Min(v->right); // ���� ������ ����� ������� � ������ ���������
        v->inf = succ->inf; // ����������� ��� �������� ����
        if (succ->parent->left == succ){ // �� ����� ������ ������ �������� ����� ��� ������ ������
            succ->parent->left = succ->right;
            if (succ->right)
                succ->right->parent = succ->parent;
        }
        else{
            succ->parent->right = succ->right;
            if (succ->right)
                succ->right->parent = succ->parent;
        }
        delete succ;
    }
}

template<typename T>
void create_tree(tree<T> *&tr, int &n){ // ������ ������
    T x;
    cout << "Enter the number of nodes: "; cin >> n;
    cout << "Enter the values: ";
    for (int i = 0; i < n; ++i){
        cin >> x;
        insert(tr, x);
    }
}

template<typename T>
void inorder(tree<T> *&tr){ // ����� �� ����� ������ � ������� �����������
    if (tr){
        inorder(tr->left);
        cout << tr->inf << " ";
        inorder(tr->right);
    }
}

template<typename T>
void postorder_delete(tree<T> *&tr, tree<T> *&v){ // �������� ����� ������ � �������� �������� ���������
    if (v){
        postorder_delete(tr, v->left);
        postorder_delete(tr, v->right);
        if (v->inf % 2) erase(tr, v);
    }
}

// 1. ���� ������. ������� �������� ��������
// 10 7 2 9 1 5 3 6 4 8 10
void task1(){
    int n;
    tree<int> *tr = nullptr;
    create_tree(tr, n);
    postorder_delete(tr, tr);
    inorder(tr);
    //print_tree(tr);
}

// 2. ���� ������. ������� ���� �� ���� A �� ���� B
// E B G A D C I H F J
void task2(){
    int n;
    tree<char> *tr = nullptr;
    create_tree(tr, n);
    char A, B;
    cout << "Enter the start and the finish: "; cin >> A >> B;
    vector<tree<char>*> path;
    tree<char>* A_node = find(tr, A, path); // ���� ���� �� ��������� �������
    path.clear();
    path.push_back(A_node);
    find(A_node, B, path); // ���� ����
    if (!path.back() || path.back()->inf != B) cout << "There's no such path\n";
    else{
        for (int i = 0; i < path.size(); ++i)
            cout << path[i]->inf << " ";
    }
}

int main(){
    int task; cout << "Choose the task: "; cin >> task;
    switch (task){
        case 1: task1(); break;
        case 2: task2(); break;
    }
    return 0;
}
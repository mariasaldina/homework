#include <iostream>
#include <vector>
using namespace std;

template<typename T>
struct tree{ // структура дерево
    T inf;
    tree *left;
    tree *right;
    tree *parent;
};

template<typename T>
tree<T> *node(T x){ // создаём новый узел
    tree<T> *r = new tree<T>;
    r->inf = x;
    r->left = r->right = nullptr;
    r->parent = nullptr;
    return r;
}

template<typename T>
void insert(tree<T> *&tr, T x){ // вставляем новый узел
    tree<T> *r = node(x);
    if (!tr) tr = r; // если в дереве ещё нет элементов
    else{
        tree<T> *y = tr;
        while (y){ // ищём место для нового элемента
            if (r->inf > y->inf){ // если новый элемент больше текущего
                if (y->right){ // и справа уже занято
                    y = y->right; // ищем дальше в правом поддереве
                }
                else{ // иначе вставляем элемент справа
                    y->right = r;
                    r->parent = y;
                    break;
                }
            }
            else if (r->inf < y->inf){ // если новый элемент меньше текущего
                if (y->left){ // и слева уже занято
                    y = y->left; // ищем дальше в левом поддереве
                }
                else{ // иначе вставляем элемент слева
                    y->left = r;
                    r->parent = y;
                    break;
                }
            }
            else break; // если встретили равный новому элемент, прерываем цикл
        }
    }
}

template<typename T>
tree<T> *find(tree<T> *&tr, T x, vector<tree<T>*> &path){ // поиск пути от корня до элемента по значению
    if (!tr || tr->inf == x)
        return tr; // если нашли элемент или дошли до конца дерева
    else{
        if (tr->inf > x){
            if (tr->left) path.push_back(tr->left); // если искомое значение меньше текущего, ищем в левом поддереве
            return find(tr->left, x, path);
        }
        else{
            if (tr->right) path.push_back(tr->right); // иначе ищем в правом поддереве
            return find(tr->right, x, path);
        }
    }
}

template<typename T>
tree<T> *Min(tree<T> *&tr){ // поиск максимального элемента 
    if (!tr->left) return tr;
    else return Min(tr->left);
}

template<typename T>
tree<T> *Max(tree<T> *&tr){ // поиск минимального элемента
    if (!tr->right) return tr;
    else return Max(tr->right);
}

template<typename T>
tree<T> *Next(tree<T> *x){ // поиск следующего элемента при симметричном обходе
    if (x == Max(x)) return nullptr; // если элемент уже является крайне правым, то следующий за ним - nullptr
    if (x->right) return Min(x->right); // иначе, если есть правая ветка, находим крайний левый элемент в правом поддереве
    tree<T> *y = x->parent; // иначе возвращаемся вверх
    while (x && x == y->right){ // пока не дошли до nullptr или пока текущий узел не стал левым ребёнком своего родителя (т.е. дошли до корня поддерева)
        x = y;
        y = x->parent;
    }
    return y;
}

template<typename T>
tree<T> *Prev(tree<T> *x){ // поиск предыдущего элемента при симметричном обходе
    if (x == Min(x)) return nullptr; // если элемент уже является крайне левым, то предыдущий - nullptr
    if (x->left) return Max(x->left); // иначе, если есть левая ветка, находим крайний правый элемент в левм поддереве
    tree<T> *y = x->parent; // иначе возвращаемся вверх
    while (x && x == y->left){ // пока не дошли до nullptr или пока текущий узел не стал правым ребёнком своего родителя (т.е. дошли до корня поддерева)
        x = y;
        y = x->parent;
    }
    return y;
}

template<typename T>
void erase(tree<T> *&tr, tree<T> *v){ // удаление узла
    tree<T> *p = v->parent; // родитель удаляемого узла
    if (!p && !v->left && !v->right){ // единственный элемент дерева
        tr = nullptr;
        delete v;
    }
    else if (!v->left && !v->right){ // лист 
        if (v == p->left) // если он является левым ребёнком родителя
            p->left = nullptr;
        else // если он является правым ребёнком родителя
            p->right =  nullptr;
        delete v;
    }
    else if (!v->left || !v->right){ // если есть только 1 ребёнок
        if (!p) { // если удаляем корень
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
        else{ // если удаляем не корень
            if (v->left){ // если есть левый ребёнок
                if (v == p->left) // если удаляемый элемент для родителя - левый ребёнок
                    p->left = v->left;
                else
                    p->right = v->left;
                v->left->parent = p;
            }
            else{ // аналогично, если есть правый ребёнок
                if (v == p->left)
                    p->left = v->right;
                else
                    p->right = v->right;
                v->right->parent = p; 
            }
        }
    }
    else{ // если есть оба ребёнка
        tree<T> *succ = Min(v->right); // ищем крайне левый элемент в правом поддереве
        v->inf = succ->inf; // присваиваем его значение узлу
        if (succ->parent->left == succ){ // на место крайне левого элемента встаёт его правый ребёнок
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
void create_tree(tree<T> *&tr, int &n){ // создаём дерево
    T x;
    cout << "Enter the number of nodes: "; cin >> n;
    cout << "Enter the values: ";
    for (int i = 0; i < n; ++i){
        cin >> x;
        insert(tr, x);
    }
}

template<typename T>
void inorder(tree<T> *&tr){ // вывод на экран дерева в порядке возрастания
    if (tr){
        inorder(tr->left);
        cout << tr->inf << " ";
        inorder(tr->right);
    }
}

template<typename T>
void postorder_delete(tree<T> *&tr, tree<T> *&v){ // обратный обход дерева и удаление нечётных элементов
    if (v){
        postorder_delete(tr, v->left);
        postorder_delete(tr, v->right);
        if (v->inf % 2) erase(tr, v);
    }
}

// 1. Дано дерево. Удалить нечетные элементы
// 10 7 2 9 1 5 3 6 4 8 10
void task1(){
    int n;
    tree<int> *tr = nullptr;
    create_tree(tr, n);
    postorder_delete(tr, tr);
    inorder(tr);
    //print_tree(tr);
}

// 2. Дано дерево. Вывести путь от узла A до узла B
// E B G A D C I H F J
void task2(){
    int n;
    tree<char> *tr = nullptr;
    create_tree(tr, n);
    char A, B;
    cout << "Enter the start and the finish: "; cin >> A >> B;
    vector<tree<char>*> path;
    tree<char>* A_node = find(tr, A, path); // ищем путь до начальной вершины
    path.clear();
    path.push_back(A_node);
    find(A_node, B, path); // ищем путь
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
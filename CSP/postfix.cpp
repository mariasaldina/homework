#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

struct stack{ // стек
    char inf;
    stack *next;
};

void push_stack(stack *&h, char x){ // добавление элемента в конец стека
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

char pop_stack(stack *&h){ // удаление элемента из стека
    char i = h->inf; // сохраняем значение головы
    stack *r = h; // сохраняем указатель на голову 
    h = h->next; // переносим голову на следующий элемент
    delete r; // удаляем указатель на голову
    return i; // возвращаем удалённое значение
}

bool is_operation(char x){ // является ли символ операцией
    return x == ')' || x == '(' || x == '+' || x == '-' || x == '*' || x == '/';
}

int prior(char x){ // приоритет операций
    if (x == '(' || x == ')') return 1;
    if (x == '+' || x == '-') return 2;
    if (x == '*' || x == '/') return 3;
}

bool is_correct(string s){ // проверка корректности ввода
    int count_open = (s[0] == '('), count_close = (s[0] == ')');
    for (int i = 0; i < s.length(); ++i) if (s[i] == ' ') s.erase(i);
    for (int i = 1; i < s.length(); ++i){
        if ((isdigit(s[i]) || isalpha(s[i])) && (isdigit(s[i - 1]) || isalpha(s[i - 1]))) return false; // две цифры или буквы подряд
        if (s[i - 1] == '(' && is_operation(s[i]) || s[i] == ')' && is_operation(s[i - 1])) return false; // <операция>) или (<операция>
        if (i != s.length() - 1 && (s[i] == '(' || s[i] == ')') && (isdigit(s[i - 1]) || isalpha(s[i - 1])) && (isdigit(s[i + 1]) || isalpha(s[i + 1])))
            return false; // скобка между операндами
        count_open += (s[i] == '(');
        count_close += (s[i] == ')');
    }
    if (count_open != count_close) return false; // не совпадает количество скобок
    else return true;
}

string postfix(string expression){ // перевод выражения в постфиксную форму
    if (!is_correct(expression)) return "невозможно перевести, некорректное выражение\n";
    stack *h = nullptr; // создаём стек
    string result;
    for (char x : expression){
        if (isdigit(x) || isalpha(x)) result += x; // число / переменную записываем в результат
        else if (x == '(') push_stack(h, x); // открывающую скобку - в стек
        else if (!h && is_operation(x)) push_stack(h, x); // если стек пуст, записываем в него операцию
        else if (x == ')'){ // если рассматриваем закрывающую скобку
            while (h && h->inf != '(') result += pop_stack(h); // пока не встретим в стеке открывающую скобку, удаляем из него по символу и записываем в результат
            if (h) pop_stack(h);
        }
        else if (is_operation(x)){
            if (prior(x) > prior(h->inf)) push_stack(h, x); // если приоритет операции больше, чем у головы стека, записываем её в стек
            else{
                while (h && prior(x) <= prior(h->inf)) result += pop_stack(h); // иначе удаляем удаляем из стека по символу и записываем в результат,
                push_stack(h, x);                                              // пока это условие не выполнится
            }
        }
    }
    while (h) result += pop_stack(h);
    return result;
}

int main(){
    SetConsoleCP(1251); // установка кодировки win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодировки win-cp 1251 в поток вывода
    cout << "Введите математическое выражение в инфиксной форме: ";
    string expression; getline(cin, expression);
    cout << "Выражение в постфиксной форме: " << postfix(expression);
    return 0;
}
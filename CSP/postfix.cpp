#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

struct stack{ // ����
    char inf;
    stack *next;
};

void push_stack(stack *&h, char x){ // ���������� �������� � ����� �����
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

char pop_stack(stack *&h){ // �������� �������� �� �����
    char i = h->inf; // ��������� �������� ������
    stack *r = h; // ��������� ��������� �� ������ 
    h = h->next; // ��������� ������ �� ��������� �������
    delete r; // ������� ��������� �� ������
    return i; // ���������� �������� ��������
}

bool is_operation(char x){ // �������� �� ������ ���������
    return x == ')' || x == '(' || x == '+' || x == '-' || x == '*' || x == '/';
}

int prior(char x){ // ��������� ��������
    if (x == '(' || x == ')') return 1;
    if (x == '+' || x == '-') return 2;
    if (x == '*' || x == '/') return 3;
}

bool is_correct(string s){ // �������� ������������ �����
    int count_open = (s[0] == '('), count_close = (s[0] == ')');
    for (int i = 0; i < s.length(); ++i) if (s[i] == ' ') s.erase(i);
    for (int i = 1; i < s.length(); ++i){
        if ((isdigit(s[i]) || isalpha(s[i])) && (isdigit(s[i - 1]) || isalpha(s[i - 1]))) return false; // ��� ����� ��� ����� ������
        if (s[i - 1] == '(' && is_operation(s[i]) || s[i] == ')' && is_operation(s[i - 1])) return false; // <��������>) ��� (<��������>
        if (i != s.length() - 1 && (s[i] == '(' || s[i] == ')') && (isdigit(s[i - 1]) || isalpha(s[i - 1])) && (isdigit(s[i + 1]) || isalpha(s[i + 1])))
            return false; // ������ ����� ����������
        count_open += (s[i] == '(');
        count_close += (s[i] == ')');
    }
    if (count_open != count_close) return false; // �� ��������� ���������� ������
    else return true;
}

string postfix(string expression){ // ������� ��������� � ����������� �����
    if (!is_correct(expression)) return "���������� ���������, ������������ ���������\n";
    stack *h = nullptr; // ������ ����
    string result;
    for (char x : expression){
        if (isdigit(x) || isalpha(x)) result += x; // ����� / ���������� ���������� � ���������
        else if (x == '(') push_stack(h, x); // ����������� ������ - � ����
        else if (!h && is_operation(x)) push_stack(h, x); // ���� ���� ����, ���������� � ���� ��������
        else if (x == ')'){ // ���� ������������� ����������� ������
            while (h && h->inf != '(') result += pop_stack(h); // ���� �� �������� � ����� ����������� ������, ������� �� ���� �� ������� � ���������� � ���������
            if (h) pop_stack(h);
        }
        else if (is_operation(x)){
            if (prior(x) > prior(h->inf)) push_stack(h, x); // ���� ��������� �������� ������, ��� � ������ �����, ���������� � � ����
            else{
                while (h && prior(x) <= prior(h->inf)) result += pop_stack(h); // ����� ������� ������� �� ����� �� ������� � ���������� � ���������,
                push_stack(h, x);                                              // ���� ��� ������� �� ����������
            }
        }
    }
    while (h) result += pop_stack(h);
    return result;
}

int main(){
    SetConsoleCP(1251); // ��������� ��������� win-cp 1251 � ����� �����
    SetConsoleOutputCP(1251); // ��������� ��������� win-cp 1251 � ����� ������
    cout << "������� �������������� ��������� � ��������� �����: ";
    string expression; getline(cin, expression);
    cout << "��������� � ����������� �����: " << postfix(expression);
    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct queue{ // �������
    string inf;
    queue *next;
};

void push_queue(queue *&h, queue *&t, string x){ // ���������� �������� � ����� �������
    queue *r = new queue;
    r->inf = x;
    r->next = nullptr;
    if (!h && !t){
        h = t = r;
    }
    else{
        t->next = r;
        t = r;
    }
}

string pop_queue(queue *&h, queue *&t){ // �������� �������� �� ������ �������
    string x = h->inf;
    queue *p = h;
    h = h->next;
    if (!h) t = nullptr;
    delete p;
    return x;
}

vector<string> bfs(map<string, vector<string>> gr, int n, string s, string l){ // ����� ����� � ������
    map<string, int> used;
    for (auto it = gr.begin(); it != gr.end(); ++it) used[it->first] = -1;
    used[s] = 0; // �������� ������ ������� ��� ����������
    queue *h = nullptr, *t = nullptr; // ������ �������
    push_queue(h, t, s); // �������� ������� � �������
    map<string, string> p; // ������ "�������": ��� ������ ������� ������� �������, �� ������� �� � �� ������
    while (h){ // ���� ������� �� �����
        string x = pop_queue(h, t); // ������� ������ �� �������
        for (int i = 0; i < gr[x].size(); ++i){ // ���������� �� ������ ������� � ������� ������
            if (used[gr[x][i]] == -1){ // ���� ��� ������� ��� �� ��������
                string y = gr[x][i];
                used[y] = used[x] + 1; // �������� � ��� ���������� � ������������ ��������� ����� ����������� ����
                push_queue(h, t, y); // � ��������� � �������
                p[y] = x;
            }
        }
    }
    vector<string> ans; // �����
    while (l != s){ // ��������������� ����
        ans.push_back(l);
        l = p[l];
    }
    ans.push_back(s);
    return ans;
}

map<string, vector<string>> create_map(){ // �������, ������������ ��� ��������� ���� ����
    map<string, vector<string>> chessboard;
    string square;
    vector<string> letters = {"A", "B", "C", "D", "E", "F", "G", "H"};
    vector<string> digits = {"1", "2", "3", "4", "5", "6", "7", "8"};
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            square = letters[i] + digits[j];
            if (i - 2 >= 0){
                if (j - 1 >= 0) chessboard[square].push_back(letters[i - 2] + digits[j - 1]);
                if (j + 1 < 8) chessboard[square].push_back(letters[i - 2] + digits[j + 1]);
            }
            if (i + 2 < 8){
                if (j - 1 >= 0) chessboard[square].push_back(letters[i + 2] + digits[j - 1]);
                if (j + 1 < 8) chessboard[square].push_back(letters[i + 2] + digits[j + 1]);
            }
            if (j - 2 >= 0){
                if (i - 1 >= 0) chessboard[square].push_back(letters[i - 1] + digits[j - 2]);
                if (i + 1 < 8) chessboard[square].push_back(letters[i + 1] + digits[j - 2]);
            }
            if (j + 2 < 8){
                if (i - 1 >= 0) chessboard[square].push_back(letters[i - 1] + digits[j + 2]);
                if (i + 1 < 8) chessboard[square].push_back(letters[i + 1] + digits[j + 2]);
            }
        }
    }
    return chessboard;
}

bool correct(string s){ // �������� �����
    if (!isalpha(s[0]) || !isdigit(s[1]) || s.length() != 2) return false;
    else return true;
}

int main(){
    map<string, vector<string>> chessboard = create_map();
    map<string, int> used;
    cout << "Enter the start and the finish squares: ";
    string s, l; cin >> s >> l; // ��������� � �������� ������
    while (!correct(s) || !correct(l)){ // �������� �����
        cout << "Forbidden symbols, please try again\n";
        cin >> s >> l;
    }
    vector<string> ans = bfs(chessboard, 64, s, l);
    cout << "The shortest path: ";
    for (int i = ans.size() - 1; i > -1; --i) cout << ans[i] << " ";
    return 0;
}
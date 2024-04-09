#include <iostream> //потоки ввода-вывода
#include <set> //множества
#include <string> //строки
#include <algorithm>
#include <fstream>
using namespace std;

ifstream in("in3.txt");

int main(){
    setlocale(LC_ALL, "RUS");
    cout << "Найти слова (без учета регистра), которые встречаются только в вопросительных предложениях.\n\n";
    set<string> question, others, sentence, result;
    string s, separators = ",.!?\":;-";
    while (in.peek() != EOF){
        if (in.peek() == '\n') cout << '\n';
        in >> s;
        cout << s << " ";
        char a = tolower(s[0]);
        s.replace(0, 1, string() + a); //приводим к нижнему регистру
        char last = *(s.begin() + s.length() - 1); //последняя буква
        if (separators.find(last) != string::npos) s.erase(s.length() - 1); //если слово оканчивается знаком препинания, удаляем его
        sentence.insert(s); //добавляем в предложение
        if (last == '.' || last == '!'){ //предложения с .!
            set_union(others.begin(), others.end(), sentence.begin(), sentence.end(), inserter(others, others.begin()));
            sentence.clear();
        }
        else if (last == '?'){ //предложения с ?
            set_union(question.begin(), question.end(), sentence.begin(), sentence.end(), inserter(question, question.begin()));
            sentence.clear();
        }
    }
    cout << "\n" << "\n";
    //слова, содержащиеся в question, но не содержащиеся в others
    set_difference(question.begin(), question.end(), others.begin(), others.end(), inserter(result, result.begin()));
    for (auto it = result.begin(); it != result.end(); ++it) cout << *it << " ";
    return 0;
}
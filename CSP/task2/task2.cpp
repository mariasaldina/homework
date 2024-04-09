#include <iostream> //потоки ввода-вывода
#include <map> //словарь
#include <fstream>
using namespace std;

ifstream in("in.txt");

int main(){
    setlocale(LC_ALL, "RUS");
    cout << "Во входном файле задан набор слов и целых чисел, разделенных пробелами. Найти числа, встречающиеся ровно k раз.\n";
    int k; cout << "k = "; cin >> k; cout << "Текст: ";
    string s, digits = "0123456789";
    map<int, int> m;
    while (in.peek() != EOF){
        if (in.peek() == '\n') cout << "\n";
        in >> s;
        cout << s << " ";
        if (s.find_first_not_of(digits) == string::npos) m[stoi(s)]++; //подсчитываем, сколько раз встречается каждое число
    }
    cout << endl << "Numbers: ";
    for (auto it = m.begin(); it != m.end(); ++it){
        if (it -> second == k) cout << it -> first << " "; //выводим числа, которые встречаюся k раз
    }
    return 0;
}
#include <iostream> // потоки ввода-вывода
#include <vector> //вектор
#include <numeric>
#include <functional>
using namespace std;

int main(){
    setlocale(LC_ALL, "RUS");
    cout << "Используя библиотеки numeric и functional, найти факториал числа n.\n";
    int n; cout << "n = "; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = i + 1;
    cout << "n! = " << accumulate(a.begin(), a.end(), 1, multiplies<int>());
    return 0;
}
#include <iostream> // потоки ввода-вывода
#include <vector> //вектор
#include <algorithm> //алгоритмы
#include <functional>
using namespace std;

int main(){
    setlocale(LC_ALL, "RUS");
    cout << "Дан набор целых чисел. Удалить все нечетные числа.\n";
    int n;
    cout << "Размер: "; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    auto it = remove_if(a.begin(), a.end(), [] (int x) {return x % 2;});
    a.erase(it, a.end());
    for (auto it = a.begin(); it != a.end(); ++it) cout << *it << " ";
    return 0;
}
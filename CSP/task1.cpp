#include <iostream> //потоки ввода-вывода
#include <set> //множества
#include <algorithm>
#include <time.h>
using namespace std;

int main(){
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    int n, x; cout << "Количество элементов: "; cin >> n;
    set<int> s, digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, result;
    cout << "Последовательность: ";
    for (int i = 0; i < n; ++i) {
        x = rand() % 5000; //генерируем элементы последовательности
        cout << x << " ";
        if (x >= 100 && x <= 999){ //цифры, содержащиеся в трёхзначных числах
            while (x > 0){
                s.insert(x % 10);
                x /= 10;
            }
        }
    }
    cout << endl;
    set_difference(digits.begin(), digits.end(), s.begin(), s.end(), inserter(result, result.begin()));
    for (auto it = result.begin(); it != result.end(); ++it) cout << *it << " ";
    return 0;
}
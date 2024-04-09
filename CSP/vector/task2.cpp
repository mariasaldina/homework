#include <iostream> // потоки ввода-вывода
#include <vector> //вектор
#include <algorithm> //алгоритмы
#include <functional>
using namespace std;

void print(vector<int> a){
    for (auto it = a.begin(); it != a.end(); ++it) cout << *it << " ";
}

int main(){
    setlocale(LC_ALL, "RUS");
    int n;
    cout << "Размер: "; cin >> n;
    vector<int> a(n), b1(n), b2(n), c(n), c2(n);
    int first_even = -1, first_even_i, last_odd, last_odd_i;
    for (int i = 0; i < n; ++i){ //ввод последовательности, поиск первого чётного и последнего нечётного элементов
        cin >> a[i];
        if (first_even == -1 && a[i] % 2 == 0){
            first_even_i = i;
            first_even = a[i];
        }
        if (a[i] % 2){
            last_odd_i = i;
            last_odd = a[i];
        }
    }
    
    cout << "Создать новую последовательность, заменив все числа в диапазоне от первого четного до последнего нечетного минимальным числом.\n";
    int min = *min_element(a.begin(), a.end()); //минимальный элемент
    cout << "1й вариант (диапазон значений): ";
    if (first_even > last_odd) swap(first_even, last_odd);
    replace_copy_if(a.begin(), a.end(), b1.begin(), [&first_even, &last_odd](int x) {return (x >= first_even && x <= last_odd);}, min);
    print(b1);
    cout << "\n2й вариант (диапазон индексов): ";
    copy(a.begin(), a.end(), b2.begin()); //копируем вектор а в вектор b
    if (first_even_i > last_odd_i) swap(first_even_i, last_odd_i);
    for (int i = first_even_i; i <= last_odd_i; ++i) b2[i] = min; //заменяем элементы между первым чётным и последним нечётным
    print(b2);

    cout << "\nСоздать новую последовательность, применив циклический сдвиг так, чтобы на первом месте стоял максимальный элемент.\n";
    auto mx_it = max_element(a.begin(), a.end()); //максимальный элемент
    copy(mx_it, a.end(), c.begin()); //копируем элементы после максимального
    copy(a.begin(), mx_it, c.begin() + (a.begin() + n - mx_it)); //и перед максимальным
    print(c);

    cout << "\nОтсортировать последовательность, удалив повторяющиеся элементы.\n";
    sort(a.begin(), a.end()); //сортировка
    auto it = unique(a.begin(), a.end()); //отправляем одинаковые элементы в конец
    a.erase(it, a.end()); //удаляем повторы
    print(a);
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void cocktailsort(vector<int> &a, int n){
    int begin = -1, end = a.size() - 1;
    while (true){
        bool flag = false;
        ++begin;
        for (int j = begin; j < end; ++j){
            if (a[j] > a[j + 1]){
                swap(a[j], a[j + 1]); flag = true;
            }
        }
        if (flag == false) break;
        flag = false; --end;
        for (int j = end; j >= begin; --j){
            if (a[j] > a[j + 1]){
                swap(a[j], a[j + 1]); flag = true;
            }
        }
        cout << endl;
        for (int i = 0; i < n; ++i) cout << a[i] << " ";
    }
}

void choice_sort(vector<int> &a, int n){
    for (int i = 0; i < n - 1; ++i){
        swap(*min_element(a.begin() + i, a.end()), a[i]);
    }
}

int main(){
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    choice_sort(a, n);
    for (int i = 0; i < n; ++i) cout << a[i] << " ";
    return 0;
}
#include <iostream> //потоки ввода-вывода
#include <map> //словарь
#include <string> //строка
#include <fstream> //файловые потоки
#include <time.h>
#include <Windows.h>
using namespace std;

ifstream in("russian_nouns.txt");

//выбор случайного слова из файла russian_nouns.txt
string choice_of_word(){
    srand(time(NULL));
    int number_of_word = rand() % 51301;
    string word;
    for (int i = 0; i <= number_of_word; ++i)
        getline(in, word);
    in.close();
    return word;
}

//ввод пользователем буквы или слова
int input(string word, string &letter, string &user_word, map<char, bool> alphabet){
    cout << "¬ведите букву или слово целиком: "; cin >> letter;
    if (letter.length() > 1 && letter == word) { //если пользователь угадал слово целиком
        user_word = letter;
        return 0;
    }
    else if (letter.length() > 1){ //если пользователь не угадал слово целиком
        cout << "Ќе угадали :(\n";
        return 0;
    }
    else if (alphabet[letter[0]] == 1){ //если буква введена повторно
        cout << "¬ы уже вводили эту букву\n";
        return 1;
    }
    else{
        if (word.find(letter) == string::npos){ //если буквы нет в слове
            cout << "“акой буквы в слове нет :(\n";
            return 0;
        }
        else return 2;
    }
}

//поиск и замена _ на угаданную букву
void search(string word, string letter, string &user_word){
    string::size_type number_of_letter = word.find(letter);
    while (number_of_letter != string::npos){
        user_word.replace(number_of_letter, 1, letter);
        number_of_letter = word.find(letter, number_of_letter + 1);
    }
    cout << user_word << "\n";
}

//вывод алфавита
void print_alphabet(char letter, map<char, bool> &alphabet){
    alphabet[letter] = 1;
    for (auto i = alphabet.begin(); i != alphabet.end(); ++i)
        if (i -> second == 0) cout << i -> first << " ";
        else cout << "\x1b[31m" << i -> first << "\x1b[0m "; //использованные буквы выдел€ютс€ красным цветом
    cout << "\n";
}

//игра
void guess(string word){
    map<char, bool> alphabet;
    for (char i = 'а'; i < '€'; ++i)
        alphabet[i] = 0; //если буква ещЄ не использовалась, значение по ключу равно 0, иначе 1
    string letter, user_word(word.length(), '_');
    int max_moves = word.length() + 10, moves = 0, input_result;
    cout << user_word << "\nћаксимальное количество ходов: " << max_moves << "\n";
    while (moves != max_moves && user_word != word){ //пока не кончатс€ ходы или пользователь не угадает слово
        input_result = input(word, letter, user_word, alphabet);
        if (letter.length() == 1) print_alphabet(letter[0], alphabet);
        switch (input_result){
            case 0: break; //если пользователь не угадал букву/слово или угадал слово целиком
            case 1: continue; break; //если буква введена повторно
            case 2: search(word, letter, user_word); break; //если буква угадана
        }
        cout << "¬ы сделали " << ++moves << " ходов, осталось " << max_moves - moves << "\n";
    }
    if (user_word == word) cout << "”ра, победа!\n";
    else cout << "¬ы проиграли :(\n" << "ѕравильный ответ: " << word << "\n";
}

int main(){
    SetConsoleCP(1251); //установка кодировки win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); //установка кодировки win-cp 1251 в поток вывода
    guess(choice_of_word());
    return 0;
}
#include <iostream> //������ �����-������
#include <map> //�������
#include <string> //������
#include <fstream> //�������� ������
#include <time.h>
#include <Windows.h>
using namespace std;

ifstream in("russian_nouns.txt");

//����� ���������� ����� �� ����� russian_nouns.txt
string choice_of_word(){
    srand(time(NULL));
    int number_of_word = rand() % 51301;
    string word;
    for (int i = 0; i <= number_of_word; ++i)
        getline(in, word);
    in.close();
    return word;
}

//���� ������������� ����� ��� �����
int input(string word, string &letter, string &user_word, map<char, bool> alphabet){
    cout << "������� ����� ��� ����� �������: "; cin >> letter;
    if (letter.length() > 1 && letter == word) { //���� ������������ ������ ����� �������
        user_word = letter;
        return 0;
    }
    else if (letter.length() > 1){ //���� ������������ �� ������ ����� �������
        cout << "�� ������� :(\n";
        return 0;
    }
    else if (alphabet[letter[0]] == 1){ //���� ����� ������� ��������
        cout << "�� ��� ������� ��� �����\n";
        return 1;
    }
    else{
        if (word.find(letter) == string::npos){ //���� ����� ��� � �����
            cout << "����� ����� � ����� ��� :(\n";
            return 0;
        }
        else return 2;
    }
}

//����� � ������ _ �� ��������� �����
void search(string word, string letter, string &user_word){
    string::size_type number_of_letter = word.find(letter);
    while (number_of_letter != string::npos){
        user_word.replace(number_of_letter, 1, letter);
        number_of_letter = word.find(letter, number_of_letter + 1);
    }
    cout << user_word << "\n";
}

//����� ��������
void print_alphabet(char letter, map<char, bool> &alphabet){
    alphabet[letter] = 1;
    for (auto i = alphabet.begin(); i != alphabet.end(); ++i)
        if (i -> second == 0) cout << i -> first << " ";
        else cout << "\x1b[31m" << i -> first << "\x1b[0m "; //�������������� ����� ���������� ������� ������
    cout << "\n";
}

//����
void guess(string word){
    map<char, bool> alphabet;
    for (char i = '�'; i < '�'; ++i)
        alphabet[i] = 0; //���� ����� ��� �� ��������������, �������� �� ����� ����� 0, ����� 1
    string letter, user_word(word.length(), '_');
    int max_moves = word.length() + 10, moves = 0, input_result;
    cout << user_word << "\n������������ ���������� �����: " << max_moves << "\n";
    while (moves != max_moves && user_word != word){ //���� �� �������� ���� ��� ������������ �� ������� �����
        input_result = input(word, letter, user_word, alphabet);
        if (letter.length() == 1) print_alphabet(letter[0], alphabet);
        switch (input_result){
            case 0: break; //���� ������������ �� ������ �����/����� ��� ������ ����� �������
            case 1: continue; break; //���� ����� ������� ��������
            case 2: search(word, letter, user_word); break; //���� ����� �������
        }
        cout << "�� ������� " << ++moves << " �����, �������� " << max_moves - moves << "\n";
    }
    if (user_word == word) cout << "���, ������!\n";
    else cout << "�� ��������� :(\n" << "���������� �����: " << word << "\n";
}

int main(){
    SetConsoleCP(1251); //��������� ��������� win-cp 1251 � ����� �����
    SetConsoleOutputCP(1251); //��������� ��������� win-cp 1251 � ����� ������
    guess(choice_of_word());
    return 0;
}
#include "card_game.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// Вывод меню
void menu() {
    cout << "\n";
    cout << "МЕНЮ: " << endl;
    cout << "1. Начать новую игру" << endl;
    cout << "2. Загрузить игру из файла" << endl;
    cout << "3. Сыграть один ход" << endl;
    cout << "4. Сыграть до конца игры" << endl;
    cout << "5. Показать текущее состояние игры" << endl;
    cout << "6. Сохранить игру в файл" << endl;
    cout << "7. Показать историю ходов" << endl;
    cout << "8. Сохранить историю ходов в файл" << endl;
    cout << "9. Перемешать и перераздать карты" << endl;
    cout << "10. Выйти из игры" << endl;
    cout << "\n"; 
    cout << "Выберите пункт меню (1-10): ";
}

// Вывод карт игрока
void printCards(const vector<Card>& cards, const string& player_name) {
    cout << player_name << " (" << cards.size() << " карт): ";
    
    if (cards.empty()) {
        cout << "нет карт";
    } else {
        // Показываем только первые 5 карт для краткости
        for (size_t i = 0; i < min(cards.size(), static_cast<size_t>(5)); ++i) {
            cout << cardToString(cards[i]) << " ";
        }
        
        if (cards.size() > 5) {
            cout << "... и ещё " << cards.size() - 5 << " карт";
        }
    }
    cout << endl;
}

// Вывод текущего состояния игры
void printGameState(const vector<Card>& player1, const vector<Card>& player2, int turn) {
    cout << "\n Текущее состояние игры (ход " << turn << ")" << endl;
    printCards(player1, "Игрок 1");
    printCards(player2, "Игрок 2");
}

// Вывод истории ходов
void printTurnHistory(const vector<TurnRecord>& history) {
    if (history.empty()) {
        cout << "История ходов пуста." << endl;
        return;
    }
    
    cout << "\n История ходов" << endl;
    cout << left << setw(5) << "Ход" << setw(15) << "Карта игрока 1" << setw(15) << "Карта игрока 2" << setw(15) << "Победитель" << setw(15) << "Карт у 1" << setw(15) << "Карт у 2" << endl;
    cout << string(80, '-') << endl;
    
    for (const auto& record : history) {
        cout << left << setw(5) << record.turn_number
             << setw(15) << record.player1_card
             << setw(15) << record.player2_card
             << setw(15) << record.winner
             << setw(15) << record.player1_cards_count
             << setw(15) << record.player2_cards_count << endl;
    }
}

// Функция для безопасного ввода числа
int getValidatedInput(int min_val, int max_val) {
    int choice;
    while (true) {
        cin >> choice;
        
        if (cin.fail() || choice < min_val || choice > max_val) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите число от " << min_val << " до " << max_val << ": ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
    }
}

// Функция для безопасного ввода строки
string getStringInput() {
    string input;
    getline(cin, input);
    return input;
}
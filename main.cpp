#include "card_game.h"
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;

// Глобальные переменные для состояния игры
vector<Card> player1_cards;
vector<Card> player2_cards;
vector<Card> table_cards;
vector<TurnRecord> turn_history;
int current_turn = 0;
bool game_active = false;

// Прототипы функций из interface.cpp
void menu();
void printGameState(const vector<Card>& player1, const vector<Card>& player2, int turn);
void printTurnHistory(const vector<TurnRecord>& history);
int getValidatedInput(int min_val, int max_val);
string getStringInput();

// Инициализация новой игры
void initializeNewGame() {
    vector<Card> deck;
    
    initializeDeck(deck);
    shuffleDeck(deck);
    dealCards(deck, player1_cards, player2_cards);
    
    table_cards.clear();
    turn_history.clear();
    current_turn = 0;
    game_active = true;
    
    cout << "\nНовая игра начата!" << endl;
    printGameState(player1_cards, player2_cards, current_turn);
}

// Выполнение одного хода с интерфейсом
void executeSingleTurn() {
    if (!game_active) {
        cout << "\nОшибка: игра не активна. Начните новую игру или загрузите существующую." << endl;
        return;
    }
    
    if (player1_cards.empty() || player2_cards.empty()) {
        cout << "\nИгра уже завершена. Начните новую игру." << endl;
        return;
    }
    
    current_turn++;
    TurnRecord record;
    
    playTurn(player1_cards, player2_cards, table_cards, record, current_turn);
    turn_history.push_back(record);
    
    cout << "\n Ход " << current_turn << endl;
    cout << "Игрок 1 выложил: " << record.player1_card << endl;
    cout << "Игрок 2 выложил: " << record.player2_card << endl;
    cout << "Победитель хода: " << record.winner << endl;
    cout << "Карт на столе: " << table_cards.size() << endl;
    
    printGameState(player1_cards, player2_cards, current_turn);
    
    // Проверка окончания игры
    if (checkGameEnd(player1_cards, player2_cards, current_turn)) {
        game_active = false;
    }
}

// Игра до завершения
void playToEnd() {
    if (!game_active) {
        cout << "\nОшибка: игра не активна. Начните новую игру или загрузите существующую." << endl;
        return;
    }
    
    cout << "\nИграем до завершения игры..." << endl;
    
    while (game_active && !checkGameEnd(player1_cards, player2_cards, current_turn)) {
        executeSingleTurn();
        
        // Ограничиваем вывод каждого хода для больших игр
        if (current_turn % 10 == 0 && current_turn > 0) {
            cout << "\nСыграно " << current_turn << " ходов. Продолжить автоматическую игру? (y/n): ";
            char choice;
            cin >> choice;
            cin.ignore();
            if (choice != 'y' && choice != 'Y') {
                break;
            }
        }
    }
}

// Основная функция
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Добро пожаловать в симулятор карточной игры 'Пьяница'!" << endl;
    bool running = true;
    while (running) {
        menu();
        int choice = getValidatedInput(1, 10);
        
        switch (choice) {
            case 1: // Новая игра
                initializeNewGame();
                break;
                
            case 2: // Загрузить игру
                {
                    cout << "Введите имя файла для загрузки: ";
                    string filename = getStringInput();
                    if (loadGame(player1_cards, player2_cards, filename)) {
                        game_active = true;
                        table_cards.clear();
                        turn_history.clear();
                        current_turn = 0;
                        printGameState(player1_cards, player2_cards, current_turn);
                    }
                }
                break;
                
            case 3: // Сыграть один ход
                executeSingleTurn();
                break;
                
            case 4: // Сыграть до конца
                playToEnd();
                break;
                
            case 5: // Показать состояние
                if (game_active) {
                    printGameState(player1_cards, player2_cards, current_turn);
                } else {
                    cout << "\nИгра не активна. Начните новую игру или загрузите существующую." << endl;
                }
                break;
                
            case 6: // Сохранить игру
                if (game_active) {
                    cout << "Введите имя файла для сохранения: ";
                    string filename = getStringInput();
                    saveGame(player1_cards, player2_cards, filename);
                } else {
                    cout << "\nНет активной игры для сохранения." << endl;
                }
                break;
                
            case 7: // Показать историю
                printTurnHistory(turn_history);
                break;
                
            case 8: // Сохранить историю
                if (!turn_history.empty()) {
                    cout << "Введите имя файла для сохранения истории: ";
                    string filename = getStringInput();
                    saveTurnHistory(turn_history, filename);
                } else {
                    cout << "\nИстория ходов пуста." << endl;
                }
                break;
                
            case 9: // Перераздать карты
                if (game_active) {
                    char confirm;
                    cout << "\nВы уверены, что хотите перемешать и перераздать карты? (y/n): ";
                    cin >> confirm;
                    cin.ignore();
                    if (confirm == 'y' || confirm == 'Y') {
                        initializeNewGame();
                    }
                } else {
                    initializeNewGame();
                }
                break;
                
            case 10: // Выход
                cout << "\nСпасибо за игру! До свидания!" << endl;
                running = false;
                break;
                
            default:
                cout << "\nНеверный выбор. Попробуйте снова." << endl;
        }
    }
    
    return 0;
}
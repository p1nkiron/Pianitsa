#include "card_game.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Сохранение игры в файл
bool saveGame(const vector<Card>& player1, const vector<Card>& player2, const string& filename) {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл для сохранения: " << filename << endl;
        return false;
    }
    
    // Сохраняем карты первого игрока
    file << "Player1:" << player1.size() << endl;
    for (const auto& card : player1) {
        file << card.rank << " " << card.suit << endl;
    }
    
    // Сохраняем карты второго игрока
    file << "Player2:" << player2.size() << endl;
    for (const auto& card : player2) {
        file << card.rank << " " << card.suit << endl;
    }
    
    file.close();
    cout << "Игра успешно сохранена в файл: " << filename << endl;
    return true;
}

// Загрузка игры из файла
bool loadGame(vector<Card>& player1, vector<Card>& player2, const string& filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл для загрузки: " << filename << endl;
        return false;
    }
    
    player1.clear();
    player2.clear();
    
    string line;
    bool readingPlayer1 = false;
    bool readingPlayer2 = false;
    int cardsToRead = 0;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        if (line.find("Player1:") == 0) {
            readingPlayer1 = true;
            readingPlayer2 = false;
            cardsToRead = stoi(line.substr(8));
            continue;
        }
        
        if (line.find("Player2:") == 0) {
            readingPlayer1 = false;
            readingPlayer2 = true;
            cardsToRead = stoi(line.substr(8));
            continue;
        }
        
        if (cardsToRead > 0) {
            istringstream iss(line);
            int rank, suit;
            if (iss >> rank >> suit) {
                Card card{rank, suit};
                
                if (readingPlayer1) {
                    player1.push_back(card);
                } else if (readingPlayer2) {
                    player2.push_back(card);
                }
                cardsToRead--;
            }
        }
    }
    
    file.close();
    cout << "Игра успешно загружена из файла: " << filename << endl;
    return true;
}

// Сохранение истории ходов в файл
bool saveTurnHistory(const vector<TurnRecord>& history, const string& filename) {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл для сохранения истории: " << filename << endl;
        return false;
    }
    
    file << "Номер хода, Карта игрока 1, Карта игрока 2, Победитель, Карт у игрока 1, Карт у игрока 2" << endl;
    
    for (const auto& record : history) {
        file << record.turn_number << "," << record.player1_card << "," << record.player2_card << "," << record.winner << "," << record.player1_cards_count << ","<< record.player2_cards_count << endl;
    }
    
    file.close();
    cout << "История ходов сохранена в файл: " << filename << endl;
    return true;
}
#include "head.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
void initializeDeck(vector<Card>& deck) {
    deck.clear();
    deck.reserve(DECK_SIZE);
    
    for (int suit = 0; suit < SUITS_COUNT; ++suit) {
        for (int rank = 0; rank < RANKS_COUNT; ++rank) {
            deck.push_back({rank, suit});
        }
    }
}

void shuffleDeck(vector<Card>& deck) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(deck.begin(), deck.end(), default_random_engine(seed));
}

void dealCards(vector<Card>& deck, vector<Card>& player1, vector<Card>& player2) {
    player1.clear();
    player2.clear();
    
    for (size_t i = 0; i < deck.size(); ++i) {
        if (i % 2 == 0) {
            player1.push_back(deck[i]);
        } else {
            player2.push_back(deck[i]);
        }
    }
}

string cardToString(const Card& card) {
    string result;
    switch(card.rank) {
        case 0: result = "6"; break;
        case 1: result = "7"; break;
        case 2: result = "8"; break;
        case 3: result = "9"; break;
        case 4: result = "10"; break;
        case 5: result = "J"; break;
        case 6: result = "Q"; break;
        case 7: result = "K"; break;
        case 8: result = "A"; break;
        default: result = "?"; break;
    }
    switch(card.suit) {
        case 0: result += "-черви"; break;
        case 1: result += "-буби"; break;
        case 2: result += "-крести"; break;
        case 3: result += "-пики"; break;
        default: result += "?"; break;
    }
    
    return result;
}

int compareCards(const Card& card1, const Card& card2) {
    if (card1.rank > card2.rank) {
        return 1;
    } else if (card1.rank < card2.rank) {
        return -1;
    } else {
        if (card1.suit > card2.suit) {
            return 1;
        } else if (card1.suit < card2.suit) {
            return -1;
        }
        return 0;
    }
}

void playTurn(vector<Card>& player1, vector<Card>& player2, vector<Card>& table, TurnRecord& record, int turn) {
    if (player1.empty() || player2.empty()) {
        return;
    }

    Card card1 = player1.front();
    Card card2 = player2.front();
    
    player1.erase(player1.begin());
    player2.erase(player2.begin());
    table.push_back(card1);
    table.push_back(card2);
    record.turn_number = turn;
    record.player1_card = cardToString(card1);
    record.player2_card = cardToString(card2);
    record.player1_cards_count = player1.size();
    record.player2_cards_count = player2.size();
    int result = compareCards(card1, card2);
    
    if (result > 0) {
        record.winner = "Игрок 1";
        takeAllCards(player1, table);
    } else if (result < 0) {
        record.winner = "Игрок 2";
        takeAllCards(player2, table);
    } else {
        record.winner = "Спор (ничья)";
    }
}
void takeAllCards(vector<Card>& winner, vector<Card>& table) {
    shuffleDeck(table);
    winner.insert(winner.end(), table.begin(), table.end());
    table.clear();
}

bool checkGameEnd(const vector<Card>& player1, const vector<Card>& player2, int turns) {
    if (player1.empty()) {
        cout << "\n Игрок 2 победил! У игрока 1 закончились карты." << endl;
        return true;
    }
    
    if (player2.empty()) {
        cout << "\nИгрок 1 победил! У игрока 2 закончились карты." << endl;
        return true;
    }
    
    if (turns >= MAX_TURNS) {
        cout << "\n=== Игра завершена по достижении максимального количества ходов (" << MAX_TURNS << ")." << endl;
        if (player1.size() > player2.size()) {
            cout << "Игрок 1 победил по количеству карт!" << endl;
        } else if (player2.size() > player1.size()) {
            cout << "Игрок 2 победил по количеству карт!" << endl;
        } else {
            cout << "Ничья! " << endl;
        }
        return true;
    }
    
    return false;

}

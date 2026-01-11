#include <string>
#include <vector>
using namespace std;

// Константы для игры
const int DECK_SIZE = 36;
const int SUITS_COUNT = 4;
const int RANKS_COUNT = 9;
const int MAX_TURNS = 1000; // Максимальное количество ходов для предотвращения бесконечной игры

// Структура для карты
struct Card {
    int rank;    // 6=0, 7=1, 8=2, 9=3, 10=4, J=5, Q=6, K=7, A=8
    int suit;    // 0-черви, 1-буби, 2-крести, 3-пики
};

// Структура для записи хода
struct TurnRecord {
    int turn_number;
    string player1_card;
    string player2_card;
    string winner;
    int player1_cards_count;
    int player2_cards_count;
};

// Функции для работы с картами
void initializeDeck(vector<Card>& deck);
void shuffleDeck(vector<Card>& deck);
void dealCards(vector<Card>& deck, vector<Card>& player1, vector<Card>& player2);
string cardToString(const Card& card);
int compareCards(const Card& card1, const Card& card2);

// Функции игровой логики
void playTurn(vector<Card>& player1, vector<Card>& player2,vector<Card>& table, TurnRecord& record, int turn);
void takeAllCards(vector<Card>& winner, vector<Card>& table);
bool checkGameEnd(const vector<Card>& player1, const vector<Card>& player2, int turns);

// Функции интерфейса
void menu();
void printCards(const vector<Card>& cards, const string& player_name);
void printGameState(const vector<Card>& player1, const vector<Card>& player2, int turn);
void printTurnHistory(const vector<TurnRecord>& history);

// Функции для работы с файлами
bool saveGame(const vector<Card>& player1, const vector<Card>& player2, const string& filename);
bool loadGame(vector<Card>& player1, vector<Card>& player2, const string& filename);
bool saveTurnHistory(const vector<TurnRecord>& history, const string& filename);

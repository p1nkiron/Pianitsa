#include <string>
#include <vector>
using namespace std;
const int DECK_SIZE = 36;
const int SUITS_COUNT = 4;
const int RANKS_COUNT = 9;
const int MAX_TURNS = 1000;
struct Card {
    int rank;
    int suit;
};

struct TurnRecord {
    int turn_number;
    string player1_card;
    string player2_card;
    string winner;
    int player1_cards_count;
    int player2_cards_count;
};
void initializeDeck(vector<Card>& deck);
void shuffleDeck(vector<Card>& deck);
void dealCards(vector<Card>& deck, vector<Card>& player1, vector<Card>& player2);
string cardToString(const Card& card);
int compareCards(const Card& card1, const Card& card2);
void playTurn(vector<Card>& player1, vector<Card>& player2,vector<Card>& table, TurnRecord& record, int turn);
void takeAllCards(vector<Card>& winner, vector<Card>& table);
bool checkGameEnd(const vector<Card>& player1, const vector<Card>& player2, int turns);
void menu();
void printCards(const vector<Card>& cards, const string& player_name);
void printGameState(const vector<Card>& player1, const vector<Card>& player2, int turn);
void printTurnHistory(const vector<TurnRecord>& history);
bool saveGame(const vector<Card>& player1, const vector<Card>& player2, const string& filename);
bool loadGame(vector<Card>& player1, vector<Card>& player2, const string& filename);
bool saveTurnHistory(const vector<TurnRecord>& history, const string& filename);

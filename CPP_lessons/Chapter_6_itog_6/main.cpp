/*
    Simplifed BlackJack Card Game.
    Read task.txt for more info  
*/

#ifdef __APPLE__
    #define CLS "clear"
#endif

#ifdef _WIN32
    #define CLS "cls"
#endif

#include <iostream>
#include <array> 
#include <cstdlib>
#include <ctime>
#include <string>

enum Suit{

    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADE,
    MAX_SUITS

};

enum Rank{

    RANK_2, RANK_3, RANK_4,  RANK_5,
    RANK_6, RANK_7, RANK_8,  RANK_9,
    RANK_10, JACK, QUEEN, KING, ACE,
    MAX_RANKS
};

struct Card{
    Rank rank;
    Suit suit;
};

void printCard(const Card &card){

    switch (card.rank)
    {
        case RANK_2: std::cout << "2"; break;
        case RANK_3: std::cout << "3"; break;
        case RANK_4: std::cout << "4"; break;
        case RANK_5: std::cout << "5"; break;
        case RANK_6: std::cout << "6"; break;
        case RANK_7: std::cout << "7"; break;
        case RANK_8: std::cout << "8"; break;
        case RANK_9: std::cout << "9"; break;
        case RANK_10: std::cout << "10"; break;
        case JACK: std::cout << "J"; break;
        case QUEEN: std::cout << "Q"; break;
        case KING: std::cout << "K"; break;
        case ACE: std::cout << "A"; break;
    }
    switch (card.suit)
    {
        case CLUBS: std::cout << "C"; break;
        case DIAMONDS: std::cout << "D"; break;
        case HEARTS: std::cout << "H"; break;
        case SPADE: std::cout << "S"; break;
    }
}

std::string getCard(const Card &card){

    std::string current;

    switch (card.rank)
    {
        case RANK_2: current = "2"; break;
        case RANK_3: current = "3"; break;
        case RANK_4: current = "4"; break;
        case RANK_5: current = "5"; break;
        case RANK_6: current = "6"; break;
        case RANK_7: current = "7"; break;
        case RANK_8: current = "8"; break;
        case RANK_9: current = "9"; break;
        case RANK_10: current = "10"; break;
        case JACK: current = "J"; break;
        case QUEEN: current = "Q"; break;
        case KING: current = "K"; break;
        case ACE: current = "A"; break;
    }
    switch (card.suit)
    {
        case CLUBS: current += "C"; break;
        case DIAMONDS: current += "D"; break;
        case HEARTS: current += "H"; break;
        case SPADE: current += "S"; break;
    }
    return current;
}


int getCardValue(Card &card){

    //printCard(card);

    switch(card.rank)
    {
        case RANK_2: return 2;
        case RANK_3: return 3;
        case RANK_4: return 4;
        case RANK_5: return 5;
        case RANK_6: return 6;
        case RANK_7: return 7;
        case RANK_8: return 8;
        case RANK_9: return 9;
        case RANK_10: return 10;
        case JACK: return 10;
        case QUEEN: return 10;
        case KING: return 10;
        case ACE: return 11;
    }
    return 0;
}

void cardSpawn(std::array<Card, 52> &deck){

    int card = 0;
    for (int suit = 0; suit < MAX_SUITS; ++suit){
        for (int rank = 0; rank < MAX_RANKS; ++rank)
        {
            deck[card].suit = static_cast<Suit>(suit);
            deck[card].rank = static_cast<Rank>(rank);
            ++card;
        }
        
    }
}

void printDeck(const std::array<Card, 52> &deck){
    int count{0};

    for (const auto &card : deck)
        {
            printCard(card);
            std::cout << ' ';
            ++count;
            if (count % 8 == 0)
                std::cout << std::endl;
        }
        std::cout << '\n' << std::endl;
    }

void swapCard(Card &a, Card &b){
        Card temp = a;
        a = b;
        b = temp;
    }

// get random number in custom range
int getRandomNumber(int min, int max){
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        // Равномерно распределяем рандомное число в нашем диапазоне
        return static_cast<int>(rand() * fraction * (max - min + 1) + min);
     }

void shuffleDeck(std::array<Card, 52> &deck){
        for (int i = 0; i < 52; ++i){
            swapCard(deck[i], deck[getRandomNumber(0, 51)]);
        }
    }

void printWinner(int winner){

    std::cout << std::endl;

    if (winner == 0){
        std::cout << "***** You won! *****" << std::endl;

    }else{
        std::cout << "Dealer won!\n" << std::endl;
    }
}

bool playerChoice(){
    char answer = ' ';
    std::cout << "Your move. Press (y) to Hit or (n) to Stand: ";
    std::cin >> answer;
    std::cout << std::endl;
    if (answer == 'y')
        return true;
    else
        return false;
}

bool playBlackjack(std::array<Card, 52> &deck){
    
    // Настраиваем стартовый режим игры
    cardSpawn(deck);
    shuffleDeck(deck);
    //printDeck(deck);

    Card *cardPtr = &deck[0];

    int playerTotal = 0;
    int dealerTotal = 0;

    std::string d_cardHolder = getCard(*cardPtr) + " ";
    std::string p_cardHolder;

    // Дилер получает одну карту
    dealerTotal += getCardValue(*cardPtr++);

    std::cout << "The dealer got " << d_cardHolder << "and is showing: " << dealerTotal << '\n';

    // Игрок получает две карты
    p_cardHolder = getCard(*cardPtr) + " ";
    playerTotal += getCardValue(*cardPtr++);
    p_cardHolder += getCard(*cardPtr) + " ";
    playerTotal += getCardValue(*cardPtr++);


    // Игрок начинает
    while (1) {
        std::cout << "You got " << p_cardHolder << "and have: " << playerTotal << '\n';
            
        if (playerTotal == 21) {
            std::cout << "***** BLACKJACK *****";
            return true;
        }
        if (playerTotal > 21)
            return false;
        if (!playerChoice())
            break;

        p_cardHolder += getCard(*cardPtr) + " ";
        playerTotal += getCardValue(*cardPtr++);
        
    }

    // Если игрок не проиграл и у него не больше 21 очка, то тогда
    //дилер получает карты до тех пор, пока у него не получится в сумме 17 очков
    while (dealerTotal < 17) {
            d_cardHolder += getCard(*cardPtr) + " ";
            dealerTotal += getCardValue(*cardPtr++);
            std::cout << "The dealer got " << d_cardHolder << "and now has " << dealerTotal << '\n';
        }
    // Если у дилера больше 21 очка, то игрок победил
    if (dealerTotal > 21) return true;

    return (playerTotal > dealerTotal);

}

int main(){

    system(CLS);

    std::cout << "**********************" << std::endl;
    std::cout << "*** BLACKJACK GAME ***" << std::endl;
    std::cout << "**********************" << std::endl << std::endl;

    srand(static_cast<unsigned int>(time(0)));
    std::array<Card, 52> deck;
    bool play = true;

    do{
        
        if (playBlackjack(deck))
            printWinner(0);
        else
            printWinner(1);

        char playAgain = ' ';

        std::cout << std::endl;

        std::cout << "Play again y/n: ";
        std::cin >> playAgain;
        if (playAgain == 'n')
            play = false;
        std::cout << std::endl;

    }while(play);

    return 0;
}
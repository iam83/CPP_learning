/*

            Задание No6
            Предположим, что мы хотим написать карточную игру.

            a) В колоде карт находятся 52 уникальные карты: 13 достоинств
                (2, 3, 4, 5, 6, 7, 8, 9, 10, Валет, Дама, Король, Туз)
                и 4 масти (трефы, бубны, червы, пики). Создайте два перечисления: первое для масти,
                второе для достоинств карт.

            b) Каждая карта должна быть представлена структурой Card,
                в которой хранится информация о достоинстве и масти карты
                (например, 4 бубны, король трефы). Создайте эту структуру.

            c) Создайте функцию printCard(), параметром которой будет константная ссылка
                типа структуры Card, которая будет выводить значения достоинства и масти
                определенной карты в виде 2-буквенного кода (например, валет пики будет выводиться
                как VP).

            d) Для представления целой колоды карт (52 карты) создайте массив
            deck (используя std::array) и инициализируйте каждый элемент определенной картой.

            е) Напишите функцию printDeck(), которая в качестве параметра принимает
                константную ссылку на массив deck и выводит все значения (карты). 
                Используйте цикл foreach.

            f) Напишите функцию swapCard(), которая принимает две карты и меняет местами их значения.

            Подсказка: Добавьте в каждое перечисление еще по одному элементу,
            который будет обозначать длину этого перечисления.

            Подсказка: Используйте оператор static_cast для конвертации целочисленной
            переменной в тип перечисления.

            g) Напишите функцию shuffleDeck() для перетасовки колоды карт.
                Для этого используйте цикл for с итерацией по массиву.
                Перетасовка карт должна произойти 52 раза.

                В цикле for выберите случайное число от 1 до 52 и вызовите swapCard(),
                параметрами которой будут текущая карта и карта, выбранная случайным образом.
                Добавьте в функцию main() возможность перетасовки и вывода уже обновленной
                (перетасованной) колоды карт.
            Подсказки:
                Для генерации случайных чисел смотрите урок No74.
                Не забудьте в начале функции main() вызвать функцию srand().
                Если вы используете Visual Studio, то не забудьте перед генерацией
                случайного числа вызвать один раз функцию rand().

            h) Напишите функцию getCardValue(), которая возвращает значение карты
            (например, 2 значит 2, 3 значит 3 и т.д., 10, валет, королева или король — это 10,
            туз — это 11).


*/

#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>

enum Suit{

    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADE,
    MAX_SUITS

};

enum Rank{

    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    JACK,
    QUEEN,
    KING,
    ACE,
    MAX_RANKS
};

struct Card{
    Rank rank;
    Suit suit;
};

int getCardValue(Card &card){

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
}

void printCard(const Card &card)
{
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

void printWinner(int winner, int playerResult, int dealerResult){
   
    std::cout << std::endl;
    std::cout << "___________________" << std::endl;
     std::cout << std::endl;
    if (winner == 0){
        std::cout << "*** You won! ***\n" << std::endl;
        std::cout << "Your result: " << playerResult << std::endl;
        std::cout << "Dealer result: " << dealerResult << std::endl;
    }else{
        std::cout << "Dealer won!\n" << std::endl;
        std::cout << "Dealer result: " << dealerResult << std::endl;
        std::cout << "Your result: " << playerResult << std::endl;
    }
}

int main(){

    srand(static_cast<unsigned int>(time(0)));
    

    bool playBlackjack = true;
    do{

    int p_counter{0}, d_counter{0}; //for counting cards during moves
    int playerResult{0};
    int dealerResult{0};
    Card *cardPtr;
    
    Card player;
    Card dealer;

    std::array<Card, 52> deck;
    cardSpawn(deck);
    shuffleDeck(deck);
    //printDeck(deck);

    cardPtr = &deck[0];

    dealerResult += getCardValue(*cardPtr++);
    d_counter++; //adding card
    playerResult += getCardValue(*cardPtr++);
    p_counter++;
    playerResult += getCardValue(*cardPtr++);
    p_counter++;

    if (playerResult == 21){
        printWinner(0, playerResult, dealerResult);
        return 0;
    }

    while(1){

        std::cout << std::endl;

        char answer = ' ';
        //std::cout << "Dealer's got " << d_counter << " cards. " << dealerResult << " points." << std::endl;
        std::cout << "You've got " << p_counter << " cards. " << playerResult << " points." << std::endl << std::endl;
        
        std::cout << "Your move. Press y to Hit or n to Stand: ";
        std::cin >> answer;

        if (answer == 'y'){
            playerResult += getCardValue(*cardPtr++);
            p_counter++;

            if (playerResult == 21){
                printWinner(0, playerResult, dealerResult);
                break;
            }
            if (playerResult > 21){
                printWinner(1, playerResult, dealerResult);
                break;
            }


        }else{
            std::cout << "You skipped. Dealer got 1 card" << std::endl;
            dealerResult += getCardValue(*cardPtr++);
            d_counter++;
            if (dealerResult == 21){
                printWinner(1, playerResult, dealerResult);
                break;
            }
            if (dealerResult > 21){
                printWinner(0, playerResult, dealerResult);
                break;
            }
        }


    }

    char playAgain = ' ';
    std::cout << std::endl;

    std::cout << "Play again y/n: ";
    std::cin >> playAgain;
    if (playAgain == 'n')
        playBlackjack = false;

    }while(playBlackjack);

    return 0;
}
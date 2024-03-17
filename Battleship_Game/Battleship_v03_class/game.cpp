#include "game.h"

#ifdef _WIN32
#define CLS "cls"
#define PAUSE "pause"
#endif
#ifdef __APPLE__
#define PAUSE "read"
#define CLS "clear"
#endif

extern int g_TIME;
extern std::string g_VERSION;


void Game::exit_app(){
    exit(0);
}


bool isDemo{false};

//DEBUGGING 
void Game::printMoveTable(const Field object) {
    int a{ 0 };
    for (int i = 0; i < static_cast<int>(object.moves.size()); ++i) {
        std::cout << object.moves[i] << " ";
        ++a;
        if (a % 10 == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool Game::playAgain() {

char exit;

do {
    std::cout << "  Would you like to play again (y/n)?: ";
    std::cin >> exit;

    if (exit == 'y' || exit == 'Y') {
        g_TIME = 1; //reset g_TIME to 1. otherwise it would accumulate the value from the previous runtime
        return true;
        break;
    }
    else if (exit == 'n' || exit == 'N') {
        std::cout << "  Thank you for playing. See you!" << std::endl;
        return false;
        break;
    }
    else {
        std::cin.clear(); // 
        std::cin.ignore(32767, '\n');
    }

} while (1);

std::cout << std::endl;
}

void Game::printFields(const Field& pc, const Field& user,
                ShipView field_view) {

    std::cout << std::endl;
    const std::string letters = "ABCDEFGHIJ";
    const std::string separator = "        ";
    std::cout << "      ";

    const char c_SHIP = '#';
    const char c_HIT = 'X';
    const char c_MISS = '~';
    const char c_FIELD = '.';
    const char c_BORDER = '.';
    const char c_BORDERHIT = '~';

    for (int c = 0; c < 10; ++c) {
        std::cout << c << " ";
    }

    std::cout << separator << "   ";

    for (int c = 0; c < 10; ++c) {
        std::cout << c << " ";
    }

    std::cout << std::endl;

    for (int row = 0; row < static_cast<int>(user.field.size()); ++row) {
        std::cout << "   " << letters[row] << "  "; //row number

        // user field
        for (int col = 0; col < static_cast<int>(user.field.size()); ++col) {
            if (user.field.at(row).at(col) == FieldCellStates::Ship) {
                std::cout << setColor(CColor::Yellow);
                std::cout << c_SHIP << " ";
                std::cout << setColor(CColor::Reset);
            }
            //border around ship
            else if (user.field.at(row).at(col) == FieldCellStates::Border) {
                std::cout << setColor(CColor::DarkGrey);
                std::cout << c_BORDER << " ";
                std::cout << setColor(CColor::Reset);
            }
            //ship is hit
            else if (user.field.at(row).at(col) == FieldCellStates::Hit) {
                std::cout << setColor(CColor::LightRed);
                std::cout << setColor(CColor::Negative);
                std::cout << c_HIT << " ";
                std::cout << setColor(CColor::Reset);
            }
            //border around hitted ship
            else if (user.field.at(row).at(col) == FieldCellStates::BorderHit) {
                std::cout << setColor(CColor::Blue);
                std::cout << c_BORDERHIT << " ";
                std::cout << setColor(CColor::Reset);
            }
            //missed hit
            else if (user.field.at(row).at(col) == FieldCellStates::Miss) {
                std::cout << setColor(CColor::Blue);
                std::cout << c_MISS << " ";
                std::cout << setColor(CColor::Reset);
            }
            //just empty field
            else {
                std::cout << setColor(CColor::DarkGrey);
                std::cout << c_FIELD << " ";
                std::cout << setColor(CColor::Reset);
            }
        }

        std::cout << separator;
        std::cout << letters[row] << "  ";

        // pc field
        for (int col = 0; col < static_cast<int>(pc.field.size()); ++col) {
            if (pc.field.at(row).at(col) == FieldCellStates::Ship) {
                std::cout << setColor(CColor::DarkGrey);
                if (field_view == ShipView::Visible) // make ships visible when game has ended
                    std::cout << c_SHIP << " ";
                else
                    std::cout << c_FIELD << " "; // use c_FIELD for game, use c_SHIP for DEBUGGING
                std::cout << setColor(CColor::Reset);
            }
            //border around ship
            else if (pc.field.at(row).at(col) == FieldCellStates::Border) {
                std::cout << setColor(CColor::DarkGrey);
                std::cout << c_BORDER << " ";
                std::cout << setColor(CColor::Reset);
            }
            //ship is hit
            else if (pc.field.at(row).at(col) == FieldCellStates::Hit) {
                std::cout << setColor(CColor::Green);
                std::cout << setColor(CColor::Negative);
                std::cout << c_HIT << " ";
                std::cout << setColor(CColor::Reset);
            }
            //border around hitted ship
            else if (pc.field.at(row).at(col) == FieldCellStates::BorderHit) {
                std::cout << setColor(CColor::LightRed);
                std::cout << c_BORDERHIT << " ";
                std::cout << setColor(CColor::Reset);
            }
            //missed hit
            else if (pc.field.at(row).at(col) == FieldCellStates::Miss) {
                std::cout << setColor(CColor::LightRed);
                std::cout << c_MISS << " ";
                std::cout << setColor(CColor::Reset);
            }
            //just empty field
            else {
                std::cout << setColor(CColor::DarkGrey);
                std::cout << c_FIELD << " ";
                std::cout << setColor(CColor::Reset);
            }
        }
        std::cout << std::endl;
    }

    std::cout << setColor(CColor::Reset);
    std::cout << std::endl;
}

bool Game::isAutomaticSetup(bool &isDemo){

    char exit;

    do {
        std::cout << "\n\n\n";
        std::cout << "\t\tB A T T L E S H I P  by  AU  " + g_VERSION;
        std::cout << "\n\n";
        std::cout << "        Choose ship setup mode\n\n";
        std::cout << "         'a' for Automatic\n";
        std::cout << "         'm' for Manual\n";
        std::cout << "         'd' for Demo mode\n";
        std::cout << "         'h' for Help/About\n";
        std::cout << "         'q' for Quit\n\n";
        std::cout << "          >: ";
        std::cin >> exit;
        std::cout << std::endl;
        
        if (exit == 'a' || exit == 'A') {
            std::cin.clear(); // 
            std::cin.ignore(32767, '\n');
            isDemo = false;
            return true;
            break;
        }
        else if (exit == 'm' || exit == 'M') {
            std::cin.clear(); // 
            std::cin.ignore(32767, '\n');
            isDemo = false;
            return false;
            break;
        }
        else if(exit == 'q' || exit == 'Q'){
            std::cout << "See you! Bye.\n\n";
            Game::exit_app();
        }
        else if(exit == 'd' || exit == 'D'){
            //demo mode when pc vs pc
            std::cin.clear(); // 
            std::cin.ignore(32767, '\n');
            isDemo = {true};
            g_TIME *= 3;
            return true;
        }
            else if (exit == 'h' || exit == 'H') {
            //print about/help message
            system(CLS);
            std::cout << "Battleship (also known as Battleships or Sea Battle)\nis a strategy type guessing game for two players.\n\nIt is played on ruled grids (paper or board) on which each player\'s fleet of warships are marked.\nThe locations of the fleets are concealed from the other player.\nPlayers alternate turns calling \"shots\" at the other player\'s ships,\nand the objective of the game is to destroy the opposing player\'s fleet.\n\n";
            std::cout << "      Automatic - means your ships will be placed automatically.\n";
            std::cout << "      Manual    - means you can decide where and how your ships will be placed.\n";
            std::cout << "      Demo      - means PC vs PC. It's just a demonstration of game play.\n\n";
            std::cout << "Written in C++ by AU as project-based learning in spare time. Thanks for playing.\n";
            std::cout << "Sources can be found on github.com/iam83\n\n";

            #ifdef __APPLE__
            std::cout << "Press Enter to go back...\n"; //this is for mac os x. otherwise it won't print anything.
            #endif

            system(PAUSE);
            system(CLS);

            std::cin.clear(); // 
            std::cin.ignore(32767, '\n');
        }
        else {
            system(CLS);
            std::cin.clear(); // 
            std::cin.ignore(32767, '\n');
        }

    } while (1);

    std::cout << std::endl;
}


void Game::printUpdateMessage(const Field &pc, const Field & user){


    std::cout << "   Your ships left: ";
    if (user.map.size() <= 3)
        std::cout << setColor(CColor::LightRed); //set a color LightRed if ships left <= 3
    std::cout << user.map.size();
    std::cout << setColor(CColor::Reset);

    if (user.message[2] == 'W') //if you sank a ship setColor Green
        std::cout << setColor(CColor::Green);
    if(user.message[6] == 'h') //if you hit a ship setColor Cyan
        std::cout << setColor(CColor::Cyan);

    std::cout << "\t\t" << user.message << std::endl;
    std::cout << setColor(CColor::Reset);

    std::cout << "     PC ships left: ";
    if (pc.map.size() <= 3)
        std::cout << setColor(CColor::LightRed);
    std::cout << pc.map.size();
    std::cout << setColor(CColor::Reset);

    if(pc.message[2] == 'O')
        std::cout << setColor(CColor::Red);
    if(pc.message[5] == 'h')
        std::cout << setColor(CColor::Yellow);
    std::cout << "\t\t" << pc.message << std::endl;
    std::cout << setColor(CColor::Reset);

    std::cout << "    Your last move: " << user.lastMove << std::endl;
    std::cout << "      PC last move: " << pc.lastMove << std::endl;
    
    std::cout << std::endl;
}

void Game::printCongrats(Player player) {

    std::string message_congrats = "";

    if (player == Player::User)
        message_congrats = "\t    *** CONGRATULATIONS! YOU WON!!! ***\n";
    else
        message_congrats = "\t             *** YOU LOST!!! ***\n";

    for (auto const& letter : message_congrats) {
        std::cout << letter;
        std::this_thread::sleep_for(std::chrono::milliseconds(25)); //25 ms
    }

    std::cout << std::endl;
}
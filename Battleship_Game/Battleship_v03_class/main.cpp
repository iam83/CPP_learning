/*



    ISSUES:
        FIXED 01. "You missed at" shows nothing in Automatic Mode
        FIXED 02. PC is not going
        FIXED 03. Need to revise isHit statuses.
        FIXED 04. Empty element was weirdly adding into std::map in Field::getCoord() in field.cpp
        FIXED 05. revise message status 

        06. While PC destroys a user's ship the message shows the same coordinate.

    TODO:
        01. Colorize messages.


*/


#define __DEBG false // set to true to enable DEBUG messages or false to disable.
                     // I'm using this workaround for debugging.
                     // I know it has got some special defines for NDEBUG but I made it simply.

#ifdef _WIN32
#define CLS "cls"
#define PAUSE "pause"
#endif

#ifdef __APPLE__
#define PAUSE "read"
#define CLS "clear"
#endif

#include "field.h"
#include "game.h"



std::string g_VERSION = "1.9";


int g_TIME = 1; //TIME factor for sleep::thread. Normal is 1 (but for demo mode it will decrease speed for x2) for debug put 0


//DEBUGGING ONLY
#if __DEBG
void printDebug(const Field& pc, const Field& user){
        std::cout << "Coord_str pc field: " << pc.m_coord_str << "\n";
        std::cout << "PC last move: " << pc.getLastMove() << "\n";
        std::cout << "User last move: " << user.getLastMove() << "\n";
        std::cout << "isHit pc = " << pc.isHit << "\n";
        std::cout << "isHit user = " << user.isHit << "\n";
        std::cout << "isPartlyHit pc = " << pc.isPartlyHit << "\n";
        std::cout << "isPartlyHit user = " << user.isPartlyHit << "\n";
        
}
#endif
////


int main(){

    srand(static_cast<unsigned int>(time(0)));

    Game game;

    Field user;
    Field pc;

    bool demo {false};
    
    //game loop
    do {

        system(CLS);

        pc.clearAll();
        pc.createGameField();

        user.clearAll();

        if (!game.isAutomaticSetup(demo)){
            system(CLS);
            std::cout << "\tManual setup\n";
            if (!user.manualSetup()){
                user.createGameField();
            }
        }else{
            std::cout << "\tAutomatic setup\n";
            user.createGameField();
            user.createMoveTable();
        }

        system(CLS);
        std::cout << setColor(CColor::Cyan);
        std::cout << "\tGame started!\n";
        std::cout << setColor(CColor::Reset);


        // if demo mode true
        if(demo) pc.createMoveTable();
        //

        while (1) {

            pc.checkField();
            user.checkField();

            #if !(__DEBG)
                game.printFields(pc, user, ShipView::Invisible);
            #else
                game.printFields(pc, user, ShipView::Visible);
            #endif

            game.printUpdateMessage(pc, user);


            if (!user.isHit){ // if PC doesn't hit user's ship then it's user's turn.

                if(!demo){  // if demo mode is not chosen
                    do {
                        std::cout << "  Enter Row and Column (eg. A0 or a0, or 'q' to quit):> ";
                        std::cin >> pc.m_coord_str;
                        pc.m_coord_str[0] = std::toupper(pc.m_coord_str[0]);

                        if (pc.m_coord_str == "Q") {
                            std::cout << "  See you, bye!\n\n";
                            return 0;
                        }

                        pc.setLastMove(pc.m_coord_str);

                    } while (!pc.isInputValid());


                }else{
                    // if demo mode is chosen
                    pc.getCoord(Player::User);
                }
                    #if !(__DEBG)
                        system(CLS);//COMMENT FOR DEBUG
                    #endif

                    //user move
                    if(!user.isHit){//if the previous PC move was not positive then execute User move
                        if (pc.isMove()) {
                            if (pc.checkMap(Player::User)) {

                                #if !(__DEBG)
                                    game.printFields(pc, user, ShipView::Invisible);
                                    system(CLS); //COMMENT FOR DEBUG
                                #else
                                game.printFields(pc, user, ShipView::Visible);
                                #endif
                                game.printCongrats(Player::User);
                                break;
                            }
                            user.setMessage("");
                            pc.isHit = true;
                            continue; // continue to next iteration bc User hit positive and move was true
                        }
                        else {
                            //pc.setLastMove(pc.m_coord_str);
                            pc.setMessage("    You missed at " + pc.getLastMove());
                            pc.isHit = false;
                        }

                        #if !(__DEBG)
                            game.printFields(pc, user, ShipView::Invisible);
                        #else
                            game.printFields(pc, user, ShipView::Visible);
                        #endif
                        game.printUpdateMessage(pc, user);
                    }

            }


             //pc move
             user.getCoord(Player::Pc);
             if (user.isMove()) {
                 if (user.checkMap(Player::Pc)) {
                     #if !(__DEBG)
                        //system(CLS); //COMMENT FOR DEBUG
                        game.printFields(pc, user, ShipView::Invisible);
                    #else
                    game.printFields(pc, user, ShipView::Visible);
                    #endif
                     game.printCongrats(Player::Pc);
                     break;
                 }
                 pc.setMessage("");
                 user.isHit = true;
            }
             else {
                 user.setMessage("     PC missed at " + user.getLastMove());
                 user.isHit = false;
            }
            #if !(__DEBG)
            system(CLS);//COMMENT FOR DEBUG
            #endif

              //DEBUGGING
            #if __DEBG
                std::cout << "AFTER PC move\n";
                printDebug(pc, user);
            #endif

        }
    } while (game.playAgain());


    return 0;
}
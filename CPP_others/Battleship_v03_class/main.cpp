/*



    ISSUES:
        01. "You missed at" shows nothing in Automatic Mode


*/


#define __DEBG true // set to true to enable DEBUG messages or false to disable.
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
        pc.createMoveTable();

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
        }

        system(CLS);
        std::cout << setColor(CColor::Cyan);
        std::cout << "\tGame started!\n";
        std::cout << setColor(CColor::Reset);


        // if demo mode true
        if(demo) user.createMoveTable();
        //

        while (1) {

            #if !(__DEBG)
            system(CLS);
            #endif

            pc.checkField();
            user.checkField();

            game.printFields(pc, user, ShipView::Invisible);
            game.printUpdateMessage(pc, user);
            
            #if __DEBG
                //printDebug();
            #endif


            if (!pc.isHit){
                if(!demo){
                    do {
                        std::cout << "  Enter Row and Column (eg. A0 or a0, or 'q' to quit):> ";
                        std::cin >> pc.coord_str;
                        pc.coord_str[0] = std::toupper(pc.coord_str[0]);
                        if (pc.coord_str == "Q") {
                            std::cout << "  See you, bye!\n\n";
                            return 0;
                        }

                    } while (!pc.isInputValid());

                }else{
                    //if demo mode is chosen
                    pc.getCoord(Player::User);
                }
                    #if !(__DEBG)
                        system(CLS);//COMMENT FOR DEBUG
                    #endif

                    //user move
                    if(!pc.isHit){//if the previous PC move was not positive then execute User move
                        if (pc.isMove()) {
                            if (pc.checkMap(Player::User)) {
                                #if !(__DEBG)
                                system(CLS); //COMMENT FOR DEBUG
                                #endif
                                game.printFields(pc, user, ShipView::Visible);
                                game.printCongrats(Player::User);
                                break;
                            }
                            //pc.message = "";
                            user.isHit = true;
                            continue; // continue to next iteration bc User hit positive and move was true
                        }
                        else {
                            user.message = "  You missed at " + pc.lastMove;
                            user.isHit = false;
                        }

                        game.printFields(pc, user, ShipView::Invisible);
                        game.printUpdateMessage(pc, user);

                        //DEBUGGING
                        #if __DEBG
                            //printDebug();
                        #endif
                    }

            }


             //pc move
             user.getCoord(Player::Pc);
             if (user.isMove()) {
                 if (user.checkMap(Player::Pc)) {
                     //system(CLS); //COMMENT FOR DEBUG
                     game.printFields(pc, user, ShipView::Visible);
                     game.printCongrats(Player::Pc);
                     break;
                 }
                 //user.message = "";
                 pc.isHit = true;
            }
             else {
                 pc.message = "   PC missed at " + user.lastMove;
                 pc.isHit = false;
            }
            #if !(__DEBG)
            system(CLS);//COMMENT FOR DEBUG
            #endif

        }
    } while (game.playAgain());


    return 0;
}
#pragma once
#include <iostream>
#include "ccolor.h"
#include "enums.h"
#include <thread>
#include "field.h"


class Game{

private:
    void exit_app();

public:
    bool isDemo;
    bool playAgain();
    void printMoveTable(const Field);
    void printFields(const Field &, const Field&, ShipView);
    bool isAutomaticSetup(bool &);
    void printUpdateMessage(const Field &, const Field &);
    void printCongrats(Player);

};

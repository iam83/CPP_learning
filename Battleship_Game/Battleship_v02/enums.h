#pragma once

enum Player {
    User,
    Pc
};

enum ShipView {
    Invisible,
    Visible
};

enum Warning{
    TryAgain,
    TryAgainHorizontal,
    TryAgainVertical,
    TryAgainWrongCoord,
    TryAgainHitThere
};

enum Direction {
    Horizontal,
    Vertical
};

enum ShipType {

    Submarine = 1,
    Cruiser = 2,
    Battleship = 3,
    Carrier = 4

};

enum FieldCellStates {
    Field,
    Ship,
    Hit,
    Miss,
    BorderHit = 7,
    Border = 8
};
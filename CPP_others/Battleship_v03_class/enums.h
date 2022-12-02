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

enum Ship {

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

enum ConsoleColor{
    DeepCyan = 3,
    DarkRed = 4,
    NormalWhite = 7,
    Grey = 8,
    Blue = 9,
    Green = 10,
    Red = 12,
    Yellow = 14,
};

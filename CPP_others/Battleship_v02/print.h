#ifndef PRINT_H
#define PRINT_H

#include <string>
#include <vector>
#include <array>
#include <map>
#include "enums.h"

void printUserField(std::array<std::array<int, 10>, 10> const&);
void printFields(std::array<std::array<int, 10>, 10> const&, std::array<std::array<int, 10>, 10> const&, ShipView);
void printUpdateMessage(std::map<std::string, std::vector<std::pair<int, int>>>, std::map<std::string, std::vector<std::pair<int, int>>>, std::string, std::string, std::string, std::string);
void printCongrats(Player);
void startMessage(std::string);
void printWarning(Warning);
void printMoveTable(std::vector<std::string> const&);
void printMap(std::map<std::string, std::vector<std::pair<int, int>>> const&);


#endif /* PRINT_H */
#include <iostream>
#include <array>
#include <vector>

int main(){

    srand(static_cast<unsigned int>(time(0)));
    int x = rand() % 3;
    std::cout << "x = " << x << "\n";
    std::array<std::pair<int, int>, 4> rnd_dir = {{{1,0}, {-1,0}, {0,1}, {0,-1}}};

    std::cout << "rnd_dir[1].first = " << rnd_dir[x].first << "\n";
    std::cout << "rnd_dir[1].second = " << rnd_dir[x].second << "\n";


}
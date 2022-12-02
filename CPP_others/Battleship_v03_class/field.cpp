#include <iostream>
#include <array>


class Field {

private:
    std::array<std::array<int, 10>, 10> field_user; //store main field

public:
    void set(){
        field_user.fill({ 0, 0 });
    }
    
    void print(){}
};
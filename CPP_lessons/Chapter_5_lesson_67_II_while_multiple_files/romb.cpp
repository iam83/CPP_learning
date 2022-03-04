//printRomb() function

#include <iostream>

void printRomb(int length){

    //TOP
    //// Цикл с 1 до length
    int outer_top = 1;
    while (outer_top <= length)
    {
        //top right
        int inner = length;
        // Числа в рядах появляются в порядке убывания, поэтому цикл начинаем с 5 и до 1
        while (inner >= 2)
        {
            // Первое число в любом ряде совпадает с номером этого ряда,
            // поэтому числа должны выводиться только если <= номера ряда (в противном случае, выводится пробел)
            if (inner <= outer_top) 
                std::cout << inner << " ";
            else{
                if (inner >= 10) std::cout << " "; //if length more than 10 add extra space to keep it all aligned
                std::cout << "  "; // вставляем дополнительные пробелы
            }
            --inner;
        }
        
        //top left
        while (inner <= length)
        {
            if (inner <= outer_top)
                std::cout << inner << " ";
            else{
                if (inner >= 10) std::cout << " ";
                std::cout << "  ";
            }
            ++inner;
        }
        std::cout << "\n"; // Этот ряд вывели, переходим к следующему
        ++outer_top;
        
    }
    
    //BOTTOM
    int outer_bottom = length - 1;
    while (outer_bottom >= 1){
        
        //bottom left
        int inner = length;
        while (inner >= 2){
            
            if (inner <= outer_bottom)
                std::cout << inner << " ";
            else{
                if (inner >= 10) std::cout << " ";
                std::cout << "  ";
            }
            --inner;
        }
        //bottom right
        while (inner <= length){
            
            if (inner <= outer_bottom)
                std::cout << inner << " ";
            else{
                if (inner >= 10) std::cout << " ";
                std::cout << "  ";
            }
            ++inner;
        }
        std::cout << "\n";
        --outer_bottom;
    }
}

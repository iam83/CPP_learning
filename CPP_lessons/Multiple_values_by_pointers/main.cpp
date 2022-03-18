#include <iostream>

void getMinMax(int numbers[], int size, int* min, int* max){
    for (int i=1; i < size; i++){
        if (numbers[i] < *min)
            *min = numbers[i];

        if (numbers[i] > *max)
            *max = numbers[i];
    }    
}

int main(){

    system ("clear");
    
    int numbers[5] = {3,6,2,8,10};
    int min = numbers[0];
    int max = numbers[0];

    getMinMax(numbers, 5, &min, &max);
    std::cout << "min " << min << std::endl;
    std::cout << "max " << max << std::endl;


    return 0;
}
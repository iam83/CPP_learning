#include <iostream>


void getMinMax(int numbers[], int size, int* minPtr, int* maxPtr){
    for (int i=1; i < size; i++){
        if (numbers[i] < *minPtr) //using dereference of address of &min
            *minPtr = numbers[i];

        if (numbers[i] > *maxPtr)
            *maxPtr = numbers[i];
    }    
}

int main(){

    //system ("clear"); // clear console on macos
    
    int numbers[5] = {3,6,2,8,10};
    int min = numbers[0];
    int max = numbers[0];

    //passing addresses of min and max variable instead of creating a new copies
    getMinMax(numbers, 5, &min, &max); 

    std::cout << "min " << min << std::endl;
    std::cout << "max " << max << std::endl;


    return 0;
}
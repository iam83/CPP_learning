#include <iostream>
#include "constants.h"

using namespace std;

double getHeight(){
    cout << "Enter the initial height of the tower in meters: ";
    double height;
    cin >> height;
    return height;
}

double calcDistFallen(double height, int time){
    return height - (myConstants::gravity * (time*time)/2);
}

void printResult(double height, int time){
    if (height > 0.0)
        cout << "At " << time <<  " seconds, the ball is at height: "
             << height << endl;
    else
        cout << "At " << time << " seconds, the ball is on the ground.\n";
}

void calcAndPrintResult(double height, int time){
    double result = calcDistFallen(height, time);
    printResult(result, time);
}

int main(){

    double height = getHeight();
    calcAndPrintResult(height, 0);
    calcAndPrintResult(height, 1);
    calcAndPrintResult(height, 2);
    calcAndPrintResult(height, 3);
    calcAndPrintResult(height, 4);
    calcAndPrintResult(height, 5);
    return 0;
}

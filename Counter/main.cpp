#include <iostream>

// 8285 8283 11694

const float t1_tarif = 10.23f;
const float t2_tarif = 3.71;
const float t3_tarif = 7.16;   
    
const int t1_prev = 8239;
const int t2_prev = 8260;
const int t3_prev = 11617;

struct Counter{
  
  
  int t1_cur, t2_cur, t3_cur;
  
  void Show(){
    
    float _t1 = (t1_cur - t1_prev) * t1_tarif;
    float _t2 = (t2_cur - t2_prev) * t2_tarif;
    float _t3 = (t3_cur - t3_prev) * t3_tarif;
    
    std::cout << "T1: " << _t1 << std::endl;
    std::cout << "T2: " << _t2 << std::endl;
    std::cout << "T3: " << _t3 << std::endl;
    
    std::cout << "Total sum: " << _t1 + _t2 + _t3 << std::endl;
    
  }
  
};

int main() {

    Counter total_sum;
    
    std::cout << "Enter T1, T2, T3: ";
    std::cin >> total_sum.t1_cur >> total_sum.t2_cur >> total_sum.t3_cur;
    
    total_sum.Show();
    
    return 0;
}
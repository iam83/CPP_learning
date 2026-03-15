#include <iostream>

// 8285 8283 11694

const float t1_tarif = 10.23f;
const float t2_tarif = 3.71;
const float t3_tarif = 7.16;

int main() {

  int t1_cur, t2_cur, t3_cur;
  int t1_prev{8239}, t2_prev{8260}, t3_prev{11617};
  std::cout << "Enter T1 T2 T3 :> ";
  std::cin >> t1_cur >> t2_cur >> t3_cur;

  float _t1 = (t1_cur - t1_prev) * t1_tarif;
  float _t2 = (t2_cur - t2_prev) * t2_tarif;
  float _t3 = (t3_cur - t3_prev) * t3_tarif;

  std::cout << "Total sum: " << _t1 + _t2 + _t3 << std::endl;

  return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


// 8285 8283 11694

const float t1_tarif = 10.23f;
const float t2_tarif = 3.71;
const float t3_tarif = 7.16;

struct Counter{
  int t1_cur, t2_cur, t3_cur;
};

void total_sum(Counter &counter, const std::vector<int> &prev){

    float _t1 = (counter.t1_cur - prev[0]) * t1_tarif;
    float _t2 = (counter.t2_cur - prev[1]) * t2_tarif;
    float _t3 = (counter.t3_cur - prev[2]) * t3_tarif;
    
    std::cout << "T1: " << _t1 << std::endl;
    std::cout << "T2: " << _t2 << std::endl;
    std::cout << "T3: " << _t3 << std::endl;
    
    std::cout << "Total sum: " << _t1 + _t2 + _t3 << std::endl;
}

int main() {
  
  //system("clear");

  std::string line;
  std::ifstream myfile ("counter.txt");
  std::vector <int> numbers;

  if (myfile.is_open())
  {
    while (getline (myfile, line)){
      numbers.push_back(stoi(line));
    }
    myfile.close();
  }

  else{
    std::cout << "Unable to open file";
    exit(-1);
  }
 
  Counter total_sum;
  
  std::cout << "Enter T1, T2, T3: ";
  std::cin >> total_sum.t1_cur >> total_sum.t2_cur >> total_sum.t3_cur;

  
  
  return 0;
}
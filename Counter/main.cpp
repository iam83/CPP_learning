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

void calc_total(const Counter counter, std::vector<int> &prev_numbers){
    float _t1 = (counter.t1_cur - prev_numbers[0]) * t1_tarif;
    float _t2 = (counter.t2_cur - prev_numbers[1]) * t2_tarif;
    float _t3 = (counter.t3_cur - prev_numbers[2]) * t3_tarif;
    
    std::cout << std::endl;
    std::cout << "T1: " << counter.t1_cur << " = " << _t1 << std::endl;
    std::cout << "T2: " << counter.t2_cur << " = " << _t2 << std::endl;
    std::cout << "T3: " << counter.t3_cur << " = " << _t3 << std::endl;
    
    std::cout << std::endl;
    std::cout << "Total sum: " << _t1 + _t2 + _t3 << std::endl;

    prev_numbers[0] = counter.t1_cur;
    prev_numbers[1] = counter.t2_cur;
    prev_numbers[2] = counter.t3_cur;
}

void writeToFile(const Counter total_sum){

  std::ofstream myfile("counter.txt");
  if (myfile.is_open())
  {
    myfile << total_sum.t1_cur << "\n" << total_sum.t2_cur << "\n"<< total_sum.t3_cur;
    myfile.close();
    std::cout << "Saved.";
  }
  else{
    std::cout << "Unable to open file";
    exit(-1);
  }
}

int main() {

  std::string line;
  std::ifstream myfile ("temp.txt");
  std::vector <int> prev_numbers;

  if (myfile.is_open())
  {
    while (getline (myfile, line)){
      prev_numbers.push_back(stoi(line));
    }
    myfile.close();
  }

  else{
    std::cout << "Unable to open file";
    exit(-1);
  }
 
  Counter total_sum;

  std::cout << std::endl;
  std::cout << "T1 before " << prev_numbers[0] << std::endl;
  std::cout << "T2 before " << prev_numbers[1] << std::endl;
  std::cout << "T1 before " << prev_numbers[2] << std::endl;

  std::cout << std::endl;
  std::cout << "Enter T1 T2 T3 :> ";
  std::cin >> total_sum.t1_cur >> total_sum.t2_cur >> total_sum.t3_cur;

  calc_total(total_sum, prev_numbers);
  
  writeToFile(total_sum);

  return 0;
}
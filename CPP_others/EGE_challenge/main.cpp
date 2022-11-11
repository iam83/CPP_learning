#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main () {
    
  std::string line;
  std::ifstream myfile ("_27989_B.txt");
  std::vector <int> numbers;

  if (myfile.is_open())
  {
    while (getline (myfile,line)){
      numbers.push_back(stoi(line));
    }
    myfile.close();
  }
  else{
    std::cout << "Unable to open file";
    exit(-1);
  }
  std::cout << numbers[0] << std::endl;
  numbers.erase(numbers.begin());
  int count = 0;

  for (int i = 0; i < numbers.size(); ++i){
    for (int j = i+1; j < numbers.size(); ++j){
      int result =  (numbers[i] * numbers[j]) % 26;
      if (result == 0){
        count++;
      }
    }
  }
  std::cout << "Found " << count << " pairs." << std::endl;
  
  return 0;
}
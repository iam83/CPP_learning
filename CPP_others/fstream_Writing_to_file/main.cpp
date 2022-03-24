// writing on a text file
#include <iostream>
#include <fstream>


int main () {

  std::ofstream myfile ("text.txt");

  if (myfile.is_open())
  {
    myfile << "This is a line.\n";
    myfile << "This is another line.\n";
    myfile.close();
  }
  else std::cout << "Unable to open file";

  return 0;
}
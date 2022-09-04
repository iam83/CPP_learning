#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#ifdef _WIN32
    #define CLS "cls"
#else
    #define CLS "clear"
#endif

void printVector(std::vector<std::string> const &words){
    int count {0};
    for (auto const &word : words){
        std::cout << word;
        ++count;
        std::cout << std::left << std::setw(15); //using for formatting output
            if (count % 5 == 0) std::cout << std::endl; //output in columns
    }
    std::cout << std::endl << std::endl;
}

void printCertainWords(std::vector<std::string> const &words, const char &first_letter, std::vector<std::string> *temp_words){
    int count{0};
    for (auto const &word : words){
        if(word[0] == first_letter){
            std::cout << word;
            std::cout << std::left << std::setw(15); //using for formatting output
            if (count % 5 == 0) std::cout << std::endl; //output in columns
            temp_words->push_back(word);
            ++count;
        }
    }
    std::cout << std::endl;
    std::cout << std::setw(0) << "Found " << count << " words beginning with " << first_letter << std::endl;
}

void printVectorSize(std::vector<std::string> const &words){
    std::cout << std::endl << "Size of vector: " << words.size() << std::endl;
}

bool compareMin(std::string const &i, std::string const &j) {
    return (i.size() < j.size()); 
}

bool compareMax(std::string const &i, std::string const &j) {
    return (i.size() > j.size()); 
}

std::string getTheShortestWord(std::vector<std::string> const &words){
    std::string min = (*std::min_element(words.begin(), words.end(), compareMin));
    return min;
}

std::string getTheLongestestWord(std::vector<std::string> const &words){
    std::string min = (*std::min_element(words.begin(), words.end(), compareMax));
    return min;
}

void findCertainWord(std::vector<std::string> const &words, std::vector<std::string> &temp_words){

    std::string search_word;
    char first_letter = ' ';
    std::cout << "Type the word you want to find: ";
    std::cin >> search_word;
    first_letter = search_word[0];
    std::cout << "First letter is: " << first_letter << std::endl;

    printCertainWords(words, first_letter, &temp_words);

    if (std::find(words.begin(), words.end(), search_word) != words.end()){
        std::cout << "Found. The word " << search_word << " is in the list." << std::endl;
    }else{
        std::cout << "Nothing found." << std::endl;
    }

}

int main (){

    system(CLS);

    std::ifstream file("words.txt");
    std::vector<std::string> words, temp_words;
    std::string temp, search_word;
    
    int choice{0};

    if(file.is_open()){
        while(getline (file, temp))
            words.push_back(temp);
    }else{
        std::cout << "File not found" << std::endl;
        return -1;
    }

    std::cout << "Choose what you want to do:\n";
    std::cout << "1. Print words list.\n";
    std::cout << "2. Find a certain word.\n";

    std::cin >> choice;

    switch (choice){
        case 1:
            printVector(words);
            break;
        case 2:
            findCertainWord(words, temp_words);
            break;
    }

    if (temp_words.size() != 0){
        std::cout << std::endl;
        std::cout << "The shortest word is: " << getTheShortestWord(temp_words) << std::endl;
        std::cout << "The longest word is: " << getTheLongestestWord(temp_words) << std::endl;
        std::cout << std::endl;
    }

    file.close();
    return 0;
}
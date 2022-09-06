#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#ifdef _WIN32
#define CLS "cls"
#include <iomanip>

#else
#define CLS "clear"
#endif



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

void printMinMax(std::vector<std::string> *temp_words){

    if (temp_words->size() != 0){
        std::cout << std::endl;
        std::cout << "The shortest word is: " << getTheShortestWord(*(temp_words)) << std::endl;
        std::cout << "The longest word is: " << getTheLongestestWord(*(temp_words)) << std::endl;
        std::cout << std::endl;
    }

}

void printVector(std::vector<std::string> const &words){

    int count {0};
    for (auto const &word : words){

        std::cout << std::left << std::setw(15);  //using for formatting output
        std::cout << word;
        ++count;
        
            if (count % 5 == 0 && count != 0) std::cout << std::endl; //output in columns
    }
    std::cout << std::endl << std::endl;
    std::cout << count << " words is listed." << std::endl;
    std::cout << std::endl;
}

void printCertainWords(std::vector<std::string> const &words, std::string const &search_word){

    std::vector<std::string> temp_words;

    char first_letter = ' ';

    if (search_word.empty()){
        std::cout << "Type the letter you want to find words with: ";
        std::cin >> first_letter;
    }else{
        first_letter = search_word[0];
    }

    int count{0};

    std::cout << std::endl;

    for (auto const &word : words){
        if(word[0] == first_letter){

            std::cout << std::left << std::setw(15); //using for formatting output
            std::cout << word;
            temp_words.push_back(word);
            if (count % 5 == 0 && count != 0) std::cout << std::endl; //output in columns
                ++count;
        }
    }

    std::cout << std::endl << std::endl;
    std::cout << std::setw(0) << "Found " << count << " words beginning with " << "\"" << first_letter << "\"" << ".\n" << std::endl;
    printMinMax(&temp_words);

}

void findCertainWord(std::vector<std::string> const &words){
    
    std::string search_word;
	std::cout << "Type the word you want to find: ";
	std::cin >> search_word;

    if (std::find(words.begin(), words.end(), search_word) != words.end()){
        std::cout << "\nFound. The word \"" << search_word << "\" is in the list.\n" << std::endl;
    }else{
        std::cout << "Nothing found.\n" << std::endl;

        //if found nothing print all the words beginning with the first letter of the search word
        std::cout << "But there are other words beginning with " << search_word[0] << ".\n";
        printCertainWords(words, search_word);
    }
    
}

bool playAgain(){

	char exit;

	do{
		std::cout << "Would you like to run again (y/n)?: ";
		std::cin >> exit;

        if (exit == 'y'){
			return true;
			break;
		}else if(exit == 'n'){
			std::cout << "Thank you. Good buy." << std::endl;
			return false;
			break;
		}else{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
    		std::cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
		}
	}while(1);

	std::cout << std::endl;
}

int main (){

    system(CLS);

    std::ifstream file("words.txt");
    std::vector<std::string> words, temp_words;
    std::string temp, search_word;
    
    int choice{0};

    do {
        if(file.is_open()){
            while(getline (file, temp))
                words.push_back(temp);
        }else{
            std::cout << "File not found" << std::endl;
            return -1;
        }

        std::cout << "Choose what you want to do:\n\n";
        std::cout << "1. Print words list.\n";
        std::cout << "2. Find a certain word.\n";
        std::cout << "3. List words beginning with specific letter.\n\n";
        std::cout << "Your choice:> ";

        std::cin >> choice;

        switch (choice){
            case 1:
                printVector(words);
                printMinMax(&words);
                break;
            case 2:
                findCertainWord(words);
                break;
            case 3:
                printCertainWords(words, "");
                break;
        }

    } while(playAgain());

        file.close();

    return 0;
}
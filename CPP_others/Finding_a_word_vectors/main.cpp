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
        std::cout << "\"" << search_word << "\" is not in the list.\n" << std::endl;

        //if found nothing then print all the words beginning with the first letter of the search word
        std::cout << "But there are other words beginning with " << search_word[0] << ".\n";
        printCertainWords(words, search_word);
    }
    
}

void printMenu(){
    std::cout << "Choose what you want to do:\n\n";
    std::cout << "1. Print words list.\n";
    std::cout << "2. Find a certain word.\n";
    std::cout << "3. List words beginning with specific letter.\n";
    std::cout << "4. Exit\n\n";
    std::cout << "Your choice:> ";
}

//use for correct input
int getChoice(){

	int choice{0};

	do {
		std::cin >> choice;

		if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
            std::cout << "Only numbers please" << std::endl;
            std::cout << "Choose from 1 - 4" << std::endl;
        }
        else
        {
            std::cin.ignore(32767,'\n'); // удаляем лишние значения
 
            	if (choice < 1 || choice > 4){
					std::cout << "Choose from 1 - 4" << std::endl;
					continue;
				}else{
					break;
				}
        }
	} while(1);

	return choice;
}

bool getWordsFromFile(std::vector<std::string> &words){

        std::string temp;
        std::ifstream file("words.txt");
        if(file.is_open()){
            while(getline (file, temp))
                words.push_back(temp);
            file.close();
            return true;
        }else{
            std::cout << "File not found" << std::endl;
            return false;
        }
}

int main (){

    system(CLS);

    std::vector<std::string> words, temp_words;
    std::string search_word;

    if (!getWordsFromFile(words))
        return -1;
    
    printMenu();
    bool exit = true;
    do {
        switch (getChoice()){
            case 1:
                printVector(words);
                printMinMax(&words);
                printMenu();
                break;
            case 2:
                findCertainWord(words);
                printMenu();
                break;
            case 3:
                printCertainWords(words, "");
                printMenu();
                break;
            case 4:
                exit = false;
                break;
        }
    } while(exit);
    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "word_length.h"


// Write a program that runs in two modes depending on whether a command-line argument is provided

// If no command-line argument is given, the program runs in interactive mode
// taking text input from the user and returning N for each input, where N is the
// length of the longest word in the text.

// If a command-line argument is provided, the program treats the first argument as a filename
// and reads the file line by line to perform the same operation.


int main(int argc, char *argv[]) {
    if (argc < 2) {
        // interactive
        std::cout << "Interactive mode! \n";
        std::string line{};
        while (std::getline(std::cin, line)) {
            int length = get_longest_words_length(line);
            std::cout << "Longest = " << length << "\n";
        }
    }
    else {
        std::string file_name{argv[1]};
        //std::cout << "File name is: " << file_name << "\n";
        get_longest_words_length_from_file(file_name);
    }

    return 0;
}
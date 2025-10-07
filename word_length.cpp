#include "word_length.h"
#include <fstream>
#include <iostream>

int get_longest_words_length(std::string line) {
    int longest{};
    int count{};
    for (char c: line) {
        if (c == ' ') {
            if (count > longest) {
                longest = count;
            }
            count = 0;
        }
        else {
            count ++;
        }
    }

    if (count > longest) {
        longest = count;
    }

    return longest;
}

void get_longest_words_lengt_from_file(std::string file_name) {
    std::ifstream in(file_name);
        if (!in.is_open()) {
            std::cout << "File couldn't be opened \n";
        }
        else {
            std::string line{};
            while(std::getline(in, line)) {
                std::cout << get_longest_words_length(line) << "\n";
            }
        }
        in.close();
}
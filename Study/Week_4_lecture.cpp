#include <iostream>
#include <string>
#include <cctype>



std::string remove_tags(std::string input) {
    std::string result{};
    bool inside_tag = false;
    for (char ch : input) {
        if (ch == '<') {
            inside_tag = true;
            continue;
        }
        if (ch == '>') {
            inside_tag = false;
            continue;
        }
        if (inside_tag) {
            continue;
        }
        result += ch;
    }

    return result;
}

std::string remove_tags_with_functions(std::string input) {
    while (true) {
        size_t start_tag_index{input.find("<")};
        if (start_tag_index == std::string::npos) {
            break;
        }
        size_t end_tag_index{input.find(">")};
        if (end_tag_index == std::string::npos) {
            break;
        }
        //std::cout << "Start: " << start_tag_index << " End: " << end_tag_index << "\n";
    
        input.replace(start_tag_index, end_tag_index - start_tag_index + 1, "");
    }


    return input;
}

// remove tags from html
int main() {
    std::string input = "<body>\n<h>This is a header.</h>\n<p>This is some text within a HTML paragraph</p>\n</body>\n";

    // solve without using string utility functions such as substr, find or replace
    // solve using above functions
    // add a debug option

    //std::string result = remove_tags(input);
    
    //std::cout << result << "\n";
    std::cout << remove_tags_with_functions(input) << "\n";


    return 0;

}


// Practice Problem 2:

// Imagine shopping lists in the following format:

// Apples: $3.29
// Chicken Breast (1lb): $5.99
// Basmati Rice (5lb bag) : $12.50
// Eggs (dozen): $2.99

// Write a program that returns the total grocery cost



// Write a program that takes a string of text as input and
// returns a string where the first letter of every sentence
// is uppercase, and all other letters are lowercase

// Input:
// I AM a programming Student. I study computer scienCe

// Output: 
// I am a programming student. I study conputer science. 



// Write a program that performs simple sentiment analysis on a text input. The program should look for the following good and bad words in the input, then decide whether the text has a positive or negative vibe by comparing how many good vs. bad words appear. 

// std::vector<std::string> good_words {
//     "happy", "love", etc.
// };

// std::vector<std::string> bad_words {
//     "sad", "hate", etc.
// };


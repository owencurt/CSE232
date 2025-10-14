#include <iostream>
#include <string>

// Test if 'word' is a full entry in 'word_list' beginning as index 'pos'.
bool AtListPosition(std::string word_list, std::string word, size_t pos)
{
    if (pos > word_list.size()) {
        return false;
    }
    if (pos + word.size() > word_list.size()) {
        return false;
    } 
    if (word_list.compare(pos, word.size(), word) != 0) {
        return false;
    }
    if (pos != 0 && word_list[pos - 1] != ',') {
        return false;
    }
    if (pos + word.size() != word_list.size() && word_list[pos + word.size()] != ',') {
        return false;
    }

    return true;
}

// Inputs are:
//   word_list - a string that contains a list of comma-separated words.
//   word - a string that contains to word to search for in the list.
//   pos - an optional size_t containing the position to start the search
//         (start at zero if no pos argument is provided)
// Return:
//   The index where 'word' was found as a full entry in word_list -or-
//   std::string::npos if word is not found
//
// Note, must match FULL word.  So "def" would be matched in "abc,def,ghijk,l" or in
// "def,456,ghi,789,jkl", but NOT in "defeated,indefinitely,redefined"
size_t FindInList(std::string word_list, std::string word, size_t pos=0)
{
    if (word.empty() || pos > word_list.size()) {
        return std::string::npos;
    }

    while (true) {
        size_t word_pos = word_list.find(word, pos);
        if (word_pos == std::string::npos) {
            return std::string::npos;
        }
        if (AtListPosition(word_list, word, word_pos)) {
            return word_pos;
        }
        pos = word_pos + 1;
    } 

}

// Takes two strings and a word list.
// Returns the value of the string found first in the word list.
// Should return "N/A" if neither is in the word list.
std::string GetFirstInList(std::string word_list,
                           std::string word1,
                           std::string word2)
{
    size_t pos1 = FindInList(word_list, word1);
    size_t pos2 = FindInList(word_list, word2);

    if (pos1 == std::string::npos && pos2 == std::string::npos) {
        return "N/A";
    }

    if (pos1 == std::string::npos) {
        return word2;
    }

    if (pos2 == std::string::npos) {
        return word1;
    }

    if (pos1 > pos2) {
        return word2;
    }
    else {
        return word1;
    }
}

// Takes a word_list and a word and counts the number of times that word
// is found in the list.
size_t CountInList(std::string word_list, std::string word) 
{
    size_t count = 0;
    size_t pos = 0;

    while (true) {
        size_t found = FindInList(word_list, word, pos);
        if (found == std::string::npos) {
            break;
        }
        count ++;
        pos = found + word.size();
    }
    return count;
}


// As inputs from std::cin, take in two words.  Then take in a series of comma-separated word_lists.
// For each word list provided, output which of the two words comes first, or "N/A" if neither is in
// the list.  Then output (on the same line) a count of how many times each word appeared.
//
// Example Input:
//   Kansas
//   Virginia
//   Virginia,Wyoming,Vermont
//   NewMexico,Kansas,Alabama,Virginia,NewYork,WestVirginia,Arkansas,Virginia,Utah,Virginia
//   Alaska
//
// Example Output:
//   Virginia 0 1
//   Kansas 1 3
//   N/A 0 0
//
// Note: The second output line has Virginia listed only 3 times, ignoring "WestVirginia"

int main()
{
    std::string word1, word2;
    std::getline(std::cin, word1);
    std::getline(std::cin, word2);

    std::string word_list;
    while (std::getline(std::cin, word_list)) {
        std::string first = GetFirstInList(word_list, word1, word2);
        size_t c1 = CountInList(word_list, word1);
        size_t c2 = CountInList(word_list, word2);

        std::cout << first << " " << c1 << " " << c2 << "\n";
    }
    return 0;
}

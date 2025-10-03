// WRITE YOUR CODE HERE
#include <iostream>
#include <string>
#include <vector>

int NumberOfCharactersOverlap(std::string str1, std::string str2) {
    int maxLen = std::min(str1.size(), str2.size());

    for (int len = maxLen; len > 0; --len) {
        bool match = true;
        for (int j = 0; j < len; ++j) {
            if (str1.at(str1.size() - len + j) != str2.at(j)) {
                match = false;
                break;
            }
        }
        if (match) {
            return len;
        }
    }

    return 0;
}

std::string CombineWords(std::string str1, std::string str2, int count) {
    if (count != 0) {
        std::string combined = str1.substr(0, str1.size() - count) + str2;
        return combined;
    }
    return str1 +  " " + str2;
}

std::vector<std::string> SplitWords(const std::string& input) {
  std::vector<std::string> words;
  std::string word;

  for (char c : input) {
    if (c == ' ') {
        if (!word.empty()) {
            words.push_back(word);
            word.clear();
        }
    } else {
        word += c;
    }
  }
  if (!word.empty()) {
      words.push_back(word);
  }

  return words;
}

int main(){
  std::string line{};
  while (std::getline(std::cin, line)) {
    std::vector<std::string> words = SplitWords(line);

    std::string result = words[0];
    for (size_t i = 1; i < words.size(); ++i) {
        int count = NumberOfCharactersOverlap(result, words[i]);
        result = CombineWords(result, words[i], count);
  }

  std::cout << result << "\n";
  }

  
  return 0;
}
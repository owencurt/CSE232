// WRITE YOUR CODE HERE
#include <iostream>
#include <string>

int NumberOfCharactersOverlap(std::string str1, std::string str2) {
  int count{};
  for (int i = 0; i < str1.size(); ++i) {
    if (str1.at(i) == str2.at(count)) {
      count += 1;
    }
  }
  return count;
}

std::string CombineWords(std::string str1, std::string str2, int count) {
    if (count != 0) {
        std::string combined = str1.substr(0, str1.size() - count) + str2;
        return combined;
    }
    return str1 +  " " + str2;
}

int main(){
  std::string str1 = "dog";
  std::string str2 = "cheese";
  int count{};
  count = NumberOfCharactersOverlap(str1, str2);

  std::string result{};
  result = CombineWords(str1, str2, count);

  std::cout << result << "\n";
  return 0;
}
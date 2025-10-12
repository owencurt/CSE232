// Given a vector of ints {4, 1, 4, 2, 1}, remove duplicates and keep result in order: {4, 1, 2}

// #include <iostream>
// #include <vector>

// std::vector<int> RemoveDuplicates(std::vector<int> v) {
//     for (size_t i = 0; i < v.size(); i++) {
//         for (size_t j = i + 1; j < v.size();) {
//             if (v.at(j) == v.at(i)) {
//                 v.erase(v.begin() + j);
//             }
//             else {
//                 ++j;
//             }
//         }
//     }

//     return v;
// }

// int main() {
//     std::vector<int> v = {4, 1, 4, 2, 1};
//     std::vector<int> result = RemoveDuplicates(v);

//    for (auto x : result) {
//     std::cout << x << " ";
//     }
//     std::cout << "\n";

//     return 0;
// }



// Given a string like 10, return an incremented version 11. 9 --> 10, etc. You cannot use stoi or other related conversion types (stod, etc.)

#include <iostream>
#include <string>

std::string IncrementString(std::string input) {
    bool carry = true;
    for (int i = input.size() - 1; i >= 0 && carry; --i) {
        if (input.at(i) == '9') {
            input.at(i) = '0';
        }
        else {
            input.at(i) += 1;
            carry = false;
        }
    }
    if (carry) {
        input.insert(input.begin(), '1');
    }
    
    return input;
}

int main() {

    std::string input = "9999";

    std::string result = IncrementString(input);
    std::cout << result << "\n";


    return 0;
}
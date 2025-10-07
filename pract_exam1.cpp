// Given a vector of ints {4, 1, 4, 2, 1}, remove duplicates and keep result in order: {4, 1, 2}

// #include <vector>
// #include <iostream>

// std::vector<int> RemoveDups(std::vector<int> input) {

//     for (size_t i = 0; i < input.size(); i++) {
//         for (size_t j = i + 1; j < input.size(); ) {
//             if (input.at(j) == input.at(i)) {
//                 input.erase(input.begin() + j);
//             }
//             else {
//                 j++;
//             }
//         }
//     }

//     return input;
// }


// int main() {

//     std::vector<int> v = {4, 1, 4, 2, 1};
//     std::vector<int> result = RemoveDups(v);
//     std::vector<int> expected = {4, 1, 2};

//     if (result == expected) {
//         std::cout << 1 << "\n";
//     }

//     return 0;
// }


// Given a string like 10, return an incremented version 11. 9 --> 10, etc. You cannot use stoi or other related conversion types (stod, etc.)

//Solve: access final character, increment by 1

#include <iostream>

std::string StrintIncrement(std::string input) {
    int carry = 0;
    size_t last_idx = input.size() - 1;

    if (input.at(last_idx) != '9') {
        ++input.at(last_idx);
    }
    else if (input.at(last_idx) == '9') {
        carry = 1;
        input.at(last_idx) = '0';
    }

    int i = last_idx - 1;
    while (i >= 0) {
        if (carry > 0 && input.at(i) != '9') {
            ++input.at(i);
            carry = 0;
        }
        else if (carry > 0 && input.at(i) == '9') {
            input.at(i) = '0';
        }
        --i;
    }
    

    return input;
}

int main() {
    std::string result = "123";
    std::cout << static_cast<char>(result.at(2) + 1) << std::endl;


}
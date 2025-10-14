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

// #include <iostream>
// #include <string>

// std::string IncrementString(std::string input) {
//     bool carry = true;
//     for (int i = input.size() - 1; i >= 0 && carry; --i) {
//         if (input.at(i) == '9') {
//             input.at(i) = '0';
//         }
//         else {
//             input.at(i) += 1;
//             carry = false;
//         }
//     }
//     if (carry) {
//         input.insert(input.begin(), '1');
//     }
    
//     return input;
// }

// int main() {

//     std::string input = "9999";

//     std::string result = IncrementString(input);
//     std::cout << result << "\n";


//     return 0;
// }


// Erase all occurrences of a value while iterating safely.
// Input: {3,2,3,4,3,5}, value 3 → {2,4,5}

// #include <iostream>
// #include <vector>

// std::vector<int> EraseOccurrences(std::vector<int> input, int num_to_remove) {
//     for (size_t i = 0; i < input.size();) {
//         if (input.at(i) == num_to_remove) {
//             input.erase(input.begin() + i);
//         }
//         else {
//             ++i;
//         }
//     }

//     return input;
// }

// int main() {
//     std::vector<int> input = {3,2,3,4,3,5};
//     int num_to_remove = 3;

//     std::vector<int> result = EraseOccurrences(input, num_to_remove);
 
//     for (auto x : result) {
//         std::cout << x << " ";
//     }
//     std::cout << "\n";

//     return 0;
// }


// Rotate left by k (in-place, O(1) extra).
// {1,2,3,4,5}, k=2 → {3,4,5,1,2}

// #include <iostream>
// #include <vector>

// std::vector<int> RotateVector(std::vector<int> input, int k) {
//     for (int i = 0; i < k; i++) {
//         input.push_back(input.at(0));
//         input.erase(input.begin());
//     }

//     return input;
// }

// int main() {
//     std::vector<int> input = {1, 2, 3, 4, 5};
//     int k = 2;

//     std::vector<int> result = RotateVector(input, k);

//     for (auto x : result) {
//         std::cout << x << " ";
//     }
//     std::cout << "\n";

// }



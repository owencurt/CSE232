#include <iostream>

int main() {
    int value;
    std::cout << "Enter a number: ";
    std::cin >> value;

    int result = value / 2.0;

    std::cout << result << " is half of the number you inputted. " << std::endl;
    return 0;
}

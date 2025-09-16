#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>

int main() {
    srand(time(0));
    int target_number{};
    int guess{};
    target_number = rand() % 101;

    std::cout << target_number << "\n";
    
    
    while (true) {
        std::cout << "Enter Your Guess: ";
        std::cin >> guess;

        if (guess > target_number) {
            std::cout << "The number is lower than your guess\n ";
            continue;
        }
        else if (guess < target_number) {
            std::cout << "The number is higher than your guess\n ";
            continue;
        }
        else {
            std::cout << "You guessed it correct!\n ";
            break;
        }
    }
    
    return 0;
}
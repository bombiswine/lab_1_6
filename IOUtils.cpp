#include "D:\University\PROGRAMS\c++\IOUtils.h"

int getInt() {
    bool inputCorrect{ };
    int  userInput{ };
    do {
        std::cin >> userInput;
        inputCorrect = std::cin.good();
        if (!inputCorrect) {
            std::cerr << "\tError: Input value is not an integer number\n\tRepeat input: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!inputCorrect);

    std::cin.clear();

    return userInput;
}

int getNatural() {
    bool isPositive{ };
    int  userInput{ };
    do {
        userInput = getInt();
        isPositive = (userInput >= 0) ? true : false;
        if (!isPositive) {
            std::cout << "\tError: Input value is not a positive integer\n\tRepeat input: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!isPositive);

    std::cin.clear();

    return userInput;
}

int getEvenNatural() {
    bool isEven{ };
    int  userInput{ };
    do {
        userInput = getNatural();
        isEven = (userInput % 2 == 0) ? true : false;
        if (!isEven) {
            std::cerr << "\tError: Entered value is not an even positive integer\n\tRepeat input: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!isEven);

    std::cin.clear();

    return userInput;
}
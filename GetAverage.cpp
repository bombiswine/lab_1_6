#include "GetAverage.h"

double CalculateAverageLength(std::ifstream& fin)
{
    if (!fin.is_open()) {
        std::cerr << "\tError: File cannot be opened" << std::endl;
        return -1.0;
    }
    int  totalChainsLength{ };
    int  wsChainsAmount{ };
    char currentCharecter{ };
    int  wsAmount{ };

    while (!fin.eof()) {
        currentCharecter = fin.get();
        if (currentCharecter == ' ') {
            wsAmount++;
        } else {
            if (wsAmount > 0 && wsAmount % 2 == 0) {
                wsChainsAmount++;
                totalChainsLength += wsAmount;
            } 
            wsAmount = 0;
        }
    }

    if (totalChainsLength > 0) {
        return totalChainsLength / static_cast<double>(wsChainsAmount);
    } else {
        return 0.0;
    }
}
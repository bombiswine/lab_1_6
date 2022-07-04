#pragma once
#include <fstream>

class EvenWSChain {
private:
    int length_;
public:
    EvenWSChain();
    EvenWSChain(int);
    void SelfPrint(std::ofstream&) const;
    void Increase(int);
};


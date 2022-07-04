#pragma once
#include <algorithm>
#include <fstream>
#include <random>
#include <vector>

class DelimiteringChain {
private:
    int length_;
    std::vector<char> content_;
    std::mt19937 randomGenerator_;
    std::uniform_int_distribution<int> range_;
public:
    DelimiteringChain();
    DelimiteringChain(int);
    bool canContainOddWSChain() const;
    void SelfPrint(std::ofstream& fout) const;
    void InsertOddWSChain();
    void Increase(int);
    ~DelimiteringChain();
};


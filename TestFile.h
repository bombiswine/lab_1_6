#ifndef _TESTFILE_H_
#define _TESTFILE_H_

#include <algorithm>
#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <regex>
#include <vector>
#include "EvenWSChain.h"
#include "DelimiteringChain.h"
#include "D:\University\PROGRAMS\c++\IOUtils.h"
#include "GetAverage.h"

class TestFile {
private:
    std::string name_;
    int length_;
    int totalEvenWSChainsLength_;
    std::vector<EvenWSChain> evenWSChains_;
    std::vector<DelimiteringChain> delimiters_;
    int  oddWSChainsNumber_;
    bool beginIsWS_;
    bool endIsWS_;
    std::mt19937 randomGenerator_;
    std::string setFileName();
    int  getDelimitersAmount() const;
    void setFileSplitting();
    void writeToFile() const;

public:
    TestFile();
    std::string GetFileName() const;
    void SaveTestingResult(const double, const double, const bool) const;
    void ConductTesting() const;
};

#endif

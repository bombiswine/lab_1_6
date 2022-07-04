#include "DelimiteringChain.h"

DelimiteringChain::DelimiteringChain()
{   
    std::random_device device;
    randomGenerator_.seed(device());
    length_ = 1;
    range_ = std::uniform_int_distribution<int> (0x22, 0x7e);
    content_.push_back(static_cast<char>(range_(randomGenerator_)));
}

DelimiteringChain::DelimiteringChain(int length)
{
    length_ = length;
    if (length > 0) {
        content_.resize(length);
        for (char& character : content_) {
            character = static_cast<char>(range_(randomGenerator_));
        }
    } else {
        content_.clear();
    }
}

bool DelimiteringChain::canContainOddWSChain() const
{
    return length_ > 2;
}

void DelimiteringChain::SelfPrint(std::ofstream& fout) const
{
    for (const char& character : content_) {
        fout.put(character);
    }
}

void DelimiteringChain::InsertOddWSChain()
{
    srand(time(nullptr));
    int oddWSChainLength{ 1 };
    std::uniform_int_distribution<int> oddChainLengthsRange;
    if (length_ % 2 == 0) {
        oddChainLengthsRange = std::uniform_int_distribution<int> (0, length_ / 2 - 2);
    } else {
        oddChainLengthsRange = std::uniform_int_distribution<int> (0, (length_ - 3) / 2);
    }
    oddWSChainLength += 2 * oddChainLengthsRange(randomGenerator_);

    std::uniform_int_distribution<int> oddChainBeginingRange(1, length_ - 1 - oddWSChainLength);
    int oddWSChainBeg{ oddChainBeginingRange(randomGenerator_) };

    for (int i = 0; i < oddWSChainLength; i++) {
        content_.at(oddWSChainBeg + i) =  ' ';
    }
}

void DelimiteringChain::Increase(int addition)
{
    for (int i = 0; i < addition; i++) {
        content_.push_back(static_cast<char>(range_(randomGenerator_)));
    }
    length_ += addition;
}

DelimiteringChain::~DelimiteringChain()
{   
    content_.~vector();
}

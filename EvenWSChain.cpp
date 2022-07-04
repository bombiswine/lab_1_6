#include "EvenWSChain.h"

EvenWSChain::EvenWSChain()
{
    length_ = 2;
}

EvenWSChain::EvenWSChain(int length)
{
    length_ = length;
}

void EvenWSChain::SelfPrint(std::ofstream& fout) const
{
    if (fout.good()) {
        for (int i = 0; i < length_; i++) {
            fout.put(' ');
        }
    } else {
        exit(-1);
    }
}

void EvenWSChain::Increase(int addition)
{
    length_ += addition;
}

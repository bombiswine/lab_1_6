#include "TestFile.h"

TestFile::TestFile()
{
    srand(static_cast<unsigned>(time(nullptr)));
    std::random_device device;
    randomGenerator_.seed(device());

    std::cout << "Enter test file's name (in txt format): ";
    name_ = setFileName();
    std::ofstream file;
    file.open(name_.c_str());

    if (file.is_open()) {
        file.close();
        std::cout << "Enter the amount of even white-spaces chains: ";
        const int evenWSChainsNumber{ getNatural() };
       
        if (evenWSChainsNumber > 0) {
            evenWSChains_.resize(evenWSChainsNumber);
            // even w-s chaines total length scan with check
            bool totalIsValid{ };
            do {
                std::cout << "Enter the even white-spaces chaines total length: ";
                totalEvenWSChainsLength_ = getEvenNatural();
                totalIsValid = totalEvenWSChainsLength_ >= 2 * evenWSChainsNumber;
                if (!totalIsValid) {
                    std::cout << "\tError: Total length of white-spaces chains ";
                    std::cout << "must be not fewer than " << 2 * evenWSChainsNumber;
                    std::cout << std::endl;
                }
            } while (!totalIsValid);

            // file length scan with check
            bool lengthIsValid{ };
            do {
                std::cout << "Enter the file's length: ";
                length_ = getNatural();
                lengthIsValid = length_ >= totalEvenWSChainsLength_ + evenWSChainsNumber - 1;
                if (!lengthIsValid) {
                    std::cout << "\tError: File length must be grater than ";
                    std::cout << totalEvenWSChainsLength_ + evenWSChainsNumber - 1;
                    std::cout << std::endl;
                }
            } while (!lengthIsValid);

            std::uniform_int_distribution<int> boolRange(0, 1);
            beginIsWS_ = static_cast<bool>(boolRange(randomGenerator_));
            endIsWS_ = static_cast<bool>(boolRange(randomGenerator_));
            // getDelimiterAmount depends on beginIsWS_ and endIsWS_
            delimiters_.resize(getDelimitersAmount());
            // filling dilimiters' lengths array with minimal length = 1
            for (auto& delimiter : delimiters_) {
                delimiter = DelimiteringChain{ };
            }
            setFileSplitting();
            int possibleOddWSChainsNumber{ };
            for (const auto& delimiter : delimiters_) {
                if (delimiter.canContainOddWSChain()) {
                    possibleOddWSChainsNumber++;
                }
            }
            
            if (possibleOddWSChainsNumber > 0) {
                std::uniform_int_distribution<int> oddChainsNumberRange(1, possibleOddWSChainsNumber);
                oddWSChainsNumber_ = oddChainsNumberRange(randomGenerator_);
            } else {
                oddWSChainsNumber_ = 0;
            }
            int remainOddWSChainsNumber{ oddWSChainsNumber_ };
            for (auto& delimiter: delimiters_) {
                if (delimiter.canContainOddWSChain() && remainOddWSChainsNumber > 0) {
                    delimiter.InsertOddWSChain();
                    --remainOddWSChainsNumber;
                }
            }
        } else {
            totalEvenWSChainsLength_ = 0;
            std::cout << "Enter the file's length: ";
            length_ = getNatural();
            beginIsWS_ = false;
            endIsWS_ = false;
            delimiters_.resize(getDelimitersAmount());

            if (delimiters_.size() == 1) {
                for (auto& delimiter : delimiters_) {
                    delimiter = DelimiteringChain{ length_ };
                } 
                std::uniform_int_distribution<int> oddChainsNumberRange(0, 1);
                oddWSChainsNumber_ = oddChainsNumberRange(randomGenerator_);
                int remainOddWSChainsNumber{ oddWSChainsNumber_ };
                for (auto& delimiter : delimiters_) {
                    if (delimiter.canContainOddWSChain() && remainOddWSChainsNumber > 0) {
                        delimiter.InsertOddWSChain();
                        --remainOddWSChainsNumber;
                    }
                }
            } else { }
        }
        writeToFile();
    } else {
        std::cerr << "\tError: File \"" + name_ + "\" is not opened" << std::endl;
        exit(-1);
    }
}

//-------------------------------------private methods---------------------------------------

int TestFile::getDelimitersAmount() const
{
    int delimitersAmount{ };
    if (totalEvenWSChainsLength_ > 0) {
        delimitersAmount = evenWSChains_.size() + 1;
        if (beginIsWS_) {
            delimitersAmount -= 1;
        }
        if (endIsWS_) {
            delimitersAmount -= 1;
        }
    } else if (length_ > 0) {
        delimitersAmount = 1;
    } else {
        delimitersAmount = 0;
    }

    return delimitersAmount;
}

std::string TestFile::setFileName()
{
    std::string fileName{ };
    std::regex fileNameRegex{ "^(?!.*_).*\\.txt$" };
    std::cin >> fileName;

    while (!std::regex_match(fileName.c_str(), fileNameRegex)) {
        std::cout << "\tError: Invalid file name\n\tRepeat the input: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> fileName;
    }

    return fileName;
}

void TestFile::setFileSplitting()
{
    // working with even white-spaces chaines' lengths

    const int MIN_WS_CHAIN_LENGTH{ 2 };
    int remainEvenWSChainsTotal{
        static_cast<int>(totalEvenWSChainsLength_ - evenWSChains_.size() * MIN_WS_CHAIN_LENGTH)
    };
    // filling the array of even white-spaces chaines' lengths
    std::uniform_int_distribution<int> evenWSChainsInxRange(0, evenWSChains_.size() - 1);
    while (remainEvenWSChainsTotal > 0) {
        int i = evenWSChainsInxRange(randomGenerator_);
        evenWSChains_.at(i).Increase(MIN_WS_CHAIN_LENGTH);
        remainEvenWSChainsTotal -= MIN_WS_CHAIN_LENGTH;
    }
    std::shuffle(std::begin(evenWSChains_), std::end(evenWSChains_), randomGenerator_);

    // working with delimitering chaines' lengths

    const int MIN_DELIMITER_LENGTH{ 1 };
    int remainFileLength{
        static_cast<int>(length_ - totalEvenWSChainsLength_ - MIN_DELIMITER_LENGTH * delimiters_.size())
    };
    // filling the array of delimiters' lengths
    std::uniform_int_distribution<int> delimitersInxRange(0, delimiters_.size() - 1);
    while (remainFileLength > 0) {
        int i = delimitersInxRange(randomGenerator_);
        delimiters_.at(i).Increase(MIN_DELIMITER_LENGTH);
        remainFileLength -= MIN_DELIMITER_LENGTH;
    }
    std::shuffle(std::begin(delimiters_), std::end(delimiters_), randomGenerator_);
}

void TestFile::writeToFile() const
{
    std::ofstream fout;
    fout.open(name_);
    if (!fout.is_open()) {
        std::cerr << "\tError: File \"" + name_ + "\"cannot be opened" << std::endl;
        exit(-1);
    }
    if (evenWSChains_.size() > 0) {
        char currentChar{ };
        int  remainOddWSChainsNumber{ oddWSChainsNumber_};
        const int ITERATIONS_AMOUNT{
            static_cast<int>(std::min(evenWSChains_.size(), delimiters_.size()))
        };
        if (beginIsWS_) {
            for (int i = 0; i < ITERATIONS_AMOUNT; i++) {
                evenWSChains_.at(i).SelfPrint(fout);
                delimiters_.at(i).SelfPrint(fout);
            }
            if (endIsWS_) {
                evenWSChains_.back().SelfPrint(fout);
            }
        } else {
            for (int i = 0; i < ITERATIONS_AMOUNT; i++) {
                delimiters_.at(i).SelfPrint(fout);
                evenWSChains_.at(i).SelfPrint(fout);
            }
            if (!endIsWS_) {
                delimiters_.back().SelfPrint(fout);
            }
        }
    } else if (length_ > 0) {
        delimiters_.front().SelfPrint(fout);
    }

    fout.close();
}

//-------------------------------------public methods---------------------------------------

std::string TestFile::GetFileName() const
{
    return name_;
}

void TestFile::SaveTestingResult(const double calculatedAverageLength,
                                 const double realAverageLength,
                                 const bool   isTestPassed) const
{
    std::fstream file("TestingResults.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "\tError: File \"TestingResults.txt\" cannot be opened" << std::endl;
        exit(-1);
    }
    std::string resultMessage{ };
    if (abs(calculatedAverageLength + 1.0) < DBL_EPSILON) { 
        resultMessage = "passed";
        file << "name: " << name_ << "\nlength: " << length_;
        file << "\neven ws chains total length: " << totalEvenWSChainsLength_;
        file << "\neven ws chains number: " << evenWSChains_.size();
        file << "\nodd ws chains number: " << oddWSChainsNumber_;
        file << "\ntesting result: " << resultMessage << "\n\n";
    } else {
        resultMessage = isTestPassed ? "passed" : "failed";
        file << "name: " << name_ << "\nlength: " << length_;
        file << "\neven ws chains total length: " << totalEvenWSChainsLength_;
        file << "\neven ws chains number: " << evenWSChains_.size();
        file << "\nodd ws chains number: " << oddWSChainsNumber_;
        file << "\ncalculated even ws length average: " << calculatedAverageLength;
        file << "\nreal even ws chains lengths average: " << realAverageLength;
        file << "\ntesting result: " << resultMessage << "\n\n";
    }
}

void TestFile::ConductTesting() const
{
    std::ifstream fin(name_.c_str(), std::ios::in);
    if (!fin.is_open()) {
        std::cerr << "\tError: File \"" + name_ + "\" is not opened" << std::endl;
        exit(-1);
    }
    double calculatedAverageLength{ };
    double realAverageLength{ };
    bool isTestPassed{ };
    if (totalEvenWSChainsLength_ > 0) {
        calculatedAverageLength = CalculateAverageLength(fin);
        fin.close();
        realAverageLength = totalEvenWSChainsLength_ / static_cast<double>(evenWSChains_.size());
        isTestPassed = abs(calculatedAverageLength - realAverageLength) < DBL_EPSILON;
    } else {
        calculatedAverageLength = -1.0;
        realAverageLength = -1.0;
    }

    SaveTestingResult(calculatedAverageLength, realAverageLength, isTestPassed);
}

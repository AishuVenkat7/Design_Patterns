// Question4

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

// LineFilter interface
class LineFilter
{
public:
    virtual bool shouldNotify(const std::string &line) = 0;
};

// Observer interface
class Observer
{
public:
    virtual void update(const std::string &line) = 0;
    virtual void setFilter(LineFilter *filter) = 0;
    virtual LineFilter *getFilter() = 0;
};

// Subject(publisher) class with Strategy pattern
class TextAnalyzer
{
private:
    std::vector<Observer *> observers;

public:
    void registerObserver(Observer *observer, LineFilter *filter)
    {
        // Store the observer and its associated filter
        observers.push_back(observer);
        observer->setFilter(filter);
    }

    void analyzeFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            // For each line, check if observers are interested based on their line filtering policies.
            for (Observer *observer : observers)
            {
                if (observer->getFilter()->shouldNotify(line))
                {
                    observer->update(line);
                }
            }
        }
    }
};

// Concrete LineFilter implementation
// prints "Yes! <line>" for lines containing a specific keyword
class KeywordFilter : public LineFilter
{
private:
    std::string keyword;

public:
    KeywordFilter(const std::string &keyword) : keyword(keyword) {}

    bool shouldNotify(const std::string &line) override
    {
        return std::search(line.begin(), line.end(), keyword.begin(), keyword.end(),
                           [](char ch1, char ch2)
                           { return std::tolower(ch1) == std::tolower(ch2); }) != line.end();
    }
};

// Concrete LineFilter implementation
// prints "So long....! <line>" for lines longer than a set character limit
class CharacterLimitFilter : public LineFilter
{
private:
    size_t maxLength;

public:
    CharacterLimitFilter(size_t maxLength) : maxLength(maxLength) {}

    bool shouldNotify(const std::string &line) override
    {
        return line.length() > maxLength;
    }
};

// Concrete Observer implementations
// i. Prints "Yes! <line>" for lines containing a specific keyword
class KeywordObserver : public Observer
{
private:
    LineFilter *keywordFilter;

public:
    void setFilter(LineFilter *filter) override
    {
        keywordFilter = filter;
    }

    LineFilter *getFilter()
    {
        return keywordFilter;
    }

    void update(const std::string &line) override
    {
        std::cout << "Yes! " << line << std::endl;
    }
};

// ii. Prints "So long....! <line>" for lines longer than a set character limit
class CharacterLimitObserver : public Observer
{
private:
    LineFilter *characterLimitFilter;

public:
    void setFilter(LineFilter *filter) override
    {
        characterLimitFilter = filter;
    }

    LineFilter *getFilter()
    {
        return characterLimitFilter;
    }

    void update(const std::string &line) override
    {
        std::cout << "So long....! " << line << std::endl;
    }
};

int main()
{
    TextAnalyzer textAnalyzer;

    std::string keyword;
    int characterLimit;
    std::cout << "Enter the keyword to check whether it is present in the file" << std::endl;
    std::cin >> keyword;
    std::cout << "Enter the character limit" << std::endl;
    std::cin >> characterLimit;
    std::cout << std::endl;

    // Register KeywordObserver with KeywordFilter
    KeywordObserver keywordObserver;
    KeywordFilter keywordFilter(keyword);
    textAnalyzer.registerObserver(&keywordObserver, &keywordFilter);

    // Register LengthObserver with LengthFilter
    CharacterLimitObserver lengthObserver;
    CharacterLimitFilter lengthFilter(characterLimit);
    textAnalyzer.registerObserver(&lengthObserver, &lengthFilter);

    // process each line from the file
    textAnalyzer.analyzeFile("sample_file.txt");

    return 0;
}

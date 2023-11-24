// Question3

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

// Observer - Interface
class Investor
{
public:
    virtual void update(std::string group) = 0;
    virtual void setThreshold(double threshold) = 0;
};

// Subject or publisher Interface
class Stock
{
public:
    virtual void registerInvestor(Investor *investor, std::string group) = 0;
    virtual void removeInvestor(Investor *investor, std::string groups) = 0;
    virtual void notifyInvestor(std::string group) = 0;
};

// Concrete Subject
class ConcreteStock : public Stock
{
private:
    double price;
    std::map<std::string, std::set<Investor *>> investorMap;

public:
    void registerInvestor(Investor *investor, std::string group) override
    {
        if (investorMap.count(group) > 0)
        {
            std::set<Investor *> &investorSet = investorMap[group];
            investorSet.insert(investor);
        }
        else
        {
            std::set<Investor *> investorSet = {investor};
            investorMap[group] = investorSet;
        }
    }
    void removeInvestor(Investor *investor, std::string group) override
    {
        std::set<Investor *> &investorSet = investorMap[group];
        investorSet.erase(investor);
    }
    void notifyInvestor(std::string group) override
    {
        std::set<Investor *> &investorSet = investorMap[group];
        for (Investor *investor : investorSet)
        {
            investor->update(group);
        }
    }

    void setPrice(double price, std::string group)
    {
        this->price = price;
        notifyInvestor(group);
    }

    double getPrice()
    {
        return this->price;
    }
};

// Concrete Observer
class ClientA : public Investor
{
private:
    double threshold;
    ConcreteStock *stock;

public:
    ClientA(ConcreteStock *stock, std::string group)
    {
        this->stock = stock;
        this->stock->registerInvestor(this, group);
    }
    void update(std::string group) override
    {
        std::cout << "Client A received an update for stock " << group
                  << " and its value is $" << stock->getPrice() << std::endl;
        if (threshold > 0 && stock->getPrice() > threshold)
        {
            std::cout << "Notifying Client A. Price crossed the threshold of $" << threshold
                      << " for stock " << group << "." << std::endl;
        }
    }
    void setThreshold(double threshold) override
    {
        this->threshold = threshold;
    }
};

// Concrete Observer
class ClientB : public Investor
{
private:
    double threshold;
    ConcreteStock *stock;

public:
    ClientB(ConcreteStock *stock, std::string group)
    {
        this->stock = stock;
        this->stock->registerInvestor(this, group);
    }
    void update(std::string group) override
    {
        std::cout << "Client B received an update for stock " << group
                  << " and its value is $" << stock->getPrice() << std::endl;
        if (threshold > 0 && stock->getPrice() > threshold)
        {
            std::cout << "Notifying Client B. Price crossed the threshold of $" << threshold
                      << " for stock " << group << "." << std::endl;
        }
    }
    void setThreshold(double threshold) override
    {
        this->threshold = threshold;
    }
};

// Concrete Observer
class ClientC : public Investor
{
private:
    double threshold;
    ConcreteStock *stock;

public:
    ClientC(ConcreteStock *stock, std::string group)
    {
        this->stock = stock;
        this->stock->registerInvestor(this, group);
    }
    void update(std::string group) override
    {
        std::cout << "Client C received an update for stock " << group
                  << " and its value is $" << stock->getPrice() << std::endl;
        ;
        if (threshold > 0 && stock->getPrice() > threshold)
        {
            std::cout << "Notifying Client C. Price crossed the threshold of $" << threshold
                      << " for stock " << group << "." << std::endl;
        }
    }
    void setThreshold(double threshold) override
    {
        this->threshold = threshold;
    }
};

int main()
{
    // Create the Subject object
    // It will handle registering, unregistering and updating all observers
    ConcreteStock concreteStock;

    // registering into groups and adding threshold
    ClientA clientA(&concreteStock, "GoogStock");
    clientA.setThreshold(450);
    ClientB clientB(&concreteStock, "DisneyStock");
    clientB.setThreshold(200);
    ClientC clientC(&concreteStock, "CvsStock");
    clientC.setThreshold(150);

    ClientB clientB1(&concreteStock, "CvsStock");
    clientB1.setThreshold(250);

    // notifying the observers
    concreteStock.setPrice(460, "GoogStock");
    std::cout << std::endl;
    concreteStock.setPrice(280, "DisneyStock");
    std::cout << std::endl;
    std::cout << "Before removing client B from CVS stock" << std::endl;
    concreteStock.setPrice(300, "CvsStock");

    // removing investor from particular stock
    concreteStock.removeInvestor(&clientB1, "CvsStock");

    std::cout << std::endl;
    std::cout << "after removing client B from CVS stock" << std::endl;
    concreteStock.setPrice(300, "CvsStock"); // clientB - crossing threshold

    return 0;
}
// Question5

#include <iostream>
#include <string>

// Component interface
class Cake
{
public:
    virtual std::string getName() = 0;
    virtual double cost() = 0;
};

// Concrete component
class RegularCake : public Cake
{
public:
    std::string getName()
    {
        return "Regular Cake";
    }

    double cost()
    {
        return 7.0;
    }
};

// Decorator base class
class CakeDecorator : public Cake
{
protected:
    Cake *cake;

public:
    CakeDecorator(Cake *cake) : cake(cake) {}

    std::string getName()
    {
        return cake->getName();
    }

    double cost()
    {
        return cake->cost();
    }
};

// Concrete decorator: MultiLayeredCakeDecorator
class MultiLayeredCakeDecorator : public CakeDecorator
{
public:
    MultiLayeredCakeDecorator(Cake *cake) : CakeDecorator(cake) {}

    std::string getName()
    {
        return cake->getName() + " Multi-layered";
    }

    // Additional cost for multi-layered cake
    double cost()
    {
        return cake->cost() + 5.0;
    }
};

// Concrete decorator: SprinklesDecorator
class SprinklesDecorator : public CakeDecorator
{
public:
    SprinklesDecorator(Cake *cake) : CakeDecorator(cake) {}

    std::string getName()
    {
        return cake->getName() + " with sprinkles";
    }

    double cost()
    {
        return cake->cost() + 1.0;
    }
};

// Concrete decorator: SayingDecorator
class SayingDecorator : public CakeDecorator
{
private:
    std::string saying;

public:
    SayingDecorator(Cake *cake, const std::string &saying) : CakeDecorator(cake), saying(saying) {}

    std::string getName()
    {
        return cake->getName() + " and message saying '" + saying + "'";
    }

    double cost()
    {
        return cake->cost();
    }
};

// New cake type: StrawberryCake
class StrawberryCake : public Cake
{
public:
    std::string getName()
    {
        return "Strawberry Cake";
    }

    double cost()
    {
        return 2 * RegularCake().cost();
    }
};

Cake *getCakeType()
{
    int choice;
    std::cout << "Select Cake Type:\n";
    std::cout << "1. Regular Cake - $7.0\n";
    std::cout << "2. Strawberry Cake - $14.0\n";
    std::cout << "Enter your choice (1 or 2): ";
    std::cin >> choice;

    if (choice == 2)
    {
        return new StrawberryCake();
    }
    else
    {
        return new RegularCake();
    }
}

Cake *getDecorations(Cake *cake)
{
    int choice;
    std::string continueOption;
    std::cout << "Select Cake Decorations:\n";
    std::cout << "1. Multi-layered - $5.0\n";
    std::cout << "2. With sprinkles - $1.0\n";
    std::cout << "3. Custom Message on the cake - $0.0\n";
    std::cout << "4. No decorations or messages\n";

    do
    {
        std::cout << "Enter your choice (1 to 4): ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            cake = new MultiLayeredCakeDecorator(cake);
            break;
        case 2:
            cake = new SprinklesDecorator(cake);
            break;
        case 3:
        {
            std::string saying;
            std::cout << "Enter custom saying: ";
            std::cin.ignore();
            std::getline(std::cin, saying);
            cake = new SayingDecorator(cake, saying);
            break;
        }
        case 4:
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }

        std::cout << "do you want to add anything else: (y/n)" << std::endl;
        std::cin >> continueOption;

    } while (continueOption == "y" || continueOption == "Y");

    return cake;
}

int main()
{
    // Get user input for cake type
    Cake *userCake = getCakeType();

    // Get user input for cake decorations
    userCake = getDecorations(userCake);

    // Display details of the customized cake
    std::cout << "Customized Cake Details: " << userCake->getName()
              << " and Cost: $" << userCake->cost() << std::endl;
    delete userCake;

    return 0;
}

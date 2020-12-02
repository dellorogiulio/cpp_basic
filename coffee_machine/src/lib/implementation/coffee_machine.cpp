#include <implementation/coffee_machine.h>
#include <thread>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

long CoffeeMachine::makeCoffee()
{
    //your code here
    return 0;
}

long CoffeeMachine::makeTea()
{
    //your code here
    return 0;
}

void CoffeeMachine::run()
{
    std::cout << "I'm running\n";
    std::cout << "Make tea\n";
    long tea_duration = makeTea();
    std::this_thread::sleep_for(std::chrono::seconds(tea_duration));
    std::cout << "Make coffee\n";
    long coffee_duration = makeCoffee();
}

#include <implementation/coffee_machine.h>
#include <thread>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void CoffeeMachine::makeCoffee()
{
    //your code here
}

void CoffeeMachine::makeTea()
{
    //your code here
}

void CoffeeMachine::run()
{
    while (is_running_)
    {
        std::cout << "I'm running\n";
        // here trigger button press

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

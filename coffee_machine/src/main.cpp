#include <iostream>
#include <nlohmann/json.hpp>
#include <implementation/coffee_machine.h>

using json = nlohmann::json;

int main()
{
    CoffeeMachine coffee_machine;
    coffee_machine.makeCoffee();
    coffee_machine.makeThe();
    return 0;
}

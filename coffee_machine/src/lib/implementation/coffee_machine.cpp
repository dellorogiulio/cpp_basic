#include <implementation/coffee_machine.h>
#include <thread>
#include <iostream>
#include <fstream>

CoffeeMachine::CoffeeMachine() :
    cup_valve_(0),
    stick_valve_(1),
    coffee_valve_(2),
    tea_valve_(3),
    coffee_button_("Coffee"),
    tea_button_("Tea"),
    modular_valves_{
        {"tea", tea_valve_},
        {"coffee", coffee_valve_},
    }
{
    std::ifstream json_file("../../config/recipe.json");
    if (json_file.fail())
    {
        throw std::runtime_error("Unable to find recipe.json");
    }
    recipe_json_ = json::parse(json_file);
    coffee_button_.onPressed([this]() {
        makeCoffee();
    });
    coffee_button_.onPressed([this]() {
        makeTea();
    });
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

long CoffeeMachine::makeCoffee()
{
    try
    {
        return makeRecipe("coffee");
    }
    catch (const std::runtime_error&)
    {
    }
    return 0;
}

long CoffeeMachine::makeTea()
{
    try
    {
        return makeRecipe("tea");
    }
    catch (const std::runtime_error&)
    {
    }
    return 0;
}

long CoffeeMachine::makeRecipe(const std::string& recipe_name)
{
    if (!recipe_json_.contains(recipe_name))
    {
        throw std::runtime_error("Unable to find " + recipe_name + " in recipe.json");
    }
    long actual_delay = 1;
    cup_valve_.scheduleOpen(1);
    for (const auto& ingredient : recipe_json_[recipe_name])
    {
        const std::string liquid = ingredient["liquid"];
        const long pouring_time = ingredient["time [s]"];
        if (modular_valves_.find(liquid) == modular_valves_.end())
            throw std::runtime_error("Unable to find " + liquid + " in recipe.json");
        modular_valves_.at(liquid).scheduleOpen(pouring_time, actual_delay);
        actual_delay += pouring_time;
    }
    stick_valve_.scheduleOpen(1, actual_delay);
    return actual_delay + 1;
}

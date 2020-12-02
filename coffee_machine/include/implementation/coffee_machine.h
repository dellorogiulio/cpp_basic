#ifndef COFFEE_MACHINE_H
#define COFFEE_MACHINE_H

#include <hardware_vendor/button.h>
#include <hardware_vendor/valve.h>
#include <string>
#include <map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class CoffeeMachine
{
    coffee_machine::Valve<coffee_machine::ValveType::impulsive> cup_valve_;
    coffee_machine::Valve<coffee_machine::ValveType::impulsive> stick_valve_;
    coffee_machine::Valve<coffee_machine::ValveType::modular> coffee_valve_;
    coffee_machine::Valve<coffee_machine::ValveType::modular> tea_valve_;

    coffee_machine::Button<0> coffee_button_;
    coffee_machine::Button<1> tea_button_;

    std::map<const std::string, coffee_machine::Valve<coffee_machine::ValveType::modular>&> modular_valves_;
    json recipe_json_;

   public:
    CoffeeMachine();
    void run();

   private:
    long makeTea();
    long makeCoffee();
    long makeRecipe(const std::string& recipe_name);
};

#endif  // COFFEE_MACHINE_H
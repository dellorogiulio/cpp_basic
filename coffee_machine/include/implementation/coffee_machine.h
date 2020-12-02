#ifndef COFFEE_MACHINE_H
#define COFFEE_MACHINE_H

class CoffeeMachine
{
    bool is_running_ = true;

   public:
    void run();

   private:
    void makeTea();
    void makeCoffee();
};

#endif  // COFFEE_MACHINE_H
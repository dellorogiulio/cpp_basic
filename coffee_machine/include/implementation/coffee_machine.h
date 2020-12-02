#ifndef COFFEE_MACHINE_H
#define COFFEE_MACHINE_H

class CoffeeMachine
{
   public:
    void run();

   private:
    long makeTea();
    long makeCoffee();
};

#endif  // COFFEE_MACHINE_H
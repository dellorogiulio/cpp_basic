#ifndef VALVE_H
#define VALVE_H

#include <string>
#include <functional>

namespace coffee_machine
{
enum class ValveType
{
    modular,
    impulsive,
};

template <std::size_t ValveRackPosition, ValveType type>
class Valve
{
    const std::size_t rack_position_ = ValveRackPosition;
    static constexpr ValveType type_ = type;

    void schedule(double, double)
    {
        // here we schedule the valve opening for open_time after delay
    }

   public:
    Valve()
    {
    }

    void scheduleOpen(double open_time, double delay = 0)
    {
        return schedule(open_time, delay);
    }
};
}  // namespace coffee_machine
#endif  // VALVE_H
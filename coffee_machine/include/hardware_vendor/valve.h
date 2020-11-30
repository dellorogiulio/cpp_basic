#ifndef VALVE_H
#define VALVE_H

#include <string>
#include <functional>
#include <chrono>

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

    void schedule(std::chrono::milliseconds, std::chrono::milliseconds)
    {
        // here we schedule the valve opening for open_time after delay
    }

   public:
    Valve()
    {
    }

    void scheduleOpen(std::chrono::milliseconds open_time, std::chrono::milliseconds delay = std::chrono::milliseconds(0))
    {
        return schedule(open_time, delay);
    }
};
}  // namespace coffee_machine
#endif  // VALVE_H
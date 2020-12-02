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

template <ValveType type>
class Valve
{
    static constexpr ValveType type_ = type;
    const unsigned int rack_position_;

    void schedule(double, double)
    {
        // here we schedule the valve opening for open_time after delay
    }

   public:
    Valve(unsigned int rack_position) :
        rack_position_(rack_position)
    {
    }

    void scheduleOpen(double open_time, double delay = 0)
    {
        return schedule(open_time, delay);
    }
};
}  // namespace coffee_machine
#endif  // VALVE_H
#ifndef VALVE_H
#define VALVE_H

#include <string>
#include <functional>
#include <thread>
#include <vector>
#include <iostream>

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
    std::vector<std::thread> threads_;

    void schedule(long open_time, long delay)
    {
        if (delay > 0)
            std::this_thread::sleep_for(std::chrono::seconds(delay));
        std::cout << "OPENING VALVE ON POSITION " << rack_position_ << "\n";
        if (open_time > 0)
            std::this_thread::sleep_for(std::chrono::seconds(open_time));
        std::cout << "CLOSING VALVE ON POSITION " << rack_position_ << "\n";
    }

   public:
    Valve(unsigned int rack_position) :
        rack_position_(rack_position)
    {
    }

    ~Valve()
    {
        for (auto& t : threads_)
            t.join();
    }

    void scheduleOpen(long open_time, long delay = 0)
    {
        threads_.emplace_back(&Valve<type>::schedule, this, open_time, delay);
    }
};
}  // namespace coffee_machine
#endif  // VALVE_H
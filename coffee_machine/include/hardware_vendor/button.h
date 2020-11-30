#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <functional>

namespace coffee_machine
{
template <std::size_t ButtonRackPosition>
class Button
{
    const std::size_t rack_position_ = ButtonRackPosition;
    const std::string button_label_;
    std::function<void(void)> callback_wrapper_;

   private:
    void call() { callback_wrapper_(); }

   public:
    Button(const std::string& label) :
        button_label_(label),
        callback_wrapper_()
    {
    }

    template <typename CallBack, typename... CallBackArgs>
    void onPressed(CallBack&& func, CallBackArgs&&... args)
    {
        auto binded = std::bind(std::forward<CallBack>(func), std::forward<CallBackArgs>(args)...);
        callback_wrapper_ = [binded{std::move(binded)}] {
            binded();
        };
    }
};
}  // namespace coffee_machine

#endif  // BUTTON_H
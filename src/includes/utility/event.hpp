#ifndef EVENT_HPP
#define EVENT_HPP

#include <functional>
#include <vector>

class Event
{
public:
    using Callback = std::function<void()>;

    // Subscribe to the event
    void subscribe(const Callback& callback)
    {
        mCallbacks.push_back(callback);
    }

    // Trigger (call) all subscribers
    void invoke() const
    {
        for (const auto& callback : mCallbacks)
        {
            callback();
        }
    }

private:
    std::vector<Callback> mCallbacks; // List of subscribed callbacks
};

#endif // EVENT_HPP
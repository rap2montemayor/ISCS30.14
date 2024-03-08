#pragma once

#include <functional>
#include <queue>

namespace poly {

// Enqueues function calls that will be processed at some later time. Typical
// uses would be to separate event callbacks from their triggers, and having
// some functionality repeat over a period of time.
template <typename CallbackArg>
class CallbackQueue {
    // Two queues are used in case callbacks want to reenqueue themselves.
    std::queue<std::function<void(CallbackArg)>> callbackQueue[2] = {};
    int mainQueue = 0;

public:
    CallbackQueue() = default;

    // Enqueue an event to the callback queue. This function assumes the
    // event arguments are already bound to the function, hence a void function.
    void enqueue(std::function<void(CallbackArg)> callback);
    
    // Calls each event in the callback queue and empties it.
    void process(CallbackArg args);
};

// Specialization for void
template <>
class CallbackQueue<void>;

}

#include "CallbackQueue.inl"

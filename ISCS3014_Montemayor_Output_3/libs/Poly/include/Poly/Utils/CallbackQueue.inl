#include "CallbackQueue.hpp"

namespace poly {

template <>
class CallbackQueue<void> {
    std::queue<std::function<void()>> callbackQueue[2] = {};
    int mainQueue = 0;
public:
    CallbackQueue() = default;
    void enqueue(std::function<void()> callback) {
        callbackQueue[mainQueue].push(callback);
    }
    void process() {
        mainQueue = (mainQueue+1) % 2; // In case of reenqueue
        while (not callbackQueue[(mainQueue+1) % 2].empty()) {
            callbackQueue[(mainQueue+1) % 2].front()();
            callbackQueue[(mainQueue+1) % 2].pop();
        }
    }
};

template <typename CallbackArg>
void CallbackQueue<CallbackArg>::enqueue(
        std::function<void(CallbackArg)> callback) {
    callbackQueue[mainQueue].push(callback);
}

template <typename CallbackArg>
void CallbackQueue<CallbackArg>::process(CallbackArg args) {
    mainQueue = (mainQueue+1) % 2; // In case of reenqueue
    while (not callbackQueue[(mainQueue+1) % 2].empty()) {
        callbackQueue[(mainQueue+1) % 2].front()(args);
        callbackQueue[(mainQueue+1) % 2].pop();
    }
}

}
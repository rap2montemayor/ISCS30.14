#pragma once

#include <functional>
#include <cmath>

#include "CallbackQueue.hpp"

namespace poly {

struct AnimationParameters {
    double startVal;
    double endVal;
    double currentTime;
    double endTime;
};

class Animator {
    CallbackQueue<const double> callbackQueue;

public:
    Animator() = default;

    void update(const double deltaTime);

    void interpolate(double start, double end, double duration,
        std::function<void(double)> callback,
        std::function<void()> endCallback=nullptr,
        std::function<double(const AnimationParameters)> scaling=linearScaling);

    void interpolate(double start, double end, double duration,
        std::function<void(double)> callback,
        std::function<double(const AnimationParameters)> scaling);

    static double linearScaling(const AnimationParameters params);

    static double sigmoidScaling(const AnimationParameters params);

private:
    void interpolateHandler(AnimationParameters params, const double deltaTime,
        std::function<void(double)> callback,
        std::function<void()> endCallback=nullptr,
        std::function<double(const AnimationParameters)> scaling=linearScaling);
};

}

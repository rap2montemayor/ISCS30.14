#include "Poly/Utils/Animator.hpp"

namespace poly {

void Animator::update(const double deltaTime) {
    callbackQueue.process(deltaTime);
}

void Animator::interpolate(double startVal, double endVal, double duration,
        std::function<void(double)> callback, std::function<void()> endCallback,
        std::function<double(const AnimationParameters)> scaling) {
    AnimationParameters params = {startVal, endVal, 0, duration};
    callbackQueue.enqueue(
        [this, params, callback, endCallback, scaling]
        (const double deltaTime) {
            interpolateHandler(
                    params, deltaTime, callback, endCallback, scaling);
        }
    );
}

void Animator::interpolate(double startVal, double endVal, double duration,
        std::function<void(double)> callback,
        std::function<double(const AnimationParameters)> scaling) {
    interpolate(
        startVal, endVal, duration, callback, nullptr, linearScaling);
}

void Animator::interpolateHandler(AnimationParameters params,
        const double deltaTime, std::function<void(double)> callback,
        std::function<void()> endCallback,
        std::function<double(const AnimationParameters)> scaling) {
    auto& [startVal, endVal, curTime, endTime] = params;
    curTime += deltaTime;
    if (curTime < endTime) {
        callback(scaling(params));
        callbackQueue.enqueue(
            [this, params, callback, endCallback, scaling]
            (const double deltaTime) {
                interpolateHandler(
                    params, deltaTime, callback, endCallback, scaling);
            }
        );
    } else {
        callback(endVal);
        if (endCallback != nullptr) {
            endCallback();
        }
    }
}

double Animator::linearScaling(const AnimationParameters params) {
    auto& [startVal, endVal, currentTime, endTime] = params;
    return startVal + (endVal-startVal) * (currentTime / endTime);
}

double Animator::sigmoidScaling(const AnimationParameters params) {
    auto& [startVal, endVal, currentTime, endTime] = params;
    double e = exp(10.0 * ((currentTime / endTime) - 0.5));
    return startVal + (endVal - startVal) * e / (e+1);
}

}

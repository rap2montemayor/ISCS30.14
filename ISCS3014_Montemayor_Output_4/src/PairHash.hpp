#ifndef SRC_PAIRHASH_HPP_
#define SRC_PAIRHASH_HPP_

#include <functional>
#include <utility>

namespace std {
    template<typename T, typename U>
    struct hash<std::pair<T, U>> {
        std::size_t operator()(const std::pair<T, U> p) const {
            auto first = std::hash<T>()(p.first);
            auto second = std::hash<U>()(p.second);
            first ^= second + 0x9e3779b9 + (first<<6) + (first>>2);
            return first;
        }
    };
}

#endif // SRC_PAIRHASH_HPP_

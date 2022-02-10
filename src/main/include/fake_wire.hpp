#pragma once

#include <chrono>
#include <algorithm>

inline decltype(auto) millis() noexcept{
    using namespace std::chrono;
    return high_resolution_clock::now();
}

inline decltype(auto) min(auto&& a, auto&& b){
    return std::min(std::forward(a), std::forward(b));
}
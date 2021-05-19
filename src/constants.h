#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>

constexpr std::size_t kFramesPerSecond{60};
constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
constexpr std::size_t kScreenWidth{640};
constexpr std::size_t kScreenHeight{640};
constexpr int kMinMazeSize{5};
constexpr int kMaxMazeSize{25};

#endif
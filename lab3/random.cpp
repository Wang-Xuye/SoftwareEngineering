// Copyright 2024 wangxuye

#include "include/random.h"

std::mt19937 randint((unsigned)time(NULL));
int randomInt(int l, int r) {
    // 获得服从均匀分布的随机数，区间为 [l, r]
    std::uniform_int_distribution<int> dis(l, r);
    return dis(randint);
}

#include <bits/stdc++.h>
#include "random.h"

int random_int(int l, int r) {
    // ��÷��Ӿ��ȷֲ��������������Ϊ [l, r]
    uniform_int_distribution<int> dis(l, r);
    return dis(randint);
}
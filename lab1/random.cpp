#include <bits/stdc++.h>
#include "random.h"

mt19937 randint((unsigned)time(NULL));
int randomInt(int l, int r) {
    // ��÷��Ӿ��ȷֲ��������������Ϊ [l, r]
    uniform_int_distribution<int> dis(l, r);
    return dis(randint);
}
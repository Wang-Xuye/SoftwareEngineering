#ifndef __RANDOM_H
#define __RANDOM_H
#include <bits/stdc++.h>
using namespace std;

mt19937 randint((unsigned)time(NULL));
int random_int(int l, int r);

#endif
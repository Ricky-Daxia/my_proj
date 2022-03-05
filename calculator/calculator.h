#pragma once
#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<iomanip>
using namespace std;

unordered_map<string, int> operators {
    {"+", 1},
    {"-", 2},
    {"*", 3},
    {"/", 4},
    {"(", 5},
    {")", 6}
};

unordered_map<char, float> operands {
    {'a', 1.1},
    {'b', 1.2},
    {'c', 1.3},
    {'d', 1.4},
    {'e', 1.5},
    {'f', 1.6},
    {'g', 1.7}
};


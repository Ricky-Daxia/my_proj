#pragma once
#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<iomanip>
using namespace std;

unordered_map<char, int> operators {
    {'+', 1},
    {'-', 2},
    {'*', 3},
    {'/', 4},
    {'(', 5},
    {')', 6}
};

unordered_map<char, float> operands {};

string filter (string expr);

bool expr_validity (string expr);

string generate_expr (string expr);

string infix_to_suffix (string expr);

vector<float> eval (string expr);
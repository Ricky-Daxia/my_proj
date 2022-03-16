#pragma once
#include<iostream>
#include<stack>
#include<string>
#include<vector>
#include<unordered_map>
#include<iomanip>
using namespace std;

extern unordered_map<char, int> operators;

extern unordered_map<char, double> operands;

string filter (string expr);

bool expr_validity (string expr);

string generate_expr (string expr);

string infix_to_suffix (string expr);

vector<double> eval (string expr);

vector<double> API (string test);
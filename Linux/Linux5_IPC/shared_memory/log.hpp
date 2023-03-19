#pragma once
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

ostream& Log() {
    cout << "For Debug |" << "timestamp: " << (uint64_t)time(nullptr) << "|";
    return cout;
}
#pragma once

#include <pthread.h>

#include <ctime>
#include <iostream>

std::ostream &Log() {
  std::cout << "For Debug | "
            << "timestamp: " << (uint64_t)time(nullptr) << " | "
            << " Thread[ " << pthread_self() << "] | ";
  return std::cout;
}
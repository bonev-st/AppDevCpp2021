/*
 * ThreadUtils.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#include "utils/thread/ThreadUtils.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <thread>
#endif


#include <iostream>

namespace ThreadUtils {

void sleep_usec(int64_t microseconds) {
#ifdef _WIN32
  const DWORD milliseconds = static_cast<DWORD>(microseconds / 1000);
  Sleep(milliseconds); //sleep uses milliseconds
#else
#if 1
  std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
#else
  std::cout << "Delay for: " << microseconds << " us\n";
  auto start = std::chrono::high_resolution_clock::now();
  std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end-start;
  std::cout << "Waited " << elapsed.count() << " us\n";
#endif
#endif
}

}

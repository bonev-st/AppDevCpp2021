/*
 * ThreadUtils.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: stanimir
 */

#include "ThreadUtils.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <thread>
#endif

namespace ThreadUtils {

void sleep_usec(int64_t microseconds) {
#ifdef _WIN32
  const DWORD milliseconds = static_cast<DWORD>(microseconds / 1000);
  Sleep(milliseconds); //sleep uses milliseconds
#else
  std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
#endif
}

}

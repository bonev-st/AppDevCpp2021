/*
 * BaseMgr.hpp
 *
 *  Created on: Oct 26, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_BASEMGR_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_BASEMGR_HPP_

#include <cstdint>
#include "utils/NoCopy.hpp"

enum ManagersId_t : std::uint32_t {
	MGR_DRAW = 0,
	MGR_RES,
	MGR_TIMER,
	MGR_TIMER1,
	MGR_NUMB
};

class BaseMgr : private NoCopy {
public:
	virtual ~BaseMgr() = default;
	virtual bool process() {
		return true;
	}
};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_BASEMGR_HPP_ */

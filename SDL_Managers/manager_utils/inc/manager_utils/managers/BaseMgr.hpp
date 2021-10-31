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
	MGR_RES = 0,
	MGR_DRAW,
	MGR_NUMB
};

class BaseMgr : private NoCopy {
public:
	virtual ~BaseMgr() = default;

	virtual void process() = 0;
};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_BASEMGR_HPP_ */

/*
 * BaseMgr.hpp
 *
 *  Created on: Oct 26, 2021
 *      Author: stanimir
 */

#ifndef GR_ENGINE_INC_GR_ENGINE_MANAGERS_BASEMGR_HPP_
#define GR_ENGINE_INC_GR_ENGINE_MANAGERS_BASEMGR_HPP_

#include <cstdint>
#include "utils/NoCopy.hpp"

enum ManagersId_t : std::uint32_t {
	MGR_DRAW = 0,
	MGR_RES,
	MGR_TIMER2,
	MGR_NUMB
};

class BaseMgr : private NoCopy {
public:
	virtual ~BaseMgr() = default;
	virtual std::size_t getActive() const {
		return 0;
	}
	virtual std::size_t getMaxActive() const {
		return 0;
	}
};

#endif /* GR_ENGINE_INC_GR_ENGINE_MANAGERS_BASEMGR_HPP_ */

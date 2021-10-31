/*
 * Mgr.hpp
 *
 *  Created on: Oct 27, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_MGRS_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_MGRS_HPP_

#include "manager_utils/config/ResourcesConfig.hpp"
#include "manager_utils/managers/ResMgr.hpp"
#include "manager_utils/managers/DrawMgr.hpp"

class Mgrs : public ResMgr, public DrawMgr {
public:
	Mgrs() = default;
	bool init(const ResourcesConfig::Config_t &cfg);

};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_MGRS_HPP_ */

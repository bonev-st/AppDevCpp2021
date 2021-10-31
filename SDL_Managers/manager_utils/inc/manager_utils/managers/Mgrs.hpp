/*
 * Mgr.hpp
 *
 *  Created on: Oct 27, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_MGRS_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_MGRS_HPP_

#include "manager_utils/config/ResourcesConfig.hpp"
#include "manager_utils/managers/BaseMgr.hpp"

class Mgrs {
public:
	bool init(const ResourcesConfig::Config_t &cfg);
	void process();

private:
	std::array<BaseMgr*, ManagersId_t::MGR_NUMB> m_Managers;
};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_MGRS_HPP_ */

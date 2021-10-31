/*
 * Mgr.hpp
 *
 *  Created on: Oct 27, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_MGRS_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_MGRS_HPP_

#include <memory>

#include "manager_utils/config/ResourcesConfig.hpp"
#include "manager_utils/managers/BaseMgr.hpp"

class Mgrs {
public:
	~Mgrs();
	bool init(const ResourcesConfig::Config_t &cfg);
	void process();

private:
	std::array<std::unique_ptr<BaseMgr>, ManagersId_t::MGR_NUMB> m_Managers;

	void reset(BaseMgr * const p);
};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_MGRS_HPP_ */

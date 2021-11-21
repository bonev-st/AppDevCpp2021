/*
 * Timer2Mgr.hpp
 *
 *  Created on: Nov 13, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_TIMER2MGR_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_TIMER2MGR_HPP_

#include <unordered_set>
#include <memory>

#include "utils/Singleton.hpp"
#include "utils/timer/Timer2Cfg.hpp"
#include "utils/containers/FirstFreeContainer.hpp"
#include "utils/inputs/InputEventIF.hpp"
#include "manager_utils/managers/BaseMgr.hpp"

class InputEvent;

class Timer2Mgr : public BaseMgr, public InputEventIF {
public:
	Timer2::TimerHandler_t start(uint32_t period, Timer2::TimerMode_t mode, const Timer2::TimerCB_t& cb);
	void stop(Timer2::TimerHandler_t handler);
	bool isRunning(Timer2::TimerHandler_t handler) const;
	bool changePeriod(Timer2::TimerHandler_t handler, uint32_t period);

	std::size_t getActive() const final;
	std::size_t getMaxActive() const final;

	bool handleEvent(const InputEvent &e) final;

private:
	FirstFreeContainer<std::shared_ptr<Timer2::TimerCfg_t>> m_Container;

	void release_timer_data(const Timer2::TimerCfg_t & data);
};

using Timer2MgrInst = Singleton<Timer2Mgr>;

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_TIMER2MGR_HPP_ */

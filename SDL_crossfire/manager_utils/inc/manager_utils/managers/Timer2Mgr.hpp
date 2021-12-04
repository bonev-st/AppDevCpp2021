/*
 * Timer2Mgr.hpp
 *
 *  Created on: Nov 13, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_TIMER2MGR_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_TIMER2MGR_HPP_

#include <list>
#include <memory>

#include "utils/Singleton.hpp"
#include "utils/timer/Timer2Cfg.hpp"
#include "utils/inputs/InputEventIF.hpp"
#include "manager_utils/managers/BaseMgr.hpp"

class InputEvent;

class Timer2Mgr : public BaseMgr, public InputEventIF {
public:
	const std::shared_ptr<Timer2::TimerCfg_t> start(uint32_t period, Timer2::TimerMode_t mode, const Timer2::TimerCB_t& cb);
	void stop(Timer2::Iterator_t &handler);
	bool isRunning(const Timer2::Iterator_t &handler) const;
	bool changePeriod(Timer2::Iterator_t &handler, uint32_t period);

	std::size_t getActive() const final;
	std::size_t getMaxActive() const final;

	bool handleEvent(const InputEvent &e) final;

private:
	std::size_t m_MaxSize = 0;
	std::list<std::shared_ptr<Timer2::TimerCfg_t>> m_Container;

	void release_timer_data(Timer2::Iterator_t & it);

	Timer2::Iterator_t & getIterator(Timer2::TimerHandler_t &handler) const;
};

using Timer2MgrInst = Singleton<Timer2Mgr>;

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_TIMER2MGR_HPP_ */

/*
 * Timer2Client.hpp
 *
 *  Created on: Nov 13, 2021
 *      Author: stanimir
 */

#ifndef GR_ENGINE_INC_GR_ENGINE_TIMER_TIMER2CLIENT_HPP_
#define GR_ENGINE_INC_GR_ENGINE_TIMER_TIMER2CLIENT_HPP_

#include <memory>
#include "utils/timer/Timer2Def.hpp"

namespace Timer2 {
struct TimerCfg_t;
}

class Timer2Client {
public:
	~Timer2Client();
	bool start(uint32_t period, Timer2::TimerMode_t mode, const Timer2::TimerCB_t& cb);
	void stop();
	bool isRunning() const;
	bool changePeriod(uint32_t period);
	bool operator == (Timer2::TimerHandler_t handler) const;
	bool operator != (Timer2::TimerHandler_t handler) const;

private:
	std::weak_ptr<Timer2::TimerCfg_t> m_Handler;
};

#endif /* GR_ENGINE_INC_GR_ENGINE_TIMER_TIMER2CLIENT_HPP_ */

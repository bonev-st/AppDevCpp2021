/*
 * DrawMgr.hpp
 *
 *  Created on: Oct 26, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_DRAWMGR_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_DRAWMGR_HPP_

#include "manager_utils/managers/BaseMgr.hpp"
#include "sdl_utils/Renderer.hpp"

namespace DrawMgrConfig {
struct Config_t;
}
struct DrawParams_t;

class DrawMgr : public BaseMgr {
public:
	bool init(const DrawMgrConfig::Config_t &cfg);

	void process() final;

	bool clearScreen();
	void finishFrame();
	void draw(const DrawParams_t & draw);

	SDL_Renderer* getRendered() const;

private:
	Renderer m_Renderer;
	std::int64_t m_MaxFrameRate = 0;
	bool drawImage(const DrawParams_t & img);
	bool drawText(const DrawParams_t & text);
};

extern DrawMgr * G_pDrawMgr;

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_DRAWMGR_HPP_ */

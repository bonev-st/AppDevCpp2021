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
class ResMgr;

class DrawMgr : public BaseMgr {
public:
	bool init(const DrawMgrConfig::Config_t &cfg);

	bool clearScreen() const;
	void finishFrame() const;
	void draw(const DrawParams_t & draw) const;

	SDL_Renderer* getRendered() const;

	bool setBlendMode(const DrawParams_t & draw);
	bool setAlpha(const DrawParams_t & draw);

private:
	Renderer m_Renderer;
	bool drawImage(const DrawParams_t & img) const;
	bool drawText(const DrawParams_t & text) const;
};

extern DrawMgr *G_pDrawMgr;

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_DRAWMGR_HPP_ */

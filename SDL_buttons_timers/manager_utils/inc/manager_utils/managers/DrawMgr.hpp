/*
 * DrawMgr.hpp
 *
 *  Created on: Oct 26, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_DRAWMGR_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_DRAWMGR_HPP_

#include "utils/Singleton.hpp"

#include "manager_utils/managers/BaseMgr.hpp"

namespace DrawMgrConfig {
struct Config_t;
}

struct DrawParams_t;
class ResMgr;
class SDL_Renderer;
class Renderer;

class DrawMgr : public BaseMgr {
public:
	bool init(const DrawMgrConfig::Config_t &cfg, Renderer* render);

	bool clearScreen() const;
	void finishFrame() const;
	void draw(const DrawParams_t & draw) const;

	SDL_Renderer* getRendered() const;

	bool setBlendMode(const DrawParams_t & draw);
	bool setAlpha(const DrawParams_t & draw);

private:
	Renderer * m_Renderer = nullptr;
	ResMgr * m_Resources = nullptr;

	bool drawImage(const DrawParams_t & img) const;
	bool drawText(const DrawParams_t & text) const;
};

using DrawMgrInst = Singleton<DrawMgr>;

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_MANAGERS_DRAWMGR_HPP_ */

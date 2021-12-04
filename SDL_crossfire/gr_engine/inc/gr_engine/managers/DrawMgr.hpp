/*
 * DrawMgr.hpp
 *
 *  Created on: Oct 26, 2021
 *      Author: stanimir
 */

#ifndef GR_ENGINE_INC_GR_ENGINE_MANAGERS_DRAWMGR_HPP_
#define GR_ENGINE_INC_GR_ENGINE_MANAGERS_DRAWMGR_HPP_

#include "gr_engine/managers/BaseMgr.hpp"
#include "utils/Singleton.hpp"


namespace DrawMgrConfig {
struct Config_t;
}
namespace DisplayMode {
struct Mode_t;
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
	const DisplayMode::Mode_t & getDisplayMode() const;

private:
	Renderer * m_Renderer = nullptr;
	ResMgr * m_Resources = nullptr;

	bool drawImage(const DrawParams_t & img) const;
	bool drawText(const DrawParams_t & text) const;
};

using DrawMgrInst = Singleton<DrawMgr>;

#endif /* GR_ENGINE_INC_GR_ENGINE_MANAGERS_DRAWMGR_HPP_ */

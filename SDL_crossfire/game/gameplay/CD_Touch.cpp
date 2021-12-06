/*
 * CD_Touch.cpp
 *
 *  Created on: Nov 27, 2021
 *      Author: stanimir
 */

#include "game/gameplay/CD_Touch.hpp"

#include "gr_engine/drawing/Widget.hpp"

std::vector<Widget*> CD_Touch::operator ()(Widget* obj, const std::vector<Widget *> & others) const {
	std::vector<Widget*> rc;
	if(obj) {
		rc.reserve(2);
		for(const auto e : others) {
			if(!e->getVisible()) {
				continue;
			}
			if(obj->getRectangle().isToched(e->getRectangle())) {
				if(rc.empty()) {
					rc.push_back(obj);
				}
				rc.push_back(e);
			}
		}
	}
	return rc;
}

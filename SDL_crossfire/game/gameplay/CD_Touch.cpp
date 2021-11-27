/*
 * CD_Touch.cpp
 *
 *  Created on: Nov 27, 2021
 *      Author: stanimir
 */

#include "game/gameplay/CD_Touch.hpp"

#include "manager_utils/drawing/Widget.hpp"

std::vector<const Widget*> CD_Touch::operator ()(const Widget* obj, const std::deque<const Widget *> & others) const {
	std::vector<const Widget*> rc;
	rc.reserve(2);
	if(obj) {
		for(const auto e : others) {
			if(!e->getVisible()) {
				continue;
			}
			if(obj->getRectangle().isInside(e->getRectangle())) {
				if(rc.empty()) {
					rc.push_back(obj);
				}
				rc.push_back(e);
			}
		}
	}
	return rc;
}

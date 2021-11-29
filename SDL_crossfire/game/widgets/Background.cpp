/*
 * Background.cpp
 *
 *  Created on: Nov 28, 2021
 *      Author: stanimir
 */

#include "game/widgets/Background.hpp"

#include <cmath>
#include <iostream>

#include "utils/geometry/Geometry.hpp"
#include "utils/drawing/BlendMode.hpp"

bool Background::init(std::size_t img_id, int32_t alpha, double deep, const Dimention & visible_area, const Rectangle & motion_area, const Widget & targer) {
	if(!m_Image.create(img_id)) {
		std::cerr << "Create image failed" << std::endl;
		return false;
	}
	if(FULL_OPACITY != alpha) {
		m_Image.activateAlphaModulation();
		m_Image.setOpacity(alpha);
	}
	m_Deep = deep;
	m_Target = &targer;
	Dimention area = visible_area;
	m_BasePoint = motion_area.m_Pos;
	area.m_H += Geometry::scaleVal(motion_area.m_H, deep);
	area.m_W += Geometry::scaleVal(motion_area.m_W, deep);
	Dimention image_dim;
	image_dim.m_W = m_Image.getWidth();
	image_dim.m_H = m_Image.getHeight();
	const double w_scale =  area.m_W/static_cast<double>(image_dim.m_W);
	const double h_scale =  area.m_H/static_cast<double>(image_dim.m_H);
	double scale_factor = w_scale;
	if(h_scale > scale_factor) {
		scale_factor = h_scale;
	}
	if(!m_ScaleImage.init(scale_factor, &m_Image)) {
		std::cerr << "Create image failed" << std::endl;
		return false;
	}
	image_dim.m_W = m_ScaleImage.getWidth();
	image_dim.m_H = m_ScaleImage.getHeight();
	m_OffsetPoint = Point((visible_area.m_W - image_dim.m_W + Geometry::scaleVal(motion_area.m_W, deep))/2,
						  (visible_area.m_H - image_dim.m_H + Geometry::scaleVal(motion_area.m_H, deep))/2);
	return true;
}

void Background::draw() {
	auto point = m_OffsetPoint + Geometry::scalePoint(m_BasePoint - m_Target->getPosition(), m_Deep);
	//auto point = m_BasePoint;
	m_ScaleImage.setPosition(point);
	m_ScaleImage.draw();
}

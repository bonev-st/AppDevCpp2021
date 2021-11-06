/*
 * Widget.hpp
 *
 *  Created on: Oct 31, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_WIDGET_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_WIDGET_HPP_

#include "utils/drawing/DrawParams.hpp"

class DrawMgr;

class Widget {
public:
	void draw() const;

	void setVisible(bool visible);
	bool getVisible() const;

	void setPosition(const Point& pos);
	const Point& getPosition() const;
	void setX(int32_t x);
	void setY(int32_t y);
	void moveRight(int32_t val);
	void moveLeft(int32_t val);
	void moveUp(int32_t val);
	void moveDown(int32_t val);
	void moveH(int32_t val);
	void moveV(int32_t val);

	int32_t getWidth() const;
	int32_t getHeight() const;

	void activateAlphaModulation();
	void deactivateAlphaModulation();
	void setOpacity(int32_t opacity);
	int32_t getOpacity() const;

	void scale(double val);

	void setFlipMode(FlipMode_t flip);

	void setRotation(double angle);
	double getRotation() const;
	void rotate(double delta);
	void rotateRight(double delta);
	void rotateLeft(double delta);

	void setRotationCenter(const Point& point);
	const Point& getRotationCenter() const;

	bool isContains(const Point &pos) const;
	bool isContains(const Rectangle &rec) const;

protected:
	DrawParams_t m_DrawParams;
	bool m_Visible = true;

private:
	static DrawMgr *& m_DrawMgr;
};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_WIDGET_HPP_ */

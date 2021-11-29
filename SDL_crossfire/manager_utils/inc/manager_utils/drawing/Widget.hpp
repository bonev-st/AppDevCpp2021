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
	virtual ~Widget() = default;

	static void setDebug(bool ena);
	static bool getDebug();

	void invalidate();
	virtual bool isInvalidate() const;

	virtual void draw();

	void setVisible(bool visible);
	bool getVisible() const;

	void setPosition(const Point& pos);
	virtual void setPositionCenter(const Point& pos);
	void setPosition(const Point& pos, const Dimention &dim);
	Point getPosition() const;
	Point getPositionCenter() const;
	void setX(int32_t x);
	void setY(int32_t y);
	void moveRight(int32_t val);
	void moveLeft(int32_t val);
	void moveUp(int32_t val);
	void moveDown(int32_t val);
	void moveH(int32_t val);
	void moveV(int32_t val);

	Dimention getDimentions() const;
	int32_t getWidth() const;
	int32_t getHeight() const;
	int32_t getX() const;
	int32_t getY() const;
	int32_t getBottom() const;
	int32_t getRight() const;
	Rectangle getRectangle() const;
	void setRectangle(const Rectangle rect);

	bool isAlphaModulationActivate() const;
	void activateAlphaModulation();
	void deactivateAlphaModulation();
	void setOpacity(int32_t opacity);
	int32_t getOpacity() const;

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
	static bool g_Debug;
};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_DRAWING_WIDGET_HPP_ */

/*
 * RadioWidget.hpp
 *
 *  Created on: Nov 4, 2021
 *      Author: stanimir
 */

#ifndef MANAGER_UTILS_INC_MANAGER_UTILS_INPUT_RADIOWIDGET_HPP_
#define MANAGER_UTILS_INC_MANAGER_UTILS_INPUT_RADIOWIDGET_HPP_

#include <functional>

using RadioCB_t = std::function<void(std::size_t)>;

class RadioWidget {
public:
	virtual ~RadioWidget() = default;
	virtual void attachCB(const RadioCB_t & fn) = 0;
	virtual bool getSelected() const = 0;
	virtual void setSelected() = 0;
	virtual void setDeslected() = 0;
	virtual std::size_t getId() const = 0;
};

#endif /* MANAGER_UTILS_INC_MANAGER_UTILS_INPUT_RADIOWIDGET_HPP_ */

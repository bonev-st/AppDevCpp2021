/*
 * RadioWidget.hpp
 *
 *  Created on: Nov 4, 2021
 *      Author: stanimir
 */

#ifndef GR_ENGINE_INC_GR_ENGINE_INPUT_RADIOWIDGET_HPP_
#define GR_ENGINE_INC_GR_ENGINE_INPUT_RADIOWIDGET_HPP_

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

#endif /* GR_ENGINE_INC_GR_ENGINE_INPUT_RADIOWIDGET_HPP_ */

/*
 * ExpFilter.hpp
 *
 *  Created on: Nov 14, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INC_UTILS_FILTER_EXPFILTER_HPP_
#define UTILS_INC_UTILS_FILTER_EXPFILTER_HPP_

class ExpFilter {
public:
	ExpFilter() = default;
	explicit ExpFilter(double smoothing_factor);
	void setSmootingFactor(double smoothing_factor);
	void clear();
	double operator = (double val);
	operator double() const;

private:
	double m_SmootingFactor = 1;
	double m_Value = 0;

	void setCoef(double smoothing_factor);
};

#endif /* UTILS_INC_UTILS_FILTER_EXPFILTER_HPP_ */

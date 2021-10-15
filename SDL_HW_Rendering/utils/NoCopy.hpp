/*
 * NoCopy.hpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#ifndef UTILS_NOCOPY_HPP_
#define UTILS_NOCOPY_HPP_


class NoCopy {
	NoCopy(const NoCopy &) = delete;
	NoCopy(NoCopy &&) = delete;
	NoCopy operator = (const NoCopy &) = delete;
	NoCopy operator = (NoCopy &&) = delete;
public:
	NoCopy() = default;
    ~NoCopy() = default;
};

#endif /* UTILS_NOCOPY_HPP_ */

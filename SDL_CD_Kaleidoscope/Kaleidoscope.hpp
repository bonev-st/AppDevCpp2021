/*
 * Kaleidoscope.hpp
 *
 *  Created on: Oct 11, 2021
 *      Author: stanimir
 */

#ifndef KALEIDOSCOPE_HPP_
#define KALEIDOSCOPE_HPP_

#include <cstdint>

struct SDL_Surface;

class Kaleidoscope {
public:
	explicit Kaleidoscope(SDL_Surface * surface);
	~Kaleidoscope() = default;

	std::int32_t update();

	SDL_Surface * getSurface() {
		return m_Surface;
	}
private:
	SDL_Surface * m_Surface;
	std::int32_t Offset;
};

#endif /* KALEIDOSCOPE_HPP_ */

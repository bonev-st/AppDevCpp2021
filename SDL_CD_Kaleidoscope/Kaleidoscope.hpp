/*
 * Kaleidoscope.hpp
 *
 *  Created on: Oct 11, 2021
 *      Author: stanimir
 */

#ifndef KALEIDOSCOPE_HPP_
#define KALEIDOSCOPE_HPP_

#include <cstdint>
#include <array>
#include <deque>
#include <stack>

struct SDL_Surface;

class Kaleidoscope {
public:
	~Kaleidoscope() {
		deinit();
	}
	std::int32_t init();
	std::int32_t update();

	SDL_Surface * getSurface() {
		return m_Surface;
	}
private:
	constexpr static uint32_t WIDTH = 64;
	constexpr static uint32_t HIGHT = 64;
	constexpr static uint32_t WIDTH_TO_BYTES = (WIDTH/2);
	constexpr static uint32_t ARRAY_SIZE = WIDTH_TO_BYTES*HIGHT;

	constexpr static uint32_t LO = 0x7F;
	constexpr static uint32_t HI = 0xFF;
	constexpr static uint8_t RED_SHIFT = 0;
	constexpr static uint8_t GREEN_SHIFT = 8;
	constexpr static uint8_t BLUE_SHIFT = 16;

	union HL_t {
		uint16_t m_HL;
		struct {
			uint8_t m_L;
			uint8_t m_H;
		};
	};

	SDL_Surface * m_Surface = nullptr;
	std::array<uint8_t, ARRAY_SIZE> m_PixelData{};
	uint8_t m_Acc = 0, m_B = 0, m_C = 0, m_D = 0, m_E = 0;
	bool m_Carry = false;
	HL_t m_PixelAddr = {};
	std::stack<uint8_t, std::deque<uint8_t>> m_Stack;

	void deinit();
	uint8_t getPixel0(uint8_t pixel) const;
	uint8_t getPixel1(uint8_t pixel) const;
	uint32_t toPixel(uint8_t pix_data) const;
	void copyToSurface();

	void RRC();
	void RLC();
	void RAR();
	void RAL();
	void ACI(uint8_t data);
	void ANA(uint8_t reg);
	void ANI(uint8_t data);
	void ADD(uint8_t reg);
	void SUB(uint8_t reg);
	void LXI_DE_CLER();
	void MOV_INDX_HL_A(uint8_t reg);
	void CMA();
	void INR(uint8_t &reg);
	void DCR(uint8_t &reg);
	void push(uint8_t reg);
	uint8_t pop();

	void loop();
	void subroutine();
};

#endif /* KALEIDOSCOPE_HPP_ */

/*
 * Kaleidoscope.cpp
 *
 *  Created on: Oct 11, 2021
 *      Author: stanimir
 */

#include "Kaleidoscope.hpp"

#include <cassert>
#include <iostream>

#include "sdl_utils/Texture.hpp"

#include "utils/drawing/Rectangle.hpp"

std::int32_t Kaleidoscope::init() {
    Texture::RGB_SurfaceCfg_t rgb_cfg = {
    	.Flags = 0,
    	.W = WIDTH,
    	.H = HIGHT,
    	.D = 32,
    	.R_Mask = 0,
    	.G_Mask = 0,
    	.B_Mask = 0,
    	.A_Mask = 0,
    };
    m_Surface = Texture::createRGB_Surface(rgb_cfg);
	if(nullptr == m_Surface) {
		std::cerr << "Texture::createRGB_Surface." << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void Kaleidoscope::deinit() {
	Texture::freeSurface(m_Surface);
}

std::int32_t Kaleidoscope::update() {
#if 0
	uint8_t pix_data = 0x11;
	uint32_t count = 0;
	for(auto &e : m_PixelData) {
		if(512 == count) {
			pix_data = 0xAA;
		} else if ((512*2) == count) {
			pix_data = 0xCC;
		} else if ((512*3) == count) {
			pix_data = 0xFF;
		}
		e = pix_data;
		++count;
	}
#else
	loop();
#endif
	copyToSurface();
	return EXIT_SUCCESS;
}

void Kaleidoscope::loop() {
    m_Acc = m_B;
    RRC();
    RRC();
    ANA(m_D);
    ADD(m_C);
    m_C = m_Acc;
    RRC();
    RRC();
    ANA(m_D);
    m_PixelAddr.m_L = m_Acc;
    m_Acc = m_B;
    SUB(m_PixelAddr.m_L);
    m_B = m_Acc;
    push(m_B);
    push(m_C);
    push(m_D);
    push(m_E);
    push(m_PixelAddr.m_L);
    push(m_PixelAddr.m_H);
    LXI_DE_CLER();
    m_Acc = m_PixelAddr.m_H;
    ANI(0x1F);
    RAR();
    if(!m_Carry) {
    	m_E = m_Acc;
        RLC();
        RLC();
        RLC();
        RLC();
        m_D = m_Acc;
    }
    m_PixelAddr.m_H = 0x06;
    subroutine();
    m_Acc = m_B;
    CMA();
    m_B = m_Acc;
    m_PixelAddr.m_H = 0x04;
    subroutine();
    m_Acc = m_C;
    CMA();
    m_C = m_Acc;
    m_PixelAddr.m_H = 0x00;
    subroutine();
    m_Acc = m_B;
    CMA();
    m_B = m_Acc;
    m_PixelAddr.m_H = 0x02;
    subroutine();
    m_PixelAddr.m_H = pop();
    m_PixelAddr.m_L = pop();
    m_E = pop();
    m_D = pop();
    m_C = pop();
    m_B = pop();
    DCR(m_E);
    if(m_E) {
    	return;
    }
    INR(m_B);
    INR(m_C);
    m_E = 0x3F;
    DCR(m_PixelAddr.m_H);
    if(m_PixelAddr.m_H) {
    	return;
    }
    INR(m_D);
    m_PixelAddr.m_H = 0x1F;
}

void Kaleidoscope::subroutine() {
    m_Acc = m_C;
    ANI(0xF8);
    RAL();
    m_PixelAddr.m_L = m_Acc;
    m_Acc = m_PixelAddr.m_H;
    ACI(0);
    m_PixelAddr.m_H = m_Acc;
    m_Acc= m_B;
    ANI(0xF8);
    RAR();
    RAR();
    RAR();
    RAR();
    push(static_cast<uint8_t>(m_Carry));
    ADD(m_PixelAddr.m_L);
    m_PixelAddr.m_L = m_Acc;
    m_Carry = pop();
	assert(ARRAY_SIZE > m_PixelAddr.m_HL);
	m_Acc = m_PixelData[m_PixelAddr.m_HL];
    if(m_Carry) {
        ANI(0x0F);
        ADD(m_D);
    } else {
        ANI(0xF0);
        ADD(m_E);
    }
    MOV_INDX_HL_A(m_Acc);
}

void Kaleidoscope::RRC() {
	m_Carry = m_Acc & 0x01;
	m_Acc = static_cast<uint8_t>(m_Acc >> 1);
	m_Acc = static_cast<uint8_t>(m_Acc | (m_Carry?0x80:0));
}

void Kaleidoscope::RLC() {
	m_Carry = m_Acc & 0x80;
	m_Acc = static_cast<uint8_t>(m_Acc << 1);
	m_Acc = static_cast<uint8_t>(m_Acc | (m_Carry?0x01:0));
}

void Kaleidoscope::RAR() {
	uint8_t carry = m_Acc & 0x01;
	m_Acc = static_cast<uint8_t>(m_Acc >> 1);
	m_Acc = static_cast<uint8_t>(m_Acc | (m_Carry?0x80:0));
	m_Carry = carry;
}

void Kaleidoscope::RAL() {
	uint8_t carry = m_Acc & 0x80;
	m_Acc = static_cast<uint8_t>(m_Acc << 1);
	m_Acc = static_cast<uint8_t>(m_Acc | (m_Carry?0x01:0));
	m_Carry = carry;
}

void Kaleidoscope::ACI(uint8_t data) {
	int tmp = m_Acc;
	tmp += data + m_Carry;
	m_Acc = static_cast<uint8_t>(tmp  & 0xFF);
	m_Carry = m_Acc != tmp;
}

void Kaleidoscope::ANA(uint8_t reg) {
	ANI(reg);
}

void Kaleidoscope::ANI(uint8_t data) {
	m_Acc &= data;
	m_Carry = false;
}

void Kaleidoscope::ADD(uint8_t reg) {
	int tmp = m_Acc;
	tmp += reg;
	m_Acc = static_cast<uint8_t>(tmp & 0xFF);
	m_Carry = m_Acc != tmp;
}

void Kaleidoscope::SUB(uint8_t reg) {
	m_Acc = static_cast<uint8_t>(m_Acc - reg);
	m_Carry = m_Acc & 0x80;
}

void Kaleidoscope::LXI_DE_CLER() {
	m_D = m_E = 0;
}

void Kaleidoscope::MOV_INDX_HL_A(uint8_t reg) {
	assert(ARRAY_SIZE > m_PixelAddr.m_HL);
	m_PixelData[m_PixelAddr.m_HL] = reg;
}

void Kaleidoscope::CMA() {
	m_Acc = static_cast<uint8_t>(~m_Acc);
}

void Kaleidoscope::INR(uint8_t &reg) {
	++reg;
}

void Kaleidoscope::DCR(uint8_t &reg) {
	--reg;
}

void Kaleidoscope::push(uint8_t reg) {
	m_Stack.push(reg);
}

uint8_t Kaleidoscope::pop() {
	uint8_t rc = m_Stack.top();
	m_Stack.pop();
	return rc;
}

void Kaleidoscope::copyToSurface() {
	std::uint32_t * p_pix_data = reinterpret_cast<uint32_t*>(Texture::getSurfacePixelData(m_Surface));
	assert(p_pix_data);
	uint32_t pixel_cnt = 0;
	uint32_t row = 0;
	uint32_t col = 0;
	for(const auto e : m_PixelData) {
		if(512 > pixel_cnt) {
			if((WIDTH_TO_BYTES/2) <= row) {
				row = 0;
				++col;
			}
			int offset = (col*WIDTH_TO_BYTES + row)*2;
			p_pix_data[offset++] = toPixel(getPixel0(e));
			p_pix_data[offset++] = toPixel(getPixel1(e));
			++row;
			if((512-1) == pixel_cnt) {
				col = 0;
				row = WIDTH_TO_BYTES/2;
			}
		} else if ((512*2) > pixel_cnt) {
			if((WIDTH_TO_BYTES) <= row) {
				row = WIDTH_TO_BYTES/2;
				++col;
			}
			int offset = (col*WIDTH_TO_BYTES + row)*2;
			p_pix_data[offset++] = toPixel(getPixel0(e));
			p_pix_data[offset++] = toPixel(getPixel1(e));
			++row;
			if((512*2-1) == pixel_cnt) {
				col = HIGHT/2;
				row = 0;
			}
		} else if ((512*3) > pixel_cnt) {
			if((WIDTH_TO_BYTES/2) <= row) {
				row = 0;
				++col;
			}
			int offset = (col*WIDTH_TO_BYTES + row)*2;
			p_pix_data[offset++] = toPixel(getPixel0(e));
			p_pix_data[offset++] = toPixel(getPixel1(e));
			++row;
			if((512*3-1) == pixel_cnt) {
				col = HIGHT/2;
				row = WIDTH_TO_BYTES/2;
			}
		} else if ((512*4) > pixel_cnt){
			if((WIDTH_TO_BYTES) <= row) {
				row = WIDTH_TO_BYTES/2;
				++col;
			}
			int offset = (col*WIDTH_TO_BYTES + row)*2;
			p_pix_data[offset++] = toPixel(getPixel0(e));
			p_pix_data[offset++] = toPixel(getPixel1(e));
			++row;
		}
		++pixel_cnt;
		assert(ARRAY_SIZE >= pixel_cnt);
	}
}

uint8_t Kaleidoscope::getPixel0(uint8_t pixel) const {
	return pixel & 0xF;
}

uint8_t Kaleidoscope::getPixel1(uint8_t pixel) const {
	return (pixel >> 4) & 0xF;
}

uint32_t Kaleidoscope::toPixel(uint8_t pix_data) const {
	uint32_t rc = 0;
	auto intersity = LO;
	if(0x08 & pix_data) {
		intersity = HI;
	}
	if(1 & pix_data) {
		rc |= intersity;
	}
	if(2 & pix_data) {
		rc |= intersity << 8;
	}
	if(4 & pix_data) {
		rc |= intersity << 16;
	}
	return rc;
}


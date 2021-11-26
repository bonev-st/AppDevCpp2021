/*
 * RAII_Handler.hpp
 *
 *  Created on: Nov 13, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INC_UTILS_RAII_HANDLER_HPP_
#define UTILS_INC_UTILS_RAII_HANDLER_HPP_

#include <cassert>

template<class T, T INVALID, class DELETER>
class RAII_Handler {
public:
	RAII_Handler() = default;
	~RAII_Handler();

	RAII_Handler(const RAII_Handler& obj) = delete;
	RAII_Handler& operator = (const RAII_Handler& obj) = delete;

	RAII_Handler(RAII_Handler&& obj);
	RAII_Handler& operator = (RAII_Handler&& obj);

	operator T () const;
	void set(T handler, const DELETER& deleter);
	void reset();

private:
	T m_Val = INVALID;
	DELETER m_Deleter;
	void del();
};

template<class T, T INVALID, class DELETER>
RAII_Handler<T, INVALID, DELETER>::~RAII_Handler() {
	del();
}


template<class T, T INVALID, class DELETER>
RAII_Handler<T, INVALID, DELETER>::RAII_Handler(RAII_Handler&& obj) {
	assert(obj.m_Deleter);
#if 0
		m_Val = obj.m_Val;
		obj.m_Val = INVALID;
		m_Deleter = obj.m_Deleter;
#else
		std::swap(m_Val, obj.m_Val);
		std::swap(m_Deleter, obj.m_Deleter);
#endif
}

template<class T, T INVALID, class DELETER>
RAII_Handler<T, INVALID, DELETER>& RAII_Handler<T, INVALID, DELETER>::operator = (RAII_Handler&& obj) {
	if(&obj != this) {
		del();
		assert(obj.m_Deleter);
#if 0
		m_Val = obj.m_Val;
		obj.m_Val = INVALID;
		m_Deleter = obj.m_Deleter;
#else
		std::swap(m_Val, obj.m_Val);
		std::swap(m_Deleter, obj.m_Deleter);
#endif
	}
	return *this;
}

template<class T, T INVALID, class DELETER>
RAII_Handler<T, INVALID, DELETER>::operator T () const {
	return m_Val;
}

template<class T, T INVALID, class DELETER>
void RAII_Handler<T, INVALID, DELETER>::set(T handler, const DELETER& deleter) {
	assert(deleter);
	del();
	m_Val = handler;
	m_Deleter = deleter;
}

template<class T, T INVALID, class DELETER>
void RAII_Handler<T, INVALID, DELETER>::reset() {
	del();
}

template<class T, T INVALID, class DELETER>
void RAII_Handler<T, INVALID, DELETER>::del() {
	if(INVALID != m_Val) {
		assert(m_Deleter);
		m_Deleter(m_Val);
		m_Val = INVALID;
	}
}

#endif /* UTILS_INC_UTILS_RAII_HANDLER_HPP_ */

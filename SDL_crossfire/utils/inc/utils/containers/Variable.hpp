/*
 * Variable.hpp
 *
 *  Created on: Dec 5, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INC_UTILS_CONTAINERS_VARIABLE_HPP_
#define UTILS_INC_UTILS_CONTAINERS_VARIABLE_HPP_

#include <functional>

template<class T>
class Variable {
public:
	using Callback_t = std::function<void(const T & val)>;

	Variable() = default;
	Variable(T val);

	void attach(const Callback_t &cb);

	const T & operator = (const T & val);
	operator const T& () const;

	const T& operator ++ ();
	const T& operator -- ();

	const T& operator += (const T & val);
	const T& operator -= (const T & val);

private:
	T m_Value;
	Callback_t m_CB;
};

template<class T>
Variable<T>::Variable(T val) : m_Value(val) {
}

template<class T>
void Variable<T>::attach(const Callback_t & cb) {
	m_CB = cb;
}

template<class T>
const T & Variable<T>::operator = (const T & val) {
	if(val != m_Value) {
		m_Value = val;
		if(m_CB) {
			m_CB(m_Value);
		}
	}
	return m_Value;
}

template<class T>
Variable<T>::operator const T& () const {
	return m_Value;
}

template<class T>
const T& Variable<T>::operator ++ () {
	return *this = m_Value + 1;
}

template<class T>
const T& Variable<T>::operator -- () {
	return *this = m_Value - 1;
}

template<class T>
const T& Variable<T>::operator += (const T & val) {
	return *this = m_Value + val;
}

template<class T>
const T& Variable<T>::operator -= (const T & val) {
	return *this = m_Value - val;
}


#endif /* UTILS_INC_UTILS_CONTAINERS_VARIABLE_HPP_ */

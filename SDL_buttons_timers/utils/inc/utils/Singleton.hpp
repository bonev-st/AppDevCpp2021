/*
 * Singleton.hpp
 *
 *  Created on: Oct 28, 2021
 *      Author: stanimir
 */

#ifndef SINGLETON_HPP_
#define SINGLETON_HPP_

template<class T>
class Singleton {
public:
	static T * getInstance() {
		static T obj;
		return &obj;
	}
};

#endif /* SINGLETON_HPP_ */

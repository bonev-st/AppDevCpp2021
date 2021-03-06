/*
 * Destroy.hpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#ifndef UTILS_DESTROY_DESTROY_HPP_
#define UTILS_DESTROY_DESTROY_HPP_

#include <iostream>
#include <typeinfo>
#include <memory>

namespace Destroy {

template<class T, void(deleter)(T* p)>
void free(T* p) {
	if(p) {
#ifdef SHOW_MEM_ALLOC_INFO
		std::cout << "- Destroy with " << typeid(deleter).name() << "(" << p << ")" << std::endl;
#endif
		deleter(p);
	}
#ifdef SHOW_MEM_ALLOC_INFO
	else {
		std::cout << "- Try to destroy with " << typeid(deleter).name() << "(nullptr)" << std::endl;
	}
#endif
}
}

#endif /* UTILS_DESTROY_DESTROY_HPP_ */

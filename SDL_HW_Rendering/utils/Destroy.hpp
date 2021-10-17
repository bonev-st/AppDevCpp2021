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

template<class T, class DTYPE, DTYPE *T::*M, void(deleter)(DTYPE* p)>
void freeMember(T* p) {
	if(p) {
		if(p->*M) {
#ifdef SHOW_MEM_ALLOC_INFO
		std::cout << "- Destroy with " << typeid(deleter).name() << "(" << p->*M << ")" << std::endl;
#endif
			deleter(p->*M);
		}
#ifdef SHOW_MEM_ALLOC_INFO
		else {
			std::cout << "- Try to destroy with " << typeid(deleter).name() <<  "(nullptr)"  << std::endl;
		}
#endif
		delete p;
#ifdef SHOW_MEM_ALLOC_INFO
		std::cout << "- Destroy with delete " << p << std::endl;
#endif
	}
#ifdef SHOW_MEM_ALLOC_INFO
	else {
		std::cout << "- Try to delete nillptr of " << typeid(T).name() << std::endl;
	}
#endif
}
}

#endif /* UTILS_DESTROY_DESTROY_HPP_ */

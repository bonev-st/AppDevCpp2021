/*
 * Destroy.hpp
 *
 *  Created on: Oct 14, 2021
 *      Author: stanimir
 */

#ifndef UTILS_DESTROY_DESTROY_HPP_
#define UTILS_DESTROY_DESTROY_HPP_

namespace Destroy {

template<class T, void(deleter)(T* p)>
void free(T* p) {
	if(p) {
		deleter(p);
	}
}

}

#endif /* UTILS_DESTROY_DESTROY_HPP_ */

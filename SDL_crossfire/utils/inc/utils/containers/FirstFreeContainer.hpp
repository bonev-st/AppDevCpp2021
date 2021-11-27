/*
 * FirstFreeContainer.hpp
 *
 *  Created on: Oct 23, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INC_UTILS_CONTAINERS_FIRSTFREECONTAINER_HPP_
#define UTILS_INC_UTILS_CONTAINERS_FIRSTFREECONTAINER_HPP_

#include <cassert>
#include <vector>
#include <stack>

template<class T>
class FirstFreeContainer {
	struct Data_t;
public:
	class iterator {
	public:
		iterator(Data_t* obj, Data_t* end) : m_Val(obj), m_End(end) {
		}

		bool operator != (const iterator & other) {
			return other.m_Val != m_Val;
		}

		T& operator *() const {
			return m_Val->m_Val;
		}

		iterator& operator ++() {
			if(m_Val) {
				while(m_End != m_Val) {
					++m_Val;
					if(m_Val->m_Valid) {
						break;
					}
				}
			}
			return *this;
		}

	private:
		Data_t* m_Val = nullptr;
		Data_t* m_End = nullptr;
	};

	const T* get(std::size_t id) const;
	T* get(std::size_t id);
	bool replace(std::size_t id, const T & val);
	bool release(std::size_t id);
	bool release(const T & val);
	std::size_t add(const T & val);
	std::size_t getValid() const;
	std::size_t getMaxValid() const;
	bool empty() const;
	iterator begin();
	iterator end();

private:
	struct Data_t {
		bool m_Valid = false;
		T m_Val;
	};

	std::vector<Data_t> m_Container;
	std::stack<std::size_t, std::vector<std::size_t>> m_Free;

	bool isValid(std::size_t id) const;
};

template<class T>
const T* FirstFreeContainer<T>::get(std::size_t id) const {
	if(!isValid(id)) {
		return nullptr;
	}
	return &m_Container[id].m_Val;
}

template<class T>
T* FirstFreeContainer<T>::get(std::size_t id) {
	if(!isValid(id)) {
		return nullptr;
	}
	return &m_Container[id].m_Val;
}

template<class T>
bool FirstFreeContainer<T>::replace(std::size_t id, const T & val) {
	if(!isValid(id)) {
		return false;
	}
	m_Container[id].m_Val = val;
	return true;
}

template<class T>
bool FirstFreeContainer<T>::release(std::size_t id) {
	if(!isValid(id)) {
		return false;
	}
	m_Container[id].m_Valid = false;
	m_Free.push(id);
	return true;
}

template<class T>
bool FirstFreeContainer<T>::release(const T & val) {
	for(size_t i = 0; m_Container.size() > i; ++i ) {
		if(&val == &m_Container[i].m_Val) {
			return release(i);
		}
	}
	return false;
}

template<class T>
std::size_t FirstFreeContainer<T>::add(const T & val) {
	if(m_Free.empty()) {
		m_Container.push_back(Data_t{.m_Valid = true, .m_Val = val});
		return m_Container.size() - 1;
	}
	auto id = m_Free.top();
	m_Free.pop();
	m_Container[id] = Data_t{.m_Valid = true, .m_Val = val};
	return id;
}

template<class T>
std::size_t FirstFreeContainer<T>::getValid() const {
	assert(m_Container.size() >= m_Free.size());
	return m_Container.size() - m_Free.size();
}

template<class T>
std::size_t FirstFreeContainer<T>::getMaxValid() const {
	return m_Container.size();
}

template<class T>
bool FirstFreeContainer<T>::empty() const {
	 return 0 == getValid();
}

template<class T>
bool FirstFreeContainer<T>::isValid(std::size_t id) const {
	if(m_Container.size() <= id) {
		return false;
	}
	return m_Container[id].m_Valid;
}

template<class T>
typename FirstFreeContainer<T>::iterator FirstFreeContainer<T>::begin() {
	for(auto & e : m_Container) {
		if(e.m_Valid) {
			return iterator(&e, &m_Container.back()+1);
		}
	}
	return iterator(&m_Container.back()+1, &m_Container.back()+1);
}

template<class T>
typename FirstFreeContainer<T>::iterator FirstFreeContainer<T>::end() {
	return iterator(&m_Container.back()+1, &m_Container.back()+1);
}

#endif /* UTILS_INC_UTILS_CONTAINERS_FIRSTFREECONTAINER_HPP_ */

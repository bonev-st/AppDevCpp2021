/*
 * FirstFreeContainer.hpp
 *
 *  Created on: Oct 23, 2021
 *      Author: stanimir
 */

#ifndef UTILS_INC_UTILS_CONTAINERS_FIRSTFREECONTAINER_HPP_
#define UTILS_INC_UTILS_CONTAINERS_FIRSTFREECONTAINER_HPP_

#include <vector>
#include <stack>

template<class T>
class FirstFreeContainer {
public:
	const T* get(std::size_t id) const {
		if(!isValid(id)) {
			return nullptr;
		}
		return &m_Container[id].m_Val;
	}

	bool replace(std::size_t id, const T & val) {
		if(!isValid(id)) {
			return false;
		}
		m_Container[id].m_Val = val;
		return true;
	}

	bool release(std::size_t id) {
		if(!isValid(id)) {
			return false;
		}
		m_Container[id].m_Valid = false;
		m_Free.push(id);
		return true;
	}

	std::size_t add(const T & val) {
		if(m_Free.empty()) {
			m_Container.push_back(Data_t{.m_Valid = true, .m_Val = val});
			return m_Container.size() - 1;
		}
		auto id = m_Free.top();
		m_Free.pop();
		m_Container[id] = Data_t{.m_Valid = true, .m_Val = val};
		return id;
	}

private:
	struct Data_t {
		bool m_Valid = false;
		T m_Val;
	};

	std::vector<Data_t> m_Container;
	std::stack<std::size_t, std::vector<std::size_t>> m_Free;

	bool isValid(std::size_t id) const {
		if(m_Container.size() <= id) {
			return false;
		}
		return m_Container[id].m_Valid;
	}
};

#endif /* UTILS_INC_UTILS_CONTAINERS_FIRSTFREECONTAINER_HPP_ */

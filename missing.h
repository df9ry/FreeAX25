/*
 * missing.h
 *
 *  Created on: 17.05.2015
 *      Author: tania
 */

#ifndef MISSING_H_
#define MISSING_H_

#include <sstream>

// GCC missing std::to_string(x):
template <typename T>
std::string to_string(T value) {
	std::ostringstream os;
	os << value;
	return os.str();
}

#endif /* MISSING_H_ */

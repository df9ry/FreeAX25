/*
 * Utils.h
 *
 *  Created on: 24.04.2015
 *      Author: tania
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>

namespace Utils {

/**
 * Make a string to lower case
 * @param s String to lower case
 * @return Lower case string
 */
std::string toLower(const std::string& s);

/**
 * Test if a string ends with a specific suffix.
 * @param a The string to check
 * @param b The suffix to look for
 * @return True, when a ends with b, false otherwise
 */
bool endsWith(const std::string& a, const std::string& b);

/**
 * Right trim whitespace from string
 * @param s The string to trim
 * @return Trimmed string
 */
inline std::string rtrim(std::string s) {
	s.erase(s.find_last_not_of(" \t\n\r\f\v") + 1);
	return s;
}

/**
 * Left trim whitespace from string
 * @param s The string to trim
 * @return Trimmed string
 */
inline std::string ltrim(std::string s) {
	s.erase(s.find_first_not_of(" \t\n\r\f\v"));
	return s;
}

/**
 * Trim left and right whitespace from string
 * @param s The string to trim
 * @return Trimmed string
 */
inline std::string trim(std::string s) {
	return ltrim(rtrim(s));
}

} /* namespace Utils */

#endif /* UTILS_H_ */

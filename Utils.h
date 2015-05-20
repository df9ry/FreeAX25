/*
    Project FreeAX25
    Copyright (C) 2015  tania@df9ry.de

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
	s.erase(0, s.find_first_not_of(" \t\n\r\f\v"));
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

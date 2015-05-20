/*
 * Utils.cpp
 *
 *  Created on: 24.04.2015
 *      Author: tania
 */

#include <algorithm>

#include "Utils.h"

using namespace std;

namespace Utils {

string toLower(const string& s) {
	string data{s};
	transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}

bool endsWith(const string& a, const string& b) {
    if (b.size() > a.size()) return false;
    return equal(a.begin() + a.size() - b.size(), a.end(), b.begin());
}

} /* namespace Utils */

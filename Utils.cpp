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

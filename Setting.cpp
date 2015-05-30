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

#include "Setting.h"

namespace FreeAX25 {

const std::string Setting::asString(
		Map<Setting>& map, const std::string& key, const std::string def)
{
	const Setting* s = map.findAndGet(key);
	return (s != nullptr) ? s->asString() : def;
}

int Setting::asInt(
		Map<Setting>& map, const std::string& key, const int def)
{
	const Setting* s = map.findAndGet(key);
	return (s != nullptr) ? s->asInt() : def;
}

} /* namespace FreeAX25 */

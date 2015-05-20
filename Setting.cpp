/*
 * Setting.cpp
 *
 *  Created on: 19.05.2015
 *      Author: tania
 */

#include "Setting.h"

namespace FreeAX25 {

const std::string Setting::asString(
		Map<Setting>& map, const std::string& key, const std::string def)
{
	Setting* s = map.find(key);
	return (s != nullptr) ? s->asString() : def;
}

int Setting::asInt(
		Map<Setting>& map, const std::string& key, const int def)
{
	Setting* s = map.find(key);
	return (s != nullptr) ? s->asInt() : def;
}

} /* namespace FreeAX25 */

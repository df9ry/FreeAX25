/*
 * Configuration.cpp
 *
 *  Created on: 18.05.2015
 *      Author: tania
 */

#include "Configuration.h"
#include "Environment.h"

namespace FreeAX25 {

Configuration::Configuration(Environment* e): m_environment{e} {
}

Configuration::~Configuration() {
}

} /* namespace FreeAX25 */

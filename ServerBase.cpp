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

#include "ServerBase.h"
#include "ServerProxy.h"
#include "Environment.h"

#include "JsonXObject.h"

#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;
using namespace JsonX;

namespace FreeAX25 {

class ClientProxy;

ServerBase::ServerBase(): m_proxy(this) {
	environment.logDebug("Constructor on ServerBase: " + to_string((uint64_t)this));
}

ServerBase::~ServerBase() {
	environment.logDebug("Destructor on ServerBase: " + to_string((uint64_t)this));
}

ServerProxy ServerBase::onConnect(JsonX::JsonXValue&& parameter, ServerProxy&& downlink) {
	throw logic_error("Unsupported service: connect");
}

void ServerBase::onOpen(JsonX::JsonXValue&& parameter) {
	throw logic_error("Unsupported service: open");
}

void ServerBase::onClose(JsonX::JsonXValue&& parameter) {
	throw logic_error("Unsupported service: close");
}

void ServerBase::onReceive(JsonX::JsonXValue&& message, MessagePriority priority) {
	throw logic_error("Unsupported service: send");
}

JsonX::JsonXValue ServerBase::onCtrl(JsonX::JsonXValue&& request) {
	throw logic_error("Unsupported service: control");
}

ServerProxy ServerBase::getServerProxy() {
	return m_proxy;
}

void ServerBase::_release() {
	m_proxy = ServerProxy();
}

} /* namespace JsonX */

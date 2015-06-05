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

#include "UniquePointerDict"
#include "SharedPointerDict"
#include "Null.h"
#include "Instance.h"
#include "Environment.h"
#include "ServerProxy.h"
#include "Plugin.h"

#include <stdexcept>
#include <cassert>

using namespace std;

namespace FreeAX25 {

// The one and only instance
static Null* instance{nullptr};

void initNull(Plugin& p) {
	environment.logInfo("Init plugin \"_NULL\"");
	if (instance != nullptr) throw runtime_error(
			"Null already instantiated");
	instance = new Null();
	instance->init(p);
}

void startNull() {
	environment.logInfo("Start plugin \"_NULL\"");
	if (instance == nullptr) throw runtime_error(
			"Null not instantiated");
	instance->start();
}

Null::Null() {
	if (instance != nullptr) throw runtime_error(
			"Null already instantiated");
	instance = this;
}

Null::~Null() {
	cerr << "Destroying Null !!!" << endl;
}

void Null::init(Plugin& p) {
	environment.logInfo("Init plugin \"" + p.getName() + "\"");
	// Build instances:
	for (UniquePointerDictConstIterator<Instance> ii = p.instances.begin();
			ii != p.instances.end(); ++ii)
	{
		const Instance* i = ii->second.get();
		for (UniquePointerDictConstIterator<ServerEndPoint> sepi = i->serverEndPoints.begin();
				sepi != i->serverEndPoints.end(); ++sepi) {
			const ServerEndPoint* sep = sepi->second.get();
			assert(sep != nullptr);
			const string url = sep->getUrl();
			environment.logInfo("Register service at: " + sep->getUrl());
			environment.serverProxies.insertMove(sep->getUrl(), getServerProxy());
		}
	}
}

void Null::start() {
}

ServerProxy Null::onConnect(JsonX::JsonXValue&& parameter, ServerProxy&& downlink) {
	cerr << "Null connect called. I am: " << hex << (uint64_t)this << endl;
	return getServerProxy();
}

void Null::onOpen(JsonX::JsonXValue&& parameter) {
	cerr << "Null open called. I am: " << hex << (uint64_t)this << endl;
}

void Null::onClose(JsonX::JsonXValue&& parameter) {
	cerr << "Null close called. I am: " << hex << (uint64_t)this << endl;
}

void Null::onReceive(JsonX::JsonXValue&& message, MessagePriority priority) {
	cerr << "Null send called. I am: " << hex << (uint64_t)this << endl;
}

JsonX::JsonXValue Null::onCtrl(JsonX::JsonXValue&& request) {
	cerr << "Null ctrl called. I am: " << hex << (uint64_t)this << endl;
	return JsonX::JsonXValue{};
}

} /* namespace FreeAX25 */

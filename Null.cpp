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

void initNull(const Plugin& p) {
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
	environment.logError("Destructor called on NULL session " + to_string((uint64_t)this));
}

void Null::init(const Plugin& p) {
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
	environment.logDebug("Download connect on NULL session " + to_string((uint64_t)this));
	return getServerProxy();
}

void Null::onOpen(JsonX::JsonXValue&& parameter) {
	environment.logDebug("Download open on NULL session " + to_string((uint64_t)this));
}

void Null::onClose(JsonX::JsonXValue&& parameter) {
	environment.logDebug("Download close on NULL session " + to_string((uint64_t)this));
}

void Null::onReceive(JsonX::JsonXValue&& message, MessagePriority priority) {
	environment.logDebug("Download message on NULL session " + to_string((uint64_t)this));
}

JsonX::JsonXValue Null::onCtrl(JsonX::JsonXValue&& request) {
	environment.logDebug("Download control on NULL session " + to_string((uint64_t)this));
	return JsonX::JsonXValue{};
}

} /* namespace FreeAX25 */

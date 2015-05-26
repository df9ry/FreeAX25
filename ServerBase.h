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

#ifndef SERVERBASE_H_
#define SERVERBASE_H_

#include "ClientProxy.h"

#include <memory>

namespace FreeAX25 {

class ServerProxy;

/**
 * All servers have to derive from this class
 */
class ServerBase {
	friend class ServerProxy;

public:

	/**
	 * Constructor.
	 */
	ServerBase();

	/**
	 * Destructor.
	 */
	virtual ~ServerBase();

protected:
	virtual ClientProxy&& onConnect(JsonX::JsonXObject& parameter, ClientProxy&& downlink);
	virtual ClientProxy&& onConnect(JsonX::JsonXObject& parameter);
	virtual void onOpen(JsonX::JsonXObject& parameter);
	virtual void onClose(JsonX::JsonXObject& parameter);
	virtual void onReceive(JsonX::JsonXObject&& message, MessagePriority priority);
	virtual JsonX::JsonXObject&& onCtrl(JsonX::JsonXObject& request);

	ClientProxy&& newClientProxy();

private:
	std::shared_ptr<ServerProxy> serverProxy;
};

} /* namespace JsonX */

#endif /* SERVERBASE_H_ */

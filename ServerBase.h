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

#include "JsonXValue.h"
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

	/**
	 * Get a ServerProxy for this server.
	 * @return Unique pointer to new ServerProxy.
	 */
	std::unique_ptr<ServerProxy> getServerProxy();

protected:
	virtual std::unique_ptr<ClientProxy> onConnect(
			std::unique_ptr<JsonX::JsonXValue>&& parameter,
			std::unique_ptr<ClientProxy>&& downlink);

	virtual std::unique_ptr<ClientProxy> onConnect(
			std::unique_ptr<JsonX::JsonXValue>&& parameter);

	virtual void onOpen(
			std::unique_ptr<JsonX::JsonXValue>&& parameter);

	virtual void onClose(
			std::unique_ptr<JsonX::JsonXValue>&& parameter);

	virtual void onReceive(
			std::unique_ptr<JsonX::JsonXValue>&& message,
			MessagePriority priority);

	virtual std::unique_ptr<JsonX::JsonXValue> onCtrl(
			std::unique_ptr<JsonX::JsonXValue>&& request);
};

} /* namespace FreeAX25 */

#endif /* SERVERBASE_H_ */

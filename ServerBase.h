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
#include "ServerProxy.h"

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
	 * You can not copy a server.
	 * @param other Not used.
	 */
	ServerBase(const ServerBase& other) = delete;

	/**
	 * You can not move a server.
	 * @param other Not used.
	 */
	ServerBase(ServerBase&& other) = delete;

	/**
	 * Destructor.
	 */
	virtual ~ServerBase();

	/**
	 * You can  not assign a server.
	 * @param other Not used.
	 * @return Not used.
	 */
	ServerBase& operator=(const ServerBase& other) = delete;

	/**
	 * You can  not assign a server.
	 * @param other Not used.
	 * @return Not used.
	 */
	ServerBase& operator=(ServerBase&& other) = delete;

	/**
	 * Get a ServerProxy for this server.
	 * @return ServerProxy for this server.
	 */
	ServerProxy getServerProxy();

protected:
	virtual ServerProxy onConnect(JsonX::JsonXValue&& parameter, ServerProxy&& downlink);

	virtual void onOpen(JsonX::JsonXValue&& parameter);

	virtual void onClose(JsonX::JsonXValue&& parameter);

	virtual void onReceive(JsonX::JsonXValue&& message, MessagePriority priority);

	virtual JsonX::JsonXValue onCtrl(JsonX::JsonXValue&& request);

	void _release();

private:
	ServerProxy m_proxy;
};

} /* namespace FreeAX25 */

#endif /* SERVERBASE_H_ */

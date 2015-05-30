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

#ifndef SERVERPROXY_H_
#define SERVERPROXY_H_

#include "ClientProxy.h"
#include "JsonXValue.h"

#include <memory>

namespace FreeAX25 {

class ServerBase;

/**
 * ServerProxies can be used to publish servers. If all
 * ServerProxies are deleted then the server will be
 * deleted.
 */
class ServerProxy {
	friend class ServerBase;
	friend class ClientProxy;

public:
	/**
	 * Default constructor.
	 */
	ServerProxy();

	/**
	 * Copy constructor is deleted.
	 * @param other Not used
	 */
	ServerProxy(const ServerProxy& other) = delete;

	/**
	 * Move constructor.
	 * @param other Move source.
	 */
	ServerProxy(ServerProxy&& other);

	/**
	 * Copy assignment is deleted.
	 * @param other Not used.
	 * @return Not used.
	 */
	ServerProxy& operator=(const ServerProxy& other) = delete;

	/**
	 * Move assignment.
	 * @param other Source object.
	 * @return Reference to target object.
	 */
	ServerProxy& operator=(ServerProxy&& other);

	/**
	 * Get a ClientProxy for the server.
	 * @return Unique pointer to ClientProxy.
	 */
	std::unique_ptr<ClientProxy> getClientProxy();

	/**
	 * Destructor.
	 */
	~ServerProxy();

private:
	ServerProxy(ServerBase* server);

	std::unique_ptr<ClientProxy> connect(
			std::unique_ptr<JsonX::JsonXValue>&& parameter,
			std::unique_ptr<ClientProxy>&& downlink);

	std::unique_ptr<ClientProxy> connect(
			std::unique_ptr<JsonX::JsonXValue>&& parameter);

	void open(
			std::unique_ptr<JsonX::JsonXValue>&& parameter);

	void close(
			std::unique_ptr<JsonX::JsonXValue>&& parameter);

	void send(
			std::unique_ptr<JsonX::JsonXValue>&& message,
			MessagePriority priority);

	std::unique_ptr<JsonX::JsonXValue> ctrl(
			std::unique_ptr<JsonX::JsonXValue>&& request);

	void kill();

	std::shared_ptr<ServerBase> m_server;
};

} // end namespace FreeAX25 //

#endif /* SERVERPROXY_H_ */

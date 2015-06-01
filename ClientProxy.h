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

#ifndef CLIENTPROXY_H_
#define CLIENTPROXY_H_

#include "JsonXValue.h"

#include <memory>

namespace FreeAX25 {

class ServerProxy;

enum class ClientProxyState;

/**
 * Priority a message should have.
 */
enum class MessagePriority {
	ROUTINE,//!< ROUTINE  Message will be forwarded regulary
	PRIORITY//!< PRIORITY Message will be forwarded with priority
};

/**
 * Interface to a server.
 */
class ClientProxy {
	friend class ServerProxy;

public:

	/**
	 * Standard Constructor.
	 */
	ClientProxy();

	/**
	 * Copy constructor is deleted.
	 * @param other Not used
	 */
	ClientProxy(const ClientProxy& other) = delete;

	/**
	 * Move constructor.
	 * @param other Move source.
	 */
	ClientProxy(ClientProxy&& other);

	/**
	 * Copy assignment is deleted.
	 * @param other Not used.
	 * @return Not used.
	 */
	ClientProxy& operator=(const ClientProxy& other) = delete;

	/**
	 * Move assignment.
	 * @param other Source object.
	 * @return Reference to target object.
	 */
	ClientProxy& operator=(ClientProxy&& other);

	/**
	 * Destructor.
	 */
	~ClientProxy();

	/**
	 * Connect to server for a bidirectional conversation.
	 * @param parameter Parameter to specify connection details.
	 *                  The server may move out parts of this parameters!
	 * @param downlink Proxy to your downlink server.
	 * @return Proxy to uplink.
	 */
	ClientProxy connect(JsonX::JsonXValue&& parameter, ClientProxy&& downlink);

	/**
	 * Connect to server for a bidirectional conversation.
	 * @param downlink Proxy to your downlink server.
	 * @return Proxy to uplink.
	 */
	ClientProxy connect(ClientProxy&& downlink);

	/**
	 * Connect to server for a unidirectional conversation.
	 * @param parameter Parameter to specify connection details.
	 *                  The server may move out parts of this parameters!
	 * @return Proxy to uplink.
	 */
	ClientProxy connect(JsonX::JsonXValue&& parameter);

	/**
	 * Connect to server for a unidirectional conversation.
	 * @return Proxy to uplink.
	 */
	ClientProxy connect();

	/**
	 * Start service. Do not send anything before calling this method.
	 * @param parameter Parameter to specify start details.
	 *                  The server may move out parts of this parameters!
	 */
	void open(JsonX::JsonXValue&& parameter);

	/**
	 * Start service. Do not send anything before calling this method.
	 */
	void open();

	/**
	 * Detach from service. Do not send anything after calling this method.
	 * @param parameter Parameter to specify start details.
	 *                  The server may move out parts of this parameters!
	 */
	void close(JsonX::JsonXValue&& parameter);

	/**
	 * Detach from service. Do not send anything after calling this method.
	 */
	void close();

	/**
	 * Send data to the server asynchronously.
	 * @param message Data to send
	 * @param priority Message priority
	 */
	void send(JsonX::JsonXValue&& message, MessagePriority priority = MessagePriority::ROUTINE);

	/**
	 * Send control request synchronously to the server.
	 * @param request The request to send
	 * @return The response from the server
	 */
	JsonX::JsonXValue ctrl(JsonX::JsonXValue&& request);

private:
	/**
	 * Private constructor. Can only created by a server.
	 */
	ClientProxy(ServerProxy* serverProxy);

	std::shared_ptr<ServerProxy> m_serverProxy;
	ClientProxyState             m_state;
};

} /* namespace FreeAX25 */

#endif /* CLIENTPROXY_H_ */

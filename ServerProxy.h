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

#include "JsonXValue.h"

#include <memory>

namespace FreeAX25 {

/**
 * Message priority.
 */
enum class MessagePriority {
	ROUTINE,//!< ROUTINE  Routine delivery
	PRIORITY//!< PRIORITY Express delivery
};

class ServerBase;

/**
 * ServerProxies can be used to publish servers. If all
 * ServerProxies are deleted then the server will be
 * deleted.
 */
class ServerProxy {
	friend class ServerBase;

public:
	/**
	 * Default constructor.
	 */
	ServerProxy();

	/**
	 * Copy constructor.
	 * @param other The Server proxy to copy from.
	 */
	ServerProxy(const ServerProxy& other);

	/**
	 * Copy assignment.
	 * @param other The ServerProxy to copy from.
	 * @return Copied ServerProxy.
	 */
	ServerProxy& operator=(const ServerProxy& other);

	/**
	 * Move constructor.
	 * @param other The ServerProxy to move from.
	 */
	ServerProxy(ServerProxy&& other);

	/**
	 * Move assignment.
	 * @param other The ServerProxy to move from.
	 * @return Moved ServerProxy.
	 */
	ServerProxy& operator=(ServerProxy&& other);

	/**
	 * Test if the server proxy is set.
	 */
	explicit operator bool() const noexcept { return m_server.get(); }

	/**
	 * Destructor.
	 */
	~ServerProxy();

	/**
	 * Connect to the server.
	 * @param parameter Parameter for connect.
	 * @param downlink ServerProxy for downlink.
	 * @return ServerProxy. This is not necessary a proxy to the same server where
	 *         this call is placed on. The target server may return a server dedicated
	 *         for this client directly.
	 */
	ServerProxy connect(JsonX::JsonXValue&& parameter, ServerProxy&& downlink);

	/**
	 * Connect to the server.
	 * @param downlink ServerProxy for downlink.
	 * @return ServerProxy. This is not necessary a proxy to the same server where
	 *         this call is placed on. The target server may return a server dedicated
	 *         for this client directly.
	 */
	ServerProxy connect(ServerProxy&& downlink) {
		return connect(JsonX::JsonXValue(), std::move(downlink));
	}

	/**
	 * Connect to the server.
	 * @param parameter Parameter for connect.
	 * @return ServerProxy. This is not necessary a proxy to the same server where
	 *         this call is placed on. The target server may return a server dedicated
	 *         for this client directly.
	 */
	ServerProxy connect(JsonX::JsonXValue&& parameter) {
		return connect(std::move(parameter), ServerProxy());
	}

	/**
	 * Connect to the server.
	 * @param parameter Parameter for connect.
	 * @return ServerProxy. This is not necessary a proxy to the same server where
	 *         this call is placed on. The target server may return a server dedicated
	 *         for this client directly.
	 */
	ServerProxy connect() {
		return connect(JsonX::JsonXValue(), ServerProxy());
	}

	/**
	 * Open connection to server. This should be the first call to the server after
	 * a connect.
	 * @param parameter Parameter for open.
	 */
	void open(JsonX::JsonXValue&& parameter);

	/**
	 * Open connection to server. This should be the first call to the server after
	 * a connect.
	 */
	void open() {
		open(JsonX::JsonXValue());
	}

	/**
	 * Close connection to server. This should be the last call to this server.
	 * @param parameter Parameter for close.
	 */
	void close(JsonX::JsonXValue&& parameter);

	/**
	 * Close connection to server. This should be the last call to this server.
	 */
	void close() {
		close(JsonX::JsonXValue());
	}

	/**
	 * Send a message to the server.
	 * @param message Message to send.
	 * @param priority Message priority.
	 */
	void send(JsonX::JsonXValue&& message, MessagePriority priority = MessagePriority::ROUTINE);

	/**
	 * Send a request to the server.
	 * @param request Request to send.
	 * @return Response from server.
	 */
	JsonX::JsonXValue ctrl(JsonX::JsonXValue&& request);

	/**
	 * Get numerical address of the underlying server. For debugging purposes.
	 * @return Numerical address of the underlying server.
	 */
	uint64_t serverAddr() const { return (uint64_t)m_server.get(); }

private:
	ServerProxy(ServerBase* server);
	void reset();
	::std::shared_ptr<ServerBase> m_server;
};

} // end namespace FreeAX25 //

#endif /* SERVERPROXY_H_ */

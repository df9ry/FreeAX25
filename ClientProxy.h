/*
 * ClientProxy.h
 *
 *  Created on: 26.05.2015
 *      Author: tania
 */

#ifndef CLIENTPROXY_H_
#define CLIENTPROXY_H_

#include "JsonXObject.h"

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
	 * Connect to server for a bidirectional conversation.
	 * @param parameter Parameter to specify connection details.
	 *                  The server may move out parts of this parameters!
	 * @param downlink Proxy to your downlink server.
	 * @return Proxy to uplink.
	 */
	ClientProxy&& connect(JsonX::JsonXObject& parameter, ClientProxy&& downlink);

	/**
	 * Connect to server for a bidirectional conversation.
	 * @param downlink Proxy to your downlink server.
	 * @return Proxy to uplink.
	 */
	ClientProxy&& connect(ClientProxy&& downlink);

	/**
	 * Connect to server for a unidirectional conversation.
	 * @param parameter Parameter to specify connection details.
	 *                  The server may move out parts of this parameters!
	 * @return Proxy to uplink.
	 */
	ClientProxy&& connect(JsonX::JsonXObject& parameter);

	/**
	 * Connect to server for a unidirectional conversation.
	 * @return Proxy to uplink.
	 */
	ClientProxy&& connect();

	/**
	 * Start service. Do not send anything before calling this method.
	 * @param parameter Parameter to specify start details.
	 *                  The server may move out parts of this parameters!
	 */
	void open(JsonX::JsonXObject& parameter);

	/**
	 * Start service. Do not send anything before calling this method.
	 */
	void open();

	/**
	 * Detach from service. Do not send anything after calling this method.
	 * @param parameter Parameter to specify start details.
	 *                  The server may move out parts of this parameters!
	 */
	void close(JsonX::JsonXObject& parameter);

	/**
	 * Detach from service. Do not send anything after calling this method.
	 */
	void close();

	/**
	 * Send data to the server asynchronously.
	 * @param message Data to send
	 * @param priority Message priority
	 */
	void send(JsonX::JsonXObject&& message, MessagePriority priority = MessagePriority::ROUTINE);

	/**
	 * Send control request synchronously to the server.
	 * @param request The request to send
	 * @return The response from the server
	 */
	JsonX::JsonXObject&& ctrl(JsonX::JsonXObject& request);

	/**
	 * Destructor.
	 */
	~ClientProxy();

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

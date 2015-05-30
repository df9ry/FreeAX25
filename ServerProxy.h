/*
 * ServerProxy.h
 *
 *  Created on: 26.05.2015
 *      Author: tania
 */

#ifndef SERVERPROXY_H_
#define SERVERPROXY_H_

#include "ClientProxy.h"
#include "JsonXObject.h"

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
	ClientProxy* getClientProxy();

private:
	ServerProxy(ServerBase* server);

	ClientProxy&& connect(JsonX::JsonXObject& parameter, ClientProxy&& downlink);
	ClientProxy&& connect(JsonX::JsonXObject& parameter);
	void open(JsonX::JsonXObject& parameter);
	void close(JsonX::JsonXObject& parameter);
	void send(JsonX::JsonXObject&& message, MessagePriority priority);
	JsonX::JsonXObject&& ctrl(JsonX::JsonXObject& request);
	void kill();

	std::shared_ptr<ServerBase> m_server;
};

} // end namespace FreeAX25 //

#endif /* SERVERPROXY_H_ */

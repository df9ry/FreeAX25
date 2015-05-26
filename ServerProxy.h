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

class ServerProxy {
	friend class ServerBase;
	friend class ClientProxy;

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

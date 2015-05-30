/*
 * ServerProxy.cpp
 *
 *  Created on: 26.05.2015
 *      Author: tania
 */

#include "ServerProxy.h"
#include "ServerBase.h"

#include <stdexcept>

using namespace std;
using namespace JsonX;

namespace FreeAX25 {

ServerProxy::ServerProxy():
		m_server{shared_ptr<ServerBase>()}
{
}

ServerProxy::ServerProxy(ServerProxy&& other)
{
	swap(m_server, other.m_server);
}

ServerProxy& ServerProxy::operator=(ServerProxy&& other)
{
	swap(m_server, other.m_server);
	return *this;
}

ServerProxy::ServerProxy(ServerBase* server):
		m_server{shared_ptr<ServerBase>(server)}
{
}

ClientProxy* ServerProxy::getClientProxy() {
	return new ClientProxy(this);
}

ClientProxy&& ServerProxy::connect(JsonXObject& parameter, ClientProxy&& downlink) {
	if (!m_server.get()) throw runtime_error("Server not found");
	return move(m_server.get()->onConnect(parameter, move(downlink)));
}

ClientProxy&& ServerProxy::connect(JsonXObject& parameter) {
	if (!m_server.get()) throw runtime_error("Server not found");
	return move(m_server.get()->onConnect(parameter));
}

void ServerProxy::open(JsonXObject& parameter) {
	if (!m_server.get()) throw runtime_error("Server not found");
	m_server.get()->onOpen(parameter);
}

void ServerProxy::close(JsonXObject& parameter) {
	if (!m_server.get()) throw runtime_error("Server not found");
	m_server.get()->onClose(parameter);
}

void ServerProxy::send(JsonXObject&& message, MessagePriority priority) {
	if (!m_server.get()) throw runtime_error("Server not found");
	m_server.get()->onReceive(move(message), priority);
}

JsonXObject&& ServerProxy::ctrl(JsonXObject& request) {
	if (!m_server.get()) throw runtime_error("Server not found");
	return move(m_server.get()->onCtrl(request));
}

void ServerProxy::kill() {
	m_server.reset();
}

} // end namespace FreeAX25 //

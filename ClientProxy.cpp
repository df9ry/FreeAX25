/*
 * ClientProxy.cpp
 *
 *  Created on: 26.05.2015
 *      Author: tania
 */

#include "ClientProxy.h"
#include "ServerProxy.h"

#include <stdexcept>

using namespace std;
using namespace JsonX;

namespace FreeAX25 {

enum class ClientProxyState {
	NEW, INIT, OPEN, CLOSED
};

ClientProxy::ClientProxy(ServerProxy* serverProxy):
		m_serverProxy{serverProxy}, m_state{ClientProxyState::NEW}
{
}

ClientProxy::~ClientProxy() {
}

ClientProxy&& ClientProxy::connect(JsonXObject& parameter, ClientProxy&& downlink) {
	if (m_state != ClientProxyState::NEW)
		throw logic_error("Invalid state in ClientProxy::open");
	ClientProxy&& result{m_serverProxy.get()->connect(parameter, move(downlink))};
	m_state = ClientProxyState::INIT;
	return move(result);
}

ClientProxy&& ClientProxy::connect(ClientProxy&& downlink) {
	if (m_state != ClientProxyState::NEW)
		throw logic_error("Invalid state in ClientProxy::open");
	JsonXObject parameter{};
	ClientProxy&& result{m_serverProxy.get()->connect(parameter, move(downlink))};
	m_state = ClientProxyState::INIT;
	return move(result);
}

ClientProxy&& ClientProxy::connect(JsonXObject& parameter) {
	if (m_state != ClientProxyState::NEW)
		throw logic_error("Invalid state in ClientProxy::open");
	ClientProxy&& result{m_serverProxy.get()->connect(parameter)};
	m_state = ClientProxyState::INIT;
	return move(result);
}

ClientProxy&& ClientProxy::connect() {
	if (m_state != ClientProxyState::NEW)
		throw logic_error("Invalid state in ClientProxy::open");
	JsonXObject parameter{};
	ClientProxy&& result{m_serverProxy.get()->connect(parameter)};
	m_state = ClientProxyState::INIT;
	return move(result);
}

void ClientProxy::open(JsonXObject& parameter) {
	if (m_state != ClientProxyState::NEW)
		throw logic_error("Invalid state in ClientProxy::open");
	m_serverProxy.get()->open(parameter);
	m_state = ClientProxyState::OPEN;
}

void ClientProxy::open() {
	if (m_state != ClientProxyState::NEW)
		throw logic_error("Invalid state in ClientProxy::open");
	JsonXObject parameter{};
	m_serverProxy.get()->open(parameter);
	m_state = ClientProxyState::OPEN;
}

void ClientProxy::close(JsonXObject& parameter) {
	m_serverProxy.get()->close(parameter);
	m_state = ClientProxyState::CLOSED;
}

void ClientProxy::close() {
	JsonXObject parameter{};
	m_serverProxy.get()->close(parameter);
	m_state = ClientProxyState::CLOSED;
}

void ClientProxy::send(JsonXObject&& message, MessagePriority priority) {
	if (m_state != ClientProxyState::OPEN)
		throw logic_error("Invalid state in ClientProxy::send");
	m_serverProxy.get()->send(move(message), priority);
}

JsonXObject&& ClientProxy::ctrl(JsonXObject& request) {
	return move(m_serverProxy.get()->ctrl(request));
}

} /* namespace FreeAX25 */

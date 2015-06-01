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

#include "ClientProxy.h"
#include "ServerProxy.h"

#include <stdexcept>

using namespace std;
using namespace JsonX;

namespace FreeAX25 {

enum class ClientProxyState {
	ZERO, NEW, INIT, OPEN, CLOSED
};

ClientProxy::ClientProxy():
		m_serverProxy{shared_ptr<ServerProxy>()},
		m_state{ClientProxyState::ZERO}
{
}

ClientProxy::ClientProxy(ClientProxy&& other)
{
	swap(m_serverProxy, other.m_serverProxy);
	swap(m_state, other.m_state);
}

ClientProxy& ClientProxy::operator=(ClientProxy&& other)
{
	swap(m_serverProxy, other.m_serverProxy);
	swap(m_state, other.m_state);
	return *this;
}

ClientProxy::ClientProxy(ServerProxy* serverProxy):
		m_serverProxy{serverProxy}, m_state{ClientProxyState::NEW}
{
}

ClientProxy::~ClientProxy() {
}

ClientProxy ClientProxy::connect(JsonX::JsonXValue&& parameter, ClientProxy&& downlink) {
	if (m_state != ClientProxyState::NEW)
		throw logic_error("Invalid state in ClientProxy::open");
	if (!m_serverProxy) return ClientProxy{};
	ClientProxy result{m_serverProxy.get()->connect(move(parameter), move(downlink))};
	m_state = ClientProxyState::INIT;
	return result;
}

ClientProxy ClientProxy::connect(ClientProxy&& downlink) {
	if (m_state != ClientProxyState::NEW)
		throw logic_error("Invalid state in ClientProxy::open");
	if (!m_serverProxy) return ClientProxy{};
	ClientProxy result{m_serverProxy.get()->connect(JsonXValue{}, move(downlink))};
	m_state = ClientProxyState::INIT;
	return result;
}

ClientProxy ClientProxy::connect(JsonXValue&& parameter) {
	if (m_state != ClientProxyState::NEW)
		throw logic_error("Invalid state in ClientProxy::open");
	if (!m_serverProxy) return ClientProxy{};
	ClientProxy result{m_serverProxy.get()->connect(move(parameter))};
	m_state = ClientProxyState::INIT;
	return move(result);
}

ClientProxy ClientProxy::connect() {
	if (m_state != ClientProxyState::NEW)
		throw logic_error("Invalid state in ClientProxy::open");
	if (!m_serverProxy) return ClientProxy{};
	ClientProxy result{m_serverProxy.get()->connect(JsonXValue{})};
	m_state = ClientProxyState::INIT;
	return result;
}

void ClientProxy::open(JsonXValue&& parameter) {
	if (m_state != ClientProxyState::NEW)
		throw logic_error("Invalid state in ClientProxy::open");
	if (!m_serverProxy) return;
	m_serverProxy.get()->open(move(parameter));
	m_state = ClientProxyState::OPEN;
}

void ClientProxy::open() {
	if (m_state != ClientProxyState::NEW)
		throw logic_error("Invalid state in ClientProxy::open");
	m_serverProxy.get()->open(JsonXValue{});
	m_state = ClientProxyState::OPEN;
}

void ClientProxy::close(JsonXValue&& parameter) {
	if (!m_serverProxy) return;
	m_serverProxy.get()->close(move(parameter));
	m_state = ClientProxyState::CLOSED;
}

void ClientProxy::close() {
	if (!m_serverProxy) return;
	m_serverProxy.get()->close(JsonXValue{});
	m_state = ClientProxyState::CLOSED;
}

void ClientProxy::send(JsonXValue&& message, MessagePriority priority) {
	if (m_state != ClientProxyState::OPEN)
		throw logic_error("Invalid state in ClientProxy::send");
	if (!m_serverProxy) return;
	m_serverProxy.get()->send(move(message), priority);
}

JsonXValue ClientProxy::ctrl(JsonXValue&& request) {
	if (!m_serverProxy) return JsonXValue{};
	return m_serverProxy.get()->ctrl(move(request));
}

} /* namespace FreeAX25 */

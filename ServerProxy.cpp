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

ServerProxy::~ServerProxy()
{
}

unique_ptr<ClientProxy> ServerProxy::getClientProxy() {
	return unique_ptr<ClientProxy>(new ClientProxy(this));
}

std::unique_ptr<ClientProxy> ServerProxy::connect(
		std::unique_ptr<JsonX::JsonXValue>&& parameter,
		std::unique_ptr<ClientProxy>&& downlink)
{
	if (!m_server.get()) throw runtime_error("Server not found");
	return m_server.get()->onConnect(move(parameter), move(downlink));
}

std::unique_ptr<ClientProxy> ServerProxy::connect(
		std::unique_ptr<JsonX::JsonXValue>&& parameter)
{
	if (!m_server.get()) throw runtime_error("Server not found");
	return m_server.get()->onConnect(move(parameter));
}

void ServerProxy::open(
		std::unique_ptr<JsonX::JsonXValue>&& parameter)
{
	if (!m_server.get()) throw runtime_error("Server not found");
	m_server.get()->onOpen(move(parameter));
}

void ServerProxy::close(
		std::unique_ptr<JsonX::JsonXValue>&& parameter)
{
	if (!m_server.get()) throw runtime_error("Server not found");
	m_server.get()->onClose(move(parameter));
}

void ServerProxy::send(
		std::unique_ptr<JsonX::JsonXValue>&& message,
		MessagePriority priority)
{
	if (!m_server.get()) throw runtime_error("Server not found");
	m_server.get()->onReceive(move(message), priority);
}

std::unique_ptr<JsonX::JsonXValue> ServerProxy::ctrl(
		std::unique_ptr<JsonX::JsonXValue>&& request)
{
	if (!m_server.get()) throw runtime_error("Server not found");
	return m_server.get()->onCtrl(move(request));
}

void ServerProxy::kill() {
	m_server.reset();
}

} // end namespace FreeAX25 //

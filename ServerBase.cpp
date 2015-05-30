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

#include "ServerBase.h"
#include "ServerProxy.h"

#include "JsonXObject.h"

#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;
using namespace JsonX;

namespace FreeAX25 {

class ClientProxy;

ServerBase::ServerBase() {
	cerr << "ServerBase::ServerBase()" << endl;
}

ServerBase::~ServerBase() {
	cerr << "ServerBase::~ServerBase()" << endl;
}

std::unique_ptr<ClientProxy> ServerBase::onConnect(
		std::unique_ptr<JsonX::JsonXValue>&& parameter,
		std::unique_ptr<ClientProxy>&& downlink)
{
	throw logic_error("Unsupported service: connect");
}

std::unique_ptr<ClientProxy> ServerBase::onConnect(
		std::unique_ptr<JsonX::JsonXValue>&& parameter)
{
	throw logic_error("Unsupported service: connect");
}

void ServerBase::onOpen(
		std::unique_ptr<JsonX::JsonXValue>&& parameter)
{
	throw logic_error("Unsupported service: open");
}

void ServerBase::onClose(
		std::unique_ptr<JsonX::JsonXValue>&& parameter)
{
	throw logic_error("Unsupported service: close");
}

void ServerBase::onReceive(
		std::unique_ptr<JsonX::JsonXValue>&& message,
		MessagePriority priority)
{
	throw logic_error("Unsupported service: send");
}

std::unique_ptr<JsonX::JsonXValue> ServerBase::onCtrl(
		std::unique_ptr<JsonX::JsonXValue>&& request)
{
	throw logic_error("Unsupported service: control");
}

unique_ptr<ServerProxy> ServerBase::getServerProxy() {
	return unique_ptr<ServerProxy>(new ServerProxy(this));
}

} /* namespace JsonX */

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

#include "Channel.h"
#include "Environment.h"

#include <stdexcept>
#include <string>

using namespace std;

namespace FreeAX25 {

Channel::Channel(): m_tx{ServerProxy()}
{
}

Channel::Channel(const ServerProxy& link, bool isUplink) {
	if (isUplink) {
		ServerProxy sp{link};
		m_tx = sp.connect(getServerProxy());
		if (!m_tx) throw runtime_error(
				"Unable to connect uplink service");
	} else {
		m_tx = link;
	}
}

Channel::~Channel() {
}

ServerProxy Channel::connect(JsonX::JsonXValue&& parameter, ServerProxy&& downlink) {
	if (!m_tx) throw runtime_error("Channel closed.");
	return m_tx.connect(move(parameter), move(downlink));
}

void Channel::open(JsonX::JsonXValue&& parameter) {
	if (!m_tx) throw runtime_error("Channel closed.");
	m_tx.open(move(parameter));
}

void Channel::close(JsonX::JsonXValue&& parameter) {
	if (!m_tx) throw runtime_error("Channel closed.");
	m_tx.close(move(parameter));
}

void Channel::send(JsonX::JsonXValue&& message, MessagePriority priority) {
	if (!m_tx) throw runtime_error("Channel closed.");
	m_tx.send(move(message), priority);
}

JsonX::JsonXValue Channel::ctrl(JsonX::JsonXValue&& request) {
	if (!m_tx) throw runtime_error("Channel closed.");
	return m_tx.ctrl(move(request));
}

ServerProxy Channel::onConnect(JsonX::JsonXValue&& parameter, ServerProxy&& downlink) {
	if (!connectFunction) throw runtime_error(
			"Request not handled: connect");
	return connectFunction(move(parameter), move(downlink));
}

void Channel::onOpen(JsonX::JsonXValue&& parameter) {
	if (!openFunction) throw runtime_error(
			"Request not handled: open");
	openFunction(move(parameter));
}

void Channel::onClose(JsonX::JsonXValue&& parameter) {
	if (!closeFunction) throw runtime_error(
			"Request not handled: close");
	closeFunction(move(parameter));
}

void Channel::onReceive(JsonX::JsonXValue&& message, MessagePriority priority) {
	if (!receiveFunction) throw runtime_error(
			"Request not handled: send");
	receiveFunction(move(message), priority);
}

JsonX::JsonXValue Channel::onCtrl(JsonX::JsonXValue&& request) {
	if (!ctrlFunction) throw runtime_error(
			"Request not handled: control");
	return ctrlFunction(move(request));
}

void Channel::_release() {
	m_tx.close();
	ServerBase::_release();
}


} /* namespace FreeAX25 */

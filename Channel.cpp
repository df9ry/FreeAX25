/*
 * Channel.cpp
 *
 *  Created on: 06.06.2015
 *      Author: tania
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

Channel::Channel(const ClientEndPoint& cep) {
	if (cep.getUrl().empty()) throw runtime_error(
			"Unable to create channel to server \"\"");
	ServerProxy broker{environment.serverProxies.findEntry(cep.getUrl())};
	if (!broker) throw runtime_error(
			"Unable to find broker service " + cep.getUrl());
	m_tx = broker.connect(getServerProxy());
	if (!m_tx) throw runtime_error(
			"Unable to connect service " + cep.getUrl());
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

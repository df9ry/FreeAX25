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

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include "ServerBase.h"
#include "ServerProxy.h"
#include "ClientEndPoint.h"

namespace FreeAX25 {

/**
 * A Channel is a device to send and receive to other peers.
 */
class Channel: public ServerBase {
public:
	/**
	 * Default constructor.
	 */
	Channel();

	/**
	 * Construct a channel.
	 * @param downlink Downlink proxy.
	 * @param isUplink Set true, when uplink, false when downlink.
	 */
	Channel(const ServerProxy& link, bool isUplink);

	/**
	 * Destructor.
	 */
	~Channel();

	/**
	 * Connect to the server.
	 * @param parameter Parameter for connect.
	 * @param downlink ServerProxy for downlink.
	 * @return ServerProxy. This is not necessary a proxy to the same server where
	 *         this call is placed on. The target server may return a server dedicated
	 *         for this client directly.
	 */
	ServerProxy connect(JsonX::JsonXValue&& parameter, ServerProxy&& downlink);

	/**
	 * Connect to the server.
	 * @param downlink ServerProxy for downlink.
	 * @return ServerProxy. This is not necessary a proxy to the same server where
	 *         this call is placed on. The target server may return a server dedicated
	 *         for this client directly.
	 */
	ServerProxy connect(ServerProxy&& downlink) {
		return connect(JsonX::JsonXValue(), std::move(downlink));
	}

	/**
	 * Connect to the server.
	 * @param parameter Parameter for connect.
	 * @return ServerProxy. This is not necessary a proxy to the same server where
	 *         this call is placed on. The target server may return a server dedicated
	 *         for this client directly.
	 */
	ServerProxy connect(JsonX::JsonXValue&& parameter) {
		return connect(std::move(parameter), ServerProxy());
	}

	/**
	 * Connect to the server.
	 * @param parameter Parameter for connect.
	 * @return ServerProxy. This is not necessary a proxy to the same server where
	 *         this call is placed on. The target server may return a server dedicated
	 *         for this client directly.
	 */
	ServerProxy connect() {
		return connect(JsonX::JsonXValue(), ServerProxy());
	}

	/**
	 * Open connection to server. This should be the first call to the server after
	 * a connect.
	 * @param parameter Parameter for open.
	 */
	void open(JsonX::JsonXValue&& parameter);

	/**
	 * Open connection to server. This should be the first call to the server after
	 * a connect.
	 */
	void open() {
		open (JsonX::JsonXValue());
	}

	/**
	 * Close connection to server. This should be the last call to this server.
	 * @param parameter Parameter for close.
	 */
	void close(JsonX::JsonXValue&& parameter);

	/**
	 * Close connection to server. This should be the last call to this server.
	 */
	void close() {
		close(JsonX::JsonXValue());
	}

	/**
	 * Send a message to the server.
	 * @param message Message to send.
	 * @param priority Message priority.
	 */
	void send(JsonX::JsonXValue&& message, MessagePriority priority = MessagePriority::ROUTINE);

	/**
	 * Send a request to the server.
	 * @param request Request to send.
	 * @return Response from server.
	 */
	JsonX::JsonXValue ctrl(JsonX::JsonXValue&& request);

	/**
	 * Set this function to serve connect requests.
	 */
	std::function<ServerProxy(JsonX::JsonXValue&&, ServerProxy&&)> connectFunction{};

	/**
	 * Set this function to serve open requests.
	 */
	std::function<void(JsonX::JsonXValue&&)>                       openFunction{};

	/**
	 * Set this function to serve close requests.
	 */
	std::function<void(JsonX::JsonXValue&&)>                       closeFunction{};

	/**
	 * Set this function to serve send requests.
	 */
	std::function<void(JsonX::JsonXValue&&, MessagePriority)>      receiveFunction{};

	/**
	 * Set this function to serve control requests.
	 */
	std::function<JsonX::JsonXValue(JsonX::JsonXValue&&)>          ctrlFunction{};

	/**
	 * Get a proxy to the transmitter side.
	 * @return Transmitter proxy.
	 */
	ServerProxy getTransmitterProxy() { return m_tx; }

protected:
	virtual ServerProxy onConnect(JsonX::JsonXValue&& parameter, ServerProxy&& downlink);

	virtual void onOpen(JsonX::JsonXValue&& parameter);

	virtual void onClose(JsonX::JsonXValue&& parameter);

	virtual void onReceive(JsonX::JsonXValue&& message, MessagePriority priority);

	virtual JsonX::JsonXValue onCtrl(JsonX::JsonXValue&& request);

	void _release();

private:
	ServerProxy m_tx;
};

} /* namespace FreeAX25 */

#endif /* CHANNEL_H_ */

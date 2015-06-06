/*
 * Channel.h
 *
 *  Created on: 06.06.2015
 *      Author: tania
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
	 * Construct a Channel from a ClientEndPoint.
	 * @param cep The ClientEndPoint to use.
	 */
	Channel(const ClientEndPoint& cep);

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

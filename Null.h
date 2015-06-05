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


#ifndef NULL_H_
#define NULL_H_

#include "ServerBase.h"
#include "Plugin.h"

namespace FreeAX25 {

/**
 * Plugin initialize.
 * @param e The environment struct
 * @param p The plugin struct
 */
void initNull(const Plugin& p);

/**
 * Plugin start.
 */
void startNull();

/**
 * This is a dummy class that throws away everything it receives
 * and transmit nothing at all. Good for testing and development.
 */
class Null: public ServerBase {
public:

	/**
	 * Constructor
	 */
	Null();

	/**
	 * Destructor
	 */
	~Null();

	/**
	 * Initialize the Null
	 * @param p Plugin data structure
	 */
	void init(const Plugin& p);

	/**
	 * Start the Null
	 */
	void start();

protected:
	virtual ServerProxy onConnect(JsonX::JsonXValue&& parameter, ServerProxy&& downlink);

	virtual void onOpen(JsonX::JsonXValue&& parameter);

	virtual void onClose(JsonX::JsonXValue&& parameter);

	virtual void onReceive(JsonX::JsonXValue&& message, MessagePriority priority);

	virtual JsonX::JsonXValue onCtrl(JsonX::JsonXValue&& request);
};

} /* namespace FreeAX25 */

#endif /* NULL_H_ */

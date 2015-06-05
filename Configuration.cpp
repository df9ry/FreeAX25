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

#include "Configuration.h"

#include <iostream>

using namespace std;

namespace FreeAX25 {

void Configuration::print(const Configuration& conf) {
	cerr << "<Configuration name=\"" << conf.getId() << "\">" << endl;
	if (conf.settings.size() > 0) {
		cerr << "  <Settings>" << endl;
		for (auto i = conf.settings.begin(); i != conf.settings.end(); ++i) {
			const Setting& setting = *i->second.get();
			cerr << "    <Setting name=\"" << setting.getName() << "\">"
				 << setting.asString() << "</Setting>" << endl;
		}
		cerr << "  </Settings>" << endl;
	}
	if (conf.plugins.size() > 0) {
		cerr << "  <Plugins>" << endl;
		for (auto i = conf.plugins.begin(); i != conf.plugins.end(); ++i) {
			const Plugin& plugin = *i->second.get();
			cerr << "    <Plugin name=\"" << plugin.getName();
			if (!plugin.getFile().empty())
				 cerr << "\" file=\"" << plugin.getFile() << "\"";
			cerr << ">" << endl;
			if (plugin.settings.size() > 0) {
				cerr << "      <Settings>" << endl;
				for (auto i = plugin.settings.begin(); i != plugin.settings.end(); ++i) {
					const Setting& setting = *i->second.get();
					cerr << "        <Setting name=\"" << setting.getName() << "\">"
						 << setting.asString() << "</Setting>" << endl;
				}
				cerr << "      </Settings>" << endl;
			}
			if (plugin.instances.size() > 0) {
				cerr << "      <Instances>" << endl;
				for (auto i = plugin.instances.begin(); i != plugin.instances.end(); ++i) {
					const Instance& instance = *i->second.get();
					cerr << "        <Instance name=\"" << instance.getName() << "\">" << endl;
					for (auto i = instance.serverEndPoints.begin(); i != instance.serverEndPoints.end(); ++i) {
						const ServerEndPoint& sep = *i->second.get();
						cerr << "          <ServerEndPoint name=\"" << sep.getName() << "\" url=\""
							 << sep.getUrl() << "\"/>" << endl;
					}
					for (auto i = instance.clientEndPoints.begin(); i != instance.clientEndPoints.end(); ++i) {
						const ClientEndPoint& cep = *i->second.get();
						cerr << "          <ClientEndPoint name=\"" << cep.getName() << "\" url=\""
							 << cep.getUrl() << "\"/>" << endl;
					}
					if (instance.settings.size() > 0) {
						cerr << "          <Settings>" << endl;
						for (auto i = instance.settings.begin(); i != instance.settings.end(); ++i) {
							const Setting& setting = *i->second.get();
							cerr << "            <Setting name=\"" << setting.getName() << "\">"
								 << setting.asString() << "</Setting>" << endl;
						}
						cerr << "          </Settings>" << endl;
					}
					cerr << "        </Instance>" << endl;
				}
				cerr << "      </Instances>" << endl;
			}
			cerr << "    </Plugin>" << endl;
		}
		cerr << "  </Plugins>" << endl;
	}
	cerr << "</Configuration>" << endl;
}

} // end namespace FreeAX25 //


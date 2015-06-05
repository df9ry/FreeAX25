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

#include "XMLRuntime.h"
#include "Configuration.h"
#include "Environment.h"
#include "DOMTreeErrorReporter.h"

#include <xercesc/parsers/XercesDOMParser.hpp>

#include <exception>
#include <cassert>
#include <string>

using namespace std;
using namespace XERCES_CPP_NAMESPACE;

namespace XMLIO {

/**
 * Convert standard string to XMLChar*
 * @param s String to convert
 * @return Converted XMLChar*
 */
static inline const XMLCh* toX(const string& s) {
	return XMLString::transcode(s.c_str());
}

/**
 * Convert standard string to XMLChar*
 * @param s String to convert
 * @return Converted XMLChar*
 */
static inline const XMLCh* toX(const char* s) {
	return toX(string(s));
}

/**
 * Convert XMLChar* to standard string
 * @param x XMLChar* to convert
 * @return Converted standard string
 */
static inline const string fmX(const XMLCh* x) {
	return string(XMLString::transcode(x));
}

XMLRuntime::XMLRuntime() { XMLPlatformUtils::Initialize(); }

XMLRuntime::~XMLRuntime() { XMLPlatformUtils::Terminate(); }

/**
 * Read XML file into Configuration object
 * @param filename File to read
 */
void XMLRuntime::read(const string& filename) {
    //
    //  Create our parser, then attach an error handler to the parser.
    //  The parser will call back to methods of the ErrorHandler if it
    //  discovers errors during the course of parsing the XML document.
    //
    XercesDOMParser parser;
    parser.setValidationScheme(XercesDOMParser::Val_Always);
    parser.setDoNamespaces(true);
    parser.setDoSchema(true);
    parser.setDoXInclude(true);
    parser.setHandleMultipleImports(true);
    parser.setValidationSchemaFullChecking(true);
    parser.setCreateEntityReferenceNodes(false);
    parser.setIncludeIgnorableWhitespace(false);

    DOMTreeErrorReporter errReporter;
    parser.setErrorHandler(&errReporter);

    parser.parse(filename.c_str());

    if (errReporter.getSawErrors())
    	throw exception();

    // Now read configuration from the DOM Tree:
    XERCES_CPP_NAMESPACE::DOMDocument* doc = parser.getDocument();
    assert(doc != nullptr);

    FreeAX25::Configuration& config = FreeAX25::environment.configuration;
    assert(config != nullptr);

    auto rootElement = doc->getDocumentElement();
    auto configName = rootElement->getAttribute(toX("name"));
    config.setId(fmX(configName));

    { // Get settings:
		auto nodeList = rootElement->getElementsByTagName(toX("Settings"));
		if (nodeList->getLength() > 0)
			readSettings(
					string(""),
					static_cast<DOMElement*>(nodeList->item(0)),
					config.settings);
    }

    { // Get plugins:
		auto nodeList = rootElement->getElementsByTagName(toX("Plugins"));
		if (nodeList->getLength() > 0)
			readPlugins(
					string(""),
					static_cast<DOMElement*>(nodeList->item(0)),
					config.plugins);
    }
}

void XMLRuntime::readSettings(
		const string& id,
		DOMElement* element,
		FreeAX25::UniquePointerDict<FreeAX25::Setting>& settings)
{
	if (element == nullptr) return;
	auto nodeList = element->getElementsByTagName(toX("Setting"));
	for (uint32_t i = 0; i < nodeList->getLength(); ++i) {
		auto settingElement = static_cast<DOMElement*>(nodeList->item(i));
		string name  = fmX(settingElement->getAttribute(toX("name")));
		string value = fmX(settingElement->getTextContent());
		FreeAX25::environment.logDebug(
				"Setting " + id + "/" + name + " = \"" + value + "\"");
		FreeAX25::Setting setting(id + "/" + name, value);
		settings.insertMove(name, move(setting));
	} // end for //
}

void XMLRuntime::readPlugins(
		const string& id,
		DOMElement* element,
		FreeAX25::UniquePointerDict<FreeAX25::Plugin>& plugins)
{
	if (element == nullptr) return;
	auto nodeList = element->getElementsByTagName(toX("Plugin"));
	for (uint32_t i = 0; i < nodeList->getLength(); ++i) {
		auto pluginNode = static_cast<DOMElement*>(nodeList->item(i));
		string name  = fmX(pluginNode->getAttribute(toX("name")));
		auto _file = pluginNode->getAttribute(toX("file"));
		string file = (_file != nullptr) ? fmX(_file) : "";
		FreeAX25::environment.logDebug(
				"Define plugin " + id + "/" + name + "(" + file + ")");
		FreeAX25::Plugin plugin(id + "/" + name, file);

	    { // Get settings:
			auto nodeList = pluginNode->getElementsByTagName(toX("Settings"));
			if (nodeList->getLength() > 0)
				readSettings(
						id + "/" + name,
						static_cast<DOMElement*>(nodeList->item(0)),
						plugin.settings);
	    }

	    { // Get instances:
			auto nodeList = pluginNode->getElementsByTagName(toX("Instances"));
			if (nodeList->getLength() > 0)
				readInstances(
						id + "/" + name,
						static_cast<DOMElement*>(nodeList->item(0)),
						plugin.instances);
	    }
		plugins.insertMove(name, move(plugin));

	} // end for //
}

void XMLRuntime::readInstances(
		const string& id,
		DOMElement* element,
		FreeAX25::UniquePointerDict<FreeAX25::Instance>& instances)
{
	if (element == nullptr) return;
	auto nodeList = element->getElementsByTagName(toX("Instance"));
	for (uint32_t i = 0; i < nodeList->getLength(); ++i) {
		auto instanceNode = static_cast<DOMElement*>(nodeList->item(i));
		string name  = fmX(instanceNode->getAttribute(toX("name")));
		FreeAX25::environment.logDebug(
				"Define instance " + id + "/" + name);
		FreeAX25::Instance instance(id + "/" + name);

	    { // Get client endpoints:
			auto nodeList = instanceNode->getElementsByTagName(toX("ClientEndPoint"));
			for (uint32_t i = 0; i < nodeList->getLength(); ++i) {
				auto instanceNode = static_cast<DOMElement*>(nodeList->item(i));
				string name = fmX(instanceNode->getAttribute(toX("name")));
				string url  = fmX(instanceNode->getAttribute(toX("url")));
				FreeAX25::environment.logDebug(
						"Define client endpoint " + id + "/" + name + " as " + url);
				FreeAX25::ClientEndPoint endpoint(id + "/" + name, url);
				instance.clientEndPoints.insertMove(name, move(endpoint));
			} // end for //
	    }

	    { // Get server endpoints:
			auto nodeList = instanceNode->getElementsByTagName(toX("ServerEndPoint"));
			for (uint32_t i = 0; i < nodeList->getLength(); ++i) {
				auto instanceNode = static_cast<DOMElement*>(nodeList->item(i));
				string name = fmX(instanceNode->getAttribute(toX("name")));
				string url  = fmX(instanceNode->getAttribute(toX("url")));
				FreeAX25::environment.logDebug(
						"Define server endpoint " + id + "/" + name + " as " + url);
				FreeAX25::ServerEndPoint endpoint(id + "/" + name, url);
				instance.serverEndPoints.insertMove(name, move(endpoint));
			} // end for //
	    }

	    { // Get settings:
			auto nodeList = instanceNode->getElementsByTagName(toX("Settings"));
			if (nodeList->getLength() > 0)
				readSettings(
						id + "/" + name,
						static_cast<DOMElement*>(nodeList->item(0)),
						instance.settings);
	    }

		instances.insertMove(name, move(instance));
	} // end for //
}

} /* namespace XMLIO */

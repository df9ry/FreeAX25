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
#include "DOMTreeErrorReporter.h"

#include <xercesc/parsers/XercesDOMParser.hpp>

#include <exception>
#include <cassert>

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
 * Convert XMLChar* to standard string
 * @param x XMLChar* to convert
 * @return Converted standard string
 */
static inline const string fmX(const XMLCh* x) {
	return string(XMLString::transcode(x));
}

/**
 * Read XML file into Configuration object
 * @param filename File to read
 */
void XMLRuntime::read(const string& filename)
{
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

    FreeAX25::Configuration* config = m_environment->getConfiguration();
    assert(config != nullptr);

    auto rootElement = doc->getDocumentElement();
    auto configName = rootElement->getAttribute(toX("name"));
    config->setId(fmX(configName));

    { // Get settings:
		auto nodeList = rootElement->getElementsByTagName(toX("Settings"));
		if (nodeList->getLength() > 0)
			readSettings(
					"",
					static_cast<DOMElement*>(nodeList->item(0)),
					config->settings);
    }

    { // Get plugins:
		auto nodeList = rootElement->getElementsByTagName(toX("Plugins"));
		if (nodeList->getLength() > 0)
			readPlugins(
					"",
					static_cast<DOMElement*>(nodeList->item(0)),
					config->plugins);
    }
}

void XMLRuntime::readSettings(
		const string& id,
		DOMElement* element,
		FreeAX25::Map<FreeAX25::Setting>& settings)
{
	if (element == nullptr) return;
	auto nodeList = element->getElementsByTagName(toX("Setting"));
	for (uint32_t i = 0; i < nodeList->getLength(); ++i) {
		auto settingElement = static_cast<DOMElement*>(nodeList->item(i));
		string name  = fmX(settingElement->getAttribute(toX("name")));
		string value = fmX(settingElement->getTextContent());
		m_environment->logDebug(
				"Setting " + id + "/" + name + " = \"" + value + "\"");
		settings.insert(name, new FreeAX25::Setting(
				id + "/" + name, value, m_environment));
	} // end for //
}

void XMLRuntime::readPlugins(
		const string& id,
		DOMElement* element,
		FreeAX25::Map<FreeAX25::Plugin>& plugins)
{
	if (element == nullptr) return;
	auto nodeList = element->getElementsByTagName(toX("Plugin"));
	for (uint32_t i = 0; i < nodeList->getLength(); ++i) {
		auto pluginNode = static_cast<DOMElement*>(nodeList->item(i));
		string name  = fmX(pluginNode->getAttribute(toX("name")));
		auto _file = pluginNode->getAttribute(toX("file"));
		string file = (_file != nullptr) ? fmX(_file) : "";
		m_environment->logDebug(
				"Define plugin " + id + "/" + name + "(" + file + ")");
		FreeAX25::Plugin* plugin = new FreeAX25::Plugin(
				id + "/" + name, file, m_environment);
		plugins.insert(name, plugin);

	    { // Get settings:
			auto nodeList = pluginNode->getElementsByTagName(toX("Settings"));
			if (nodeList->getLength() > 0)
				readSettings(
						id + "/" + name,
						static_cast<DOMElement*>(nodeList->item(0)),
						plugin->settings);
	    }

	    { // Get instances:
			auto nodeList = pluginNode->getElementsByTagName(toX("Instances"));
			if (nodeList->getLength() > 0)
				readInstances(
						id + "/" + name,
						static_cast<DOMElement*>(nodeList->item(0)),
						plugin->instances);
	    }
	} // end for //
}

void XMLRuntime::readInstances(
		const string& id,
		DOMElement* element,
		FreeAX25::Map<FreeAX25::Instance>& instances)
{
	if (element == nullptr) return;
	auto nodeList = element->getElementsByTagName(toX("Instance"));
	for (uint32_t i = 0; i < nodeList->getLength(); ++i) {
		auto instanceNode = static_cast<DOMElement*>(nodeList->item(i));
		string name  = fmX(instanceNode->getAttribute(toX("name")));
		m_environment->logDebug(
				"Define instance " + id + "/" + name);
		FreeAX25::Instance* instance = new FreeAX25::Instance(
				id + "/" + name, m_environment);
		instances.insert(name, instance);

	    { // Get settings:
			auto nodeList = instanceNode->getElementsByTagName(toX("Settings"));
			if (nodeList->getLength() > 0)
				readSettings(
						id + "/" + name,
						static_cast<DOMElement*>(nodeList->item(0)),
						instance->settings);
	    }
	} // end for //
}

} /* namespace XMLIO */

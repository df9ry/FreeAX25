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
#include "Utils.h"
#include "Environment.h"
#include "Configuration.h"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

#include <stdexcept>
#include <string>

using namespace std;
using namespace FreeAX25;

int main(int argc, const char* argv[]) {
	// Get program name and path:
	string filename{};
	if (argc > 1) {
		filename.append(argv[1]);
	} else {
		filename.append(argv[0]);
		if (Utils::endsWith(Utils::toLower(filename), ".exe"))
			filename = filename.substr(0, filename.size()-4);
	}
	filename.append(".xml");

	FreeAX25::Environment env{};
	env.logInfo("Parsing " + filename);

	try {
		// Create a XMLRuntime for input of configuration info:
		XMLIO::XMLRuntime xmlio(&env);
		xmlio.read(filename);
		env.logInfo("Activating configuration \"" +
				env.getConfiguration()->getId() + "\"");
		Configuration& c = *env.getConfiguration();
		env.logInfo("Load all plugins");
		for (auto i = c.plugins.begin(); i != c.plugins.end(); ++i)
			i->second->load();
		env.logInfo("Init all plugins");
		for (auto i = c.plugins.begin(); i != c.plugins.end(); ++i)
			i->second->init();
		env.logInfo("Start all plugins");
		for (auto i = c.plugins.begin(); i != c.plugins.end(); ++i)
			i->second->start();
	}
	catch(const XERCES_CPP_NAMESPACE::XMLException &e)
	{
		env.logError(
			"Error during XML IO: Exception message: " +
			XMLIO::StrX(e.getMessage()).str());
		return EXIT_FAILURE;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& e)
	{
		const unsigned int maxChars = 2047;
		XMLCh errText[maxChars + 1];

		env.logError(string(
				"DOM Error during parsing: DOMException code is: ")
				+ to_string(e.code));

		if (XERCES_CPP_NAMESPACE::DOMImplementation::loadDOMExceptionMsg(e.code, errText, maxChars))
			 env.logError("  Message is: " + XMLIO::StrX(errText).str());

		return EXIT_FAILURE;
	}
	catch (const XERCES_CPP_NAMESPACE::OutOfMemoryException &e)
	{
		env.logError("XML IO OutOfMemoryException");
		return EXIT_FAILURE;
	}
	catch (const runtime_error& e)
	{
		env.logError(string("Runtime error: ") + e.what());
		return EXIT_FAILURE;
	}
	catch (const exception& e)
	{
		// The simple exception signals errors already logged.
		return EXIT_FAILURE;
	}
	catch (...)
	{
		env.logError("Unknown XML IO error");
		return EXIT_FAILURE;
	}

	// The program is finished when the heart beat stops:
	env.getTimerManager()->join();
	env.logInfo("Regular program exit");
	return EXIT_SUCCESS;
}

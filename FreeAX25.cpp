//============================================================================
// Name        : OpenAX25_V2.cpp80
// Author      : Tania Knoebl (DF9RY)
// Version     :
// Copyright   : This project is contributed under the GPL v 3 license
// Description : Hello World in C, Ansi-style
//============================================================================

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

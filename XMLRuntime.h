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

#ifndef XMLRUNTIME_H_
#define XMLRUNTIME_H_

#include "Environment.h"
#include "Map.h"

#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>

#include <ostream>
#include <string>

namespace XMLIO {

// ---------------------------------------------------------------------------
// This class encapsulate the XML Runtime interface.
// ---------------------------------------------------------------------------

class XMLRuntime {
public:
	/**
	 * Constructor
	 * @param e Global Environment
	 */
	XMLRuntime(FreeAX25::Environment* e): m_environment{e}
	{
		XERCES_CPP_NAMESPACE::XMLPlatformUtils::Initialize();
	}

	/**
	 * Destructor
	 */
	~XMLRuntime()
	{
		XERCES_CPP_NAMESPACE::XMLPlatformUtils::Terminate();
	}

	/**
	 * Read configuration from XML file
	 * @param filename Name of the XML file
	 */
	void read(const std::string& filename);

private:
	FreeAX25::Environment* m_environment;

    void readSettings(
    		const std::string& id,
    		XERCES_CPP_NAMESPACE::DOMElement* element,
    		FreeAX25::Map<FreeAX25::Setting>& settings);

    void readPlugins(
    		const std::string& id,
			XERCES_CPP_NAMESPACE::DOMElement* element,
			FreeAX25::Map<FreeAX25::Plugin>& plugins);

    void readInstances(
    		const std::string& id,
			XERCES_CPP_NAMESPACE::DOMElement* element,
			FreeAX25::Map<FreeAX25::Instance>& instances);
};

// ---------------------------------------------------------------------------
//  This is a simple class that lets us do easy (though not terribly efficient)
//  trancoding of XMLCh data to local code page for display.
// ---------------------------------------------------------------------------
class StrX
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    StrX(const XMLCh* const toTranscode)
	{
	    // Call the private transcoding method
	    fLocalForm = XERCES_CPP_NAMESPACE::XMLString::transcode(toTranscode);
	}

	~StrX()
	{
		XERCES_CPP_NAMESPACE::XMLString::release(&fLocalForm);
	}

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const char* localForm() const
    {
        return fLocalForm;
    }

    const std::string str() const
    {
    	return std::string(fLocalForm);
    }

private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fLocalForm
    //      This is the local code page form of the string.
    // -----------------------------------------------------------------------
    char*   fLocalForm;
};

inline std::ostream& operator<<(std::ostream& target, const StrX& toDump)
{
    target << toDump.localForm();
    return target;
}

} /* namespace XMLIO */

#endif /* XMLRUNTIME_H_ */

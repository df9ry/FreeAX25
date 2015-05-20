/*
 * DOMTreeErrorReporter.cpp
 *
 *  Created on: 23.04.2015
 *      Author: tania
 */

#include <iostream>

#include <xercesc/sax/SAXParseException.hpp>

#include "XMLRuntime.h"
#include "DOMTreeErrorReporter.h"

using namespace std;
using namespace XERCES_CPP_NAMESPACE;

namespace XMLIO {

void DOMTreeErrorReporter::warning(const SAXParseException&)
{
    //
    // Ignore all warnings.
    //
}

void DOMTreeErrorReporter::error(const SAXParseException& toCatch)
{
    fSawErrors = true;
    cerr << "Error at file \"" << StrX(toCatch.getSystemId())
		 << "\", line " << toCatch.getLineNumber()
		 << ", column " << toCatch.getColumnNumber()
         << "\n   Message: " << StrX(toCatch.getMessage()) << endl;
}

void DOMTreeErrorReporter::fatalError(const SAXParseException& toCatch)
{
    fSawErrors = true;
    cerr << "Fatal Error at file \"" << StrX(toCatch.getSystemId())
		 << "\", line " << toCatch.getLineNumber()
		 << ", column " << toCatch.getColumnNumber()
         << "\n   Message: " << StrX(toCatch.getMessage()) << endl;
}

void DOMTreeErrorReporter::resetErrors()
{
    fSawErrors = false;
}

} /* namespace XMLIO */

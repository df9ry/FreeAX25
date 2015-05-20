/*
 * DOMTreeErrorReporter.h
 *
 *  Created on: 23.04.2015
 *      Author: tania
 */

#ifndef DOMTREEERRORREPORTER_H_
#define DOMTREEERRORREPORTER_H_

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax/ErrorHandler.hpp>

namespace XMLIO {

class DOMTreeErrorReporter: public XERCES_CPP_NAMESPACE::ErrorHandler {
public:
	DOMTreeErrorReporter() {}
	~DOMTreeErrorReporter() {}

    // -----------------------------------------------------------------------
    //  Implementation of the error handler interface
    // -----------------------------------------------------------------------
    void warning(const XERCES_CPP_NAMESPACE::SAXParseException& toCatch);
    void error(const XERCES_CPP_NAMESPACE::SAXParseException& toCatch);
    void fatalError(const XERCES_CPP_NAMESPACE::SAXParseException& toCatch);
    void resetErrors();

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    bool getSawErrors() const;

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fSawErrors
    //      This is set if we get any errors, and is queryable via a getter
    //      method. Its used by the main code to suppress output if there are
    //      errors.
    // -----------------------------------------------------------------------
    bool    fSawErrors{false};

};

inline bool DOMTreeErrorReporter::getSawErrors() const
{
    return fSawErrors;
}

} /* namespace XMLIO */

#endif /* DOMTREEERRORREPORTER_H_ */



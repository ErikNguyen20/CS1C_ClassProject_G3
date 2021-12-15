#ifndef PARSEREXCEPTION_H
#define PARSEREXCEPTION_H

#include <string>    /* string */
#include <exception> /* Exception Class */
using std::string;
using std::exception;

//! ParserException Class
/*! Derived from exception. */
class ParserException : public exception
{
public:
    const string DEFAULT_EMPTY_MESSAGE = "File is corrupted."; //!< The default error message.

    //! Default Constructor
    /*! Constructs a new parser exception object. */
    ParserException() : message{DEFAULT_EMPTY_MESSAGE} {}

    //! Alternate Constructor
    /*! Constructs a new parser exception object.
        \param msg the error message.
    */
    ParserException(const string& msg) : message{msg} {}

    //! Member function that returns the error message.
    /*!
        \return char pointer for the error message.
    */
    const char* what() const noexcept
    {
        return message.c_str();
    }

private:
    string message; //!< The error message.
};

#endif // PARSEREXCEPTION_H

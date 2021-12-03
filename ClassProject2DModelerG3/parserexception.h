#ifndef PARSEREXCEPTION_H
#define PARSEREXCEPTION_H

#include <string>    /* string */
#include <exception> /* Exception Class */
using std::string;
using std::exception;


class ParserException : public exception
{
public:
    const string DEFAULT_EMPTY_MESSAGE = "File is corrupted.";

    ParserException() : message{DEFAULT_EMPTY_MESSAGE} {}

    ParserException(const string& msg) : message{msg} {}

    const char* what() const noexcept
    {
        return message.c_str();
    }

private:
    string message;
};

#endif // PARSEREXCEPTION_H

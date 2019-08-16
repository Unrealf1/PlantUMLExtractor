//
// Created by fedor on 8/15/19.
//

#ifndef PLANTUMLEXTRACTOR_ARGPARSEREXCEPTIONS_HPP
#define PLANTUMLEXTRACTOR_ARGPARSEREXCEPTIONS_HPP

#include <exception>

class RepeatedArgument: public std::exception
{
    virtual const char* what() const throw()
    {
        return "One argument is given more then one time";
    }
};

class MissingEssential: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Essential argument is missing";
    }
};

class NoArgumentAfterKey: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Missing argument after key word";
    }
};

#endif //PLANTUMLEXTRACTOR_ARGPARSEREXCEPTIONS_HPP

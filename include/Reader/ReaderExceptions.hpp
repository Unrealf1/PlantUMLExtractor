//
// Created by fedor on 8/15/19.
//

#ifndef PLANTUMLEXTRACTOR_READEREXCEPTIONS_HPP
#define PLANTUMLEXTRACTOR_READEREXCEPTIONS_HPP

#include <exception>

class NoWords: public std::exception
{
    virtual const char* what() const throw()
    {
        return "No words in file";
    }
};

#endif //PLANTUMLEXTRACTOR_READEREXCEPTIONS_HPP

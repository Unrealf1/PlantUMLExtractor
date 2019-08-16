//
// Created by fedor on 8/10/19.
//

#ifndef PLANTUMLEXTRACTOR_HELPER_HPP
#define PLANTUMLEXTRACTOR_HELPER_HPP

#include <exception>

namespace PUMLE {
    enum class language {
        kotlin
    };

    class UnreachableCode: public std::exception
    {
        virtual const char* what() const throw()
        {
            return "This shouldn't happened";
        }
    };
}

#endif //PLANTUMLEXTRACTOR_HELPER_HPP

//
// Created by fedor on 8/15/19.
//

#ifndef PLANTUMLEXTRACTOR_IREADER_HPP
#define PLANTUMLEXTRACTOR_IREADER_HPP

#include "ReaderExceptions.hpp"

namespace PUMLE {
    class IReader {
    public:
        virtual ClassSource ExtractClass(const std::string& classname) = 0;
        virtual std::vector<std::string> GetAllClasses() = 0;
    };
}

#endif //PLANTUMLEXTRACTOR_IREADER_HPP

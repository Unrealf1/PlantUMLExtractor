//
// Created by fedor on 8/10/19.
//

#ifndef PLANTUMLEXTRACTOR_WRITER_HPP
#define PLANTUMLEXTRACTOR_WRITER_HPP

#include <fstream>
#include <string>
#include "ClassSource.hpp"

namespace PUMLE {
    class Writer {
    public:
        Writer(const std::string& filename);
        void Write(const ClassSource& classSource);
        static std::string ComposeFileName(const std::string& initialName);
    private:
        std::ofstream ofstr;
    };
}

#endif //PLANTUMLEXTRACTOR_WRITER_HPP

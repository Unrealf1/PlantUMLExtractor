//
// Created by fedor on 8/15/19.
//

#ifndef PLANTUMLEXTRACTOR_ARGPARSER_HPP
#define PLANTUMLEXTRACTOR_ARGPARSER_HPP

#include <string>
#include <vector>
#include "ArgparserExceptions.hpp"

class Argparser {
public:
    Argparser(int argc, char** argv);
    std::string GetOutputFileName() const;
    std::string GetInputFileName() const;
    std::string GetClassname() const;
    bool GetHelp() const;
private:
    std::string outputFileName;
    std::string inputFileName;
    std::string classname;
    bool help;
};

#endif //PLANTUMLEXTRACTOR_ARGPARSER_HPP

//
// Created by fedor on 8/15/19.
//

#include "Argparser/Argparser.hpp"


Argparser::Argparser(int argc, char **argv)
:help(false) {
    for (int i = 1; i < argc; ++i) {
        std::string current(argv[i]);
        if (current == "-o" || current == "--out") {
            if (!outputFileName.empty()) {
                throw RepeatedArgument();
            }
            ++i;
            if (i == argc) {
                throw NoArgumentAfterKey();
            } else {
                outputFileName = argv[i];
            }
        } else if (current == "-c" || current == "--class") {
            if (!classname.empty()) {
                throw RepeatedArgument();
            }
            ++i;
            if (i == argc) {
                throw NoArgumentAfterKey();
            } else {
                classname = argv[i];
            }
        } else if (current == "-h" || current == "--help") {
            if (help) {
                throw RepeatedArgument();
            }
            help = true;
        } else {
            if (!inputFileName.empty()) {
                throw RepeatedArgument();
            }
            inputFileName = argv[i];
        }
    }
    if (inputFileName.empty() && !help) {
        throw MissingEssential();
    }
}

std::string Argparser::GetOutputFileName() const {
    return outputFileName;
}
std::string Argparser::GetInputFileName() const {
    return inputFileName;
}
std::string Argparser::GetClassname() const {
    return  classname;
}

bool Argparser::GetHelp() const {
    return help;
}
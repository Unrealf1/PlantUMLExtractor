//
// Created by fedor on 8/10/19.
//

#include "Writer.hpp"

namespace PUMLE {
    Writer::Writer(const std::string& filename)
    :ofstr(filename) {

    }
    void Writer::Write(const ClassSource& classSource) {
        ofstr << "@startuml\n"
        << "class " << classSource.classname << " {\n";

        if (!classSource.public_members.empty()) {
            ofstr << "__public members__\n" << std::endl;
            for (auto& member : classSource.public_members) {
                ofstr << '+' << member << '\n';
            }
        }

        if (!classSource.public_functions.empty()) {
            ofstr << "__public methods__\n" << std::endl;
            for (auto& method : classSource.public_functions) {
                ofstr << '+' << method << '\n';
            }
        }

        if (!classSource.private_members.empty()) {
            ofstr << "__private members__\n" << std::endl;
            for (auto& member : classSource.private_members) {
                ofstr << '-' << member << '\n';
            }
        }

        if (!classSource.private_functions.empty()) {
            ofstr << "__private methods__\n" << std::endl;
            for (auto& method : classSource.private_functions) {
                ofstr << '-' << method << '\n';
            }
        }
        ofstr << "}\n";

        for (auto& inner_class : classSource.inner_classes) {
            ofstr << classSource.classname << " +-- " << inner_class << '\n';
        }

        ofstr << "@enduml\n";
        ofstr << std::flush;
    }
    std::string Writer::ComposeFileName(const std::string& initialName) {
        return "test.puml";
    }
}
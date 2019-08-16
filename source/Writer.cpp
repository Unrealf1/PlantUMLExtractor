//
// Created by fedor on 8/10/19.
//

#include "Writer.hpp"

namespace PUMLE {
    Writer::Writer(const std::string& filename)
    :ofstr(filename) {

    }

    void Writer::Begin(){
        ofstr << "@startuml\n";
    }

    void Writer::End(){
        ofstr << "@enduml\n";
        ofstr << std::flush;
    }

    void Writer::Write(const ClassSource& classSource) {
        if (classSource.type == ClassType::Enum) {
            ofstr << "enum " << classSource.classname << " {\n";
            for (auto& member : classSource.public_members) {
                ofstr << member << '\n';
            }
            ofstr << "}\n";
            return;
        } else if(classSource.type == ClassType::Class) {
            ofstr << "class " << classSource.classname << " {\n";
        } else if (classSource.type == ClassType::Object) {
            ofstr << "class " << classSource.classname << "<< (O, white) >>" << " {\n";
        } else {
            ofstr << "object " << classSource.classname << " {\n";
        }

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
    }
    std::string Writer::ComposeFileName(const std::string& initialName) {
        return "test.puml";
    }
}
//
// Created by fedor on 8/11/19.
//

#ifndef PLANTUMLEXTRACTOR_CLASSSOURCE_HPP
#define PLANTUMLEXTRACTOR_CLASSSOURCE_HPP

#include <vector>

namespace PUMLE {
    enum class ClassType {
        None, Class, Object, Enum
    };

    class ClassSource {
    public:
        ClassType type;
        std::string classname;
        std::vector<std::string> public_functions;
        std::vector<std::string> private_functions;
        std::vector<std::string> public_members;
        std::vector<std::string> private_members;
        std::vector<std::string> inner_classes;
    };
}

#endif //PLANTUMLEXTRACTOR_CLASSSOURCE_HPP

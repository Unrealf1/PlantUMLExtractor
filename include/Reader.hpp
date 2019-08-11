//
// Created by fedor on 8/10/19.
//

#ifndef PLANTUMLEXTRACTOR_READER_HPP
#define PLANTUMLEXTRACTOR_READER_HPP

#include <fstream>
#include "ClassSource.hpp"

namespace PUMLE {
    enum class search_state {
        normal, in_class, finished, in_function, in_member, in_correct_class, in_inner
    };

    enum class filter_state {
        out_of_comment, inside_inline, inside_multi, inside_string
    };

    class Reader {
    public:
        explicit Reader(const std::string &filename);

        ClassSource FindClass(const std::string& classname);
    private:
        std::vector<std::string> filterSource();
        std::string ClearName(const std::string&) const;
        std::ifstream ifstr;
    };
}

#endif //PLANTUMLEXTRACTOR_READER_HPP

//
// Created by fedor on 8/15/19.
//

#ifndef PLANTUMLEXTRACTOR_IFILTER_HPP
#define PLANTUMLEXTRACTOR_IFILTER_HPP

#include <fstream>
#include <string>
#include <vector>

enum class filter_state {
    out_of_comment, inside_inline, inside_multi, inside_string
};

class IFilter {
public:
    virtual std::vector<std::string> filterSource(std::ifstream& fileStream) const = 0;
};

#endif //PLANTUMLEXTRACTOR_IFILTER_HPP

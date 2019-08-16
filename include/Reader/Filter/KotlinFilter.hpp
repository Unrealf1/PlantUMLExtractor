//
// Created by fedor on 8/15/19.
//

#ifndef PLANTUMLEXTRACTOR_KOTLINFILTER_HPP
#define PLANTUMLEXTRACTOR_KOTLINFILTER_HPP

#include <fstream>
#include "IFilter.hpp"

class KotlinFilter : public IFilter {
public:
    KotlinFilter() = default;
    std::vector<std::string> filterSource(std::ifstream& fileStream) const override;
};


#endif //PLANTUMLEXTRACTOR_KOTLINFILTER_HPP

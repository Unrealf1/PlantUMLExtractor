//
// Created by fedor on 8/10/19.
//

#ifndef PLANTUMLEXTRACTOR_KOTLINREADER_HPP
#define PLANTUMLEXTRACTOR_KOTLINREADER_HPP

#include <fstream>
#include "ClassSource.hpp"
#include "IReader.hpp"
#include "Filter/KotlinFilter.hpp"

namespace PUMLE {
    enum class search_state {
        normal, in_class, finished, in_function, in_member, in_correct_class, in_inner
    };

    class KotlinReader : public IReader {
    public:
        explicit KotlinReader(std::ifstream& fileStream);

        ClassSource ExtractClass(const std::string& classname) override;
        std::vector<std::string> GetAllClasses() override;
    private:
        void InitWords();

        std::string ClearName(const std::string&) const;
        std::ifstream& fileStream;
        std::vector<std::string> words;
    };
}

#endif //PLANTUMLEXTRACTOR_KOTLINREADER_HPP

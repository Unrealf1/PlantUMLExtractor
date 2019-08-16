//
// Created by fedor on 8/10/19.
//

#ifndef PLANTUMLEXTRACTOR_KOTLINREADER_HPP
#define PLANTUMLEXTRACTOR_KOTLINREADER_HPP

#include <array>
#include <fstream>
#include "ClassSource.hpp"
#include "Filter/KotlinFilter.hpp"
#include "Helper.hpp"
#include "IReader.hpp"


namespace PUMLE {
    enum class search_state {
        normal, in_class, finished, in_function, in_member, in_correct_class, in_inner, in_correct_enum
    };

    class KotlinReader : public IReader {
    public:
        explicit KotlinReader(std::ifstream& fileStream);

        ClassSource ExtractClass(const std::string& classname) override;
        std::vector<std::string> GetAllClasses() override;
    private:
        void InitWords();
        ClassType checkForClassType(const std::string& word) const;

        std::ifstream& fileStream;
        std::vector<std::string> words;
    };
}

#endif //PLANTUMLEXTRACTOR_KOTLINREADER_HPP
